#include "bmp.h"
#include "parser.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *ptr = fopen("test.bmp", "rb");
    if (ptr == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    BYTE bitmapHeader[14];

    int bitHeader = fread(bitmapHeader, sizeof(BYTE), 14, ptr);

    if (!(bitHeader == 14))
    {
        printf("File read malfunction.\n");
        return 1;
    }
    /*
    bmpHeader header;
    Parser parser;


    if (header.Signature == 0x4D42)
    {
        printf("BMP confirmed\n");
    }
    memcpy(&header.FileSize, parser.current, sizeof(DWORD));

    printf("File Size:%i bytes\n", header.FileSize);
    */
    fclose(ptr);
    return 0;
}
