#include "mmio_util.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int read_first_line(const char *path, char *buf, size_t buf_len)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        return -errno;
    }
    if (!fgets(buf, (int)buf_len, fp)) {
        fclose(fp);
        return -EIO;
    }
    fclose(fp);
    size_t n = strlen(buf);
    while (n > 0 && (buf[n - 1] == '\n' || buf[n - 1] == '\r')) {
        buf[--n] = '\0';
    }
    return 0;
}

static int find_uio_dev_by_name(const char *wanted_name, char *dev_path, size_t dev_path_len)
{
    DIR *dir = opendir("/sys/class/uio");
    if (!dir) {
        return -errno;
    }

    struct dirent *de = NULL;
    char path[PATH_MAX];
    char name[256];
    int ret = -ENOENT;

    while ((de = readdir(dir)) != NULL) {
        if (strncmp(de->d_name, "uio", 3) != 0) {
            continue;
        }
        snprintf(path, sizeof(path), "/sys/class/uio/%s/name", de->d_name);
        if (read_first_line(path, name, sizeof(name)) != 0) {
            continue;
        }
        if (strcmp(name, wanted_name) == 0) {
            snprintf(dev_path, dev_path_len, "/dev/%s", de->d_name);
            ret = 0;
            break;
        }
    }

    closedir(dir);
    return ret;
}

static int get_uio_map_size_from_dev(const char *dev_path, size_t *size_out)
{
    const char *name = strrchr(dev_path, '/');
    if (!name || strncmp(name + 1, "uio", 3) != 0) {
        return -EINVAL;
    }

    char path[PATH_MAX];
    char buf[64];
    snprintf(path, sizeof(path), "/sys/class/uio/%s/maps/map0/size", name + 1);
    int ret = read_first_line(path, buf, sizeof(buf));
    if (ret != 0) {
        return ret;
    }

    *size_out = strtoull(buf, NULL, 0);
    return 0;
}

int mmio_map_uio_by_name(const char *wanted_name,
                         const char *fallback_dev,
                         size_t expected_map_size,
                         volatile uint8_t **base_out,
                         size_t *map_size_out,
                         int *fd_out)
{
    char dev_path[PATH_MAX] = {0};
    size_t map_size = expected_map_size;

    if (wanted_name && find_uio_dev_by_name(wanted_name, dev_path, sizeof(dev_path)) == 0) {
        /* found by name */
    } else if (fallback_dev) {
        snprintf(dev_path, sizeof(dev_path), "%s", fallback_dev);
    } else {
        return -ENOENT;
    }

    size_t sysfs_size = 0;
    if (get_uio_map_size_from_dev(dev_path, &sysfs_size) == 0 && sysfs_size != 0) {
        map_size = sysfs_size;
    }
    if (map_size == 0) {
        return -EINVAL;
    }

    int fd = open(dev_path, O_RDWR | O_SYNC);
    if (fd < 0) {
        return -errno;
    }

    void *map = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        int err = -errno;
        close(fd);
        return err;
    }

    *base_out = (volatile uint8_t *)map;
    *map_size_out = map_size;
    *fd_out = fd;
    return 0;
}

int mmio_map_physical(uint64_t phys_addr,
                      size_t map_size,
                      volatile uint8_t **base_out,
                      int *fd_out)
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        return -errno;
    }

    void *map = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)phys_addr);
    if (map == MAP_FAILED) {
        int err = -errno;
        close(fd);
        return err;
    }

    *base_out = (volatile uint8_t *)map;
    *fd_out = fd;
    return 0;
}

void mmio_unmap(volatile uint8_t *base, size_t map_size, int fd)
{
    if (base && base != MAP_FAILED) {
        munmap((void *)base, map_size);
    }
    if (fd >= 0) {
        close(fd);
    }
}
