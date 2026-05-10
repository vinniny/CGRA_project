/* Single definition of the runtime CGRA base pointer used by the shim.
 * Initialized by cgra_shim_attach(). */
#include <stdint.h>

uintptr_t _cgra_shim_base = 0;
