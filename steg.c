#include "bmp.h"
#include "encode.h"
#include "decode.h"
#include "helper.h"
#include "parser.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("File argument missing.\n");
        return 1;
    }

    // create header and infoheader structs
    bmpHeader header;
    infoHeader infoheader;

    /* Checking the file size independently of the
     reported file size in the bmp header */
    long ptrFileSize = findFileSize(argv[1]);

    /* Aborting if the file size is below the minimum size
     of header + infoheader */
    if (ptrFileSize < 0x37)
    {
        printf("File too small\n");
        return 1;
    }

    // populate header struct
    loadHeader(&header, argv[1]);

    if (header.FileSize != ptrFileSize)
    {
        printf("File size mismatch\n");
        return 1;
    }

    /* Allocating memory to fit the whole file and then
    reading in the whole image*/
    BYTE *image = malloc(sizeof(BYTE) * header.FileSize);
    if (image == NULL)
    {
        printf("Memory allocation error\n");
        return 0;
    }
    loadImage(image, &header, argv[1]);

    /* Declaring pointers to give access to the infoheader
     and pixel information parts of the image*/

    BYTE *infoheaderptr = image + 14;
    BYTE *pixelptr = image + header.DataOffset;

    // populate infoheader struct

    loadInfoHeader(infoheaderptr, &infoheader, (header.DataOffset - 14));

    /* Creating a memory allocation to manipulate the pixel values,
     followed by copying pixel data*/

    int pixelBytes = header.FileSize - header.DataOffset;

    /* Calculate image size, in order to know max message length */
    uint32_t pixels = infoheader.Width * infoheader.Height;

    pixelData *pixeldata = calloc(pixels, sizeof(pixelData));
    if (pixeldata == NULL)
    {
        printf("Memory allocation error\n");
        return 1;
    }
    memcpy(pixeldata, pixelptr, sizeof(BYTE) * pixelBytes);

    /* If two arguments, enter decode path*/
    if (argc == 2)
    {
        if (!decode(pixeldata))
        {
            printf("Decoding error\n");
            free(image);
            free(pixeldata);
            return 1;
        }
    }
    /* If 3 arguments, enter encode path */
    if (argc == 3)
    {
        if(!encode(pixeldata, pixels, argv[2]))
        {
            printf("encoding error\n");
            free(pixeldata);
            free(image);
            return 1;
        }

        /* Copy the pixel data array back to the image byte array */
        memcpy(pixelptr, pixeldata, sizeof(BYTE) * pixelBytes);

        /* Write the complete image byte array to file */
       if(!writeOutput(image, &header))
       {
            printf("writing error\n");
            free(pixeldata);
            free(image);
            return 1;
       }
    }
    free(pixeldata);
    free(image);

    return 0;
}
