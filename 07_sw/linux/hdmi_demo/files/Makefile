APP = hdmi-demo

SRCS = hdmi-demo.c mmio_util.c dynclk.c vtc.c vdma.c
OBJS = $(SRCS:.c=.o)

CFLAGS ?= -O2 -Wall -Wextra
LDFLAGS ?= -lm

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

install:
	install -d $(DESTDIR)/usr/bin
	install -m 0755 $(APP) $(DESTDIR)/usr/bin/$(APP)

clean:
	rm -f $(APP) $(OBJS)
