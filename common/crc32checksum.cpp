#include "crc32checksum.h"


uint_least32_t Crc32(const unsigned char * buf, size_t len)
{
    uint_least32_t crc = 0xFFFFFFFF;
    while (len--)
        crc = (crc >> 8) ^ Crc32Table[(crc ^ *buf++) & 0xFF];
    return crc ^ 0xFFFFFFFF;
}
