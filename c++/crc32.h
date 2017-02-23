#ifndef CRC32_H_
#define CRC32_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


#define MAX_STR_LEN 4096

uint32_t Crc32_Compute(const char *str);

#endif
