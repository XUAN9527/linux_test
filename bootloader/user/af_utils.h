#ifndef AF_UTILS_H_
#define AF_UTILS_H_

#include <stdint.h>
#include <stddef.h>

uint32_t af_calc_crc32(uint32_t crc, const void *buf, size_t size);


#endif

