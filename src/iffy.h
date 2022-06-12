
#ifndef IFFY_H
#define IFFY_H

#include <stdint.h>
#include <stddef.h>

#define iffy_endian_swap_32( num ) (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

#endif /* IFFY_H */

