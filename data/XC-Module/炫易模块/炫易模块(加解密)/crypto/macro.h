﻿#pragma once
#ifndef XL_XEXPAND_CYRPTO_MACRO_H
#define XL_XEXPAND_CYRPTO_MACRO_H 
#include <stdint.h>
#include <string.h>

#define SHL(datas, bits) (((datas)&0xFFFFFFFF) << ((uint32_t)bits))
#define SHR(datas, bits) (((datas)&0xFFFFFFFF) >> ((uint32_t)bits))

#define SHL64(datas, bits) (((datas)&0xFFFFFFFFFFFFFFFF) << ((uint64_t)bits))
#define SHR64(datas, bits) (((datas)&0xFFFFFFFFFFFFFFFF) >> ((uint64_t)bits))

#define ROL(datas, bits) ((datas) << (bits) | (datas) >> (32 - (bits)))
#define ROL64(datas, bits) ((datas) << (bits) | (datas) >> (64 - (bits)))

#define ROR(datas, bits) ((datas) >> (bits) | (datas) << (32 - (bits)))
#define ROR64(datas, bits) ((datas) >> (bits) | (datas) << (64 - (bits)))

#define Tranverse16(x) ((((uint16_t)(x)&0xff00) >> 8) | (((uint16_t)(x)&0x00ff) << 8))
#define Tranverse32(x) ((((uint32_t)(x)&0xff000000) >> 24) | (((uint32_t)(x)&0x00ff0000) >> 8) | (((uint32_t)(x)&0x0000ff00) << 8) | (((uint32_t)(x)&0x000000ff) << 24))
#define Tranverse64(x) ((((uint64_t)(x)&0xff00000000000000) >> 56) | (((uint64_t)(x)&0x00ff000000000000) >> 40) | (((uint64_t)(x)&0x0000ff0000000000) >> 24) | (((uint64_t)(x)&0x000000ff00000000) >> 8) | (((uint64_t)(x)&0x00000000ff000000) << 8) | (((uint64_t)(x)&0x0000000000ff0000) << 24) | (((uint64_t)(x)&0x000000000000ff00) << 40) | (((uint64_t)(x)&0x00000000000000ff) << 56))

#define GET_UINT32_BE(n, b, i) (n) = ((uint32_t)b[i] << 24) | ((uint32_t)b[i + 1] << 16) | ((uint32_t)b[i + 2] << 8) | ((uint32_t)b[i + 3]);

#define PUT_UINT32_BE(n, b, i)                     \
    {                                              \
        (b)[(i)] = (unsigned char)((n) >> 24);     \
        (b)[(i) + 1] = (unsigned char)((n) >> 16); \
        (b)[(i) + 2] = (unsigned char)((n) >> 8);  \
        (b)[(i) + 3] = (unsigned char)((n));       \
    }
#endif