#include <stdint.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;

typedef struct {
    WORD Signature;
    DWORD FileSize;
    DWORD reserved;
    DWORD DataOffset;
} bmpHeader;

typdef struct {
    DWORD Size;
    DWORD Width;
    DWORD Height;
    WORD Planes;
    WORD BitsPerPixel;
    DWORD Compression;
    DWORD ImageSize;
    DWORD XpixelsPerM;
    DWORD YpixelsPerM;
    DWORD ColorsUsed;
    DWORD ImportantColors;
} infoHeader;

typedef struct {
    BYTE Blue;
    BYTE Green;
    BYTE Red;
} pixelData;
