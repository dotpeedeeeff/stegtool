#include "bmp.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

int initHeader(bmpHeader *header)
{
    if (header)
    {
        header->Signature = 0;
        header->FileSize = 0;
        header->reserved = 0;
        header->DataOffset = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int initInfoHeader(infoHeader *infoheader)
{
    if (infoheader)
    {
        infoheader->Size = 0;
        infoheader->Width = 0;
        infoheader->Height = 0;
        infoheader->Planes = 0;
        infoheader->BitsPerPixel = 0;
        infoheader->Compression = 0;
        infoheader->ImageSize = 0;
        infoheader->XpixelsPerM = 0;
        infoheader->YpixelsPerM = 0;
        infoheader->ColorsUsed = 0;
        infoheader->ImportantColors = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int parseHeader(Parser *parser, bmpHeader *header)
{
    int count = 0;
    if (readWord(parser, &header->Signature))
    {
        count++;
        if (header->Signature != 0x4D42)
        {
            printf("File format is not bmp\n");
            return 0;
        }

    }
    if (readDWord(parser, &header->FileSize))
    {
        count++;
    }
    if (readDWord(parser, &header->reserved))
    {
        count++;
    }
    if (readDWord(parser, &header->DataOffset))
    {
        count++;
    }
    if (count == 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int parseInfoHeader(Parser *parser, infoHeader *infoheader)
{
    int count = 0;
    if (readDWord(parser, &infoheader->Size))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->Width))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->Height))
    {
        count++;
    }
    if (readWord(parser, &infoheader->Planes))
    {
        count++;
    }
    if (readWord(parser, &infoheader->BitsPerPixel))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->Compression))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->ImageSize))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->XpixelsPerM))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->YpixelsPerM))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->ColorsUsed))
    {
        count++;
    }
    if (readDWord(parser, &infoheader->ImportantColors))
    {
        count++;
    }
    if (count == 11)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int loadHeader(bmpHeader *header, char *filename)
{
    /*This function reads the incoming file and the
     populates the BMP header struct*/

    if (header == NULL || filename == NULL)
    {
        printf("Inputs null\n");
        return 0;
    }

    /* header size as per BMP standard */
    int headerSize = 14;

    BYTE *buffer = malloc(sizeof(BYTE) * headerSize);
    if (buffer == NULL)
    {
        printf("Memory allocation error\n");
        return 0;
    }

    FILE *ptr = fopen(filename, "rb");
    if (ptr == NULL)
    {
        printf("File not found\n");
        free(buffer);
        return 0;
    }

    int headerCount = fread(buffer, sizeof(BYTE), headerSize, ptr);
    if (headerCount != headerSize)
    {
        printf("File read error\n");
        free(buffer);
        fclose(ptr);
        return 0;
    }
    // ensure header struct in init to 0
    initHeader(header);

    // create and init parser
    Parser parser;
    initParser(buffer, &parser, headerSize);

    // parse the header to populate it
    parseHeader(&parser, header);

    fclose(ptr);
    free(buffer);
    return 1;
}

int loadImage(BYTE *image, bmpHeader *header, char *filename)
{
    /* This function reads in the whole image file to the
     specified pointer.*/
    if (image == NULL || header == NULL ||filename == NULL)
    {
        printf("Inputs null\n");
        return 0;
    }

    FILE *ptr = fopen(filename, "rb");
    if (ptr == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    int size = header->FileSize;

    int readCount = fread(image, sizeof(BYTE), size, ptr);
    if (readCount != size)
    {
        printf("File read error\n");
        fclose(ptr);
        return 0;
    }

    fclose(ptr);
    return 1;
}

int loadInfoHeader(BYTE *input, infoHeader *output, int length)
{
    if (input == NULL || output == NULL)
    {
        printf("Inputs null\n");
        return 0;
    }

    Parser parser;
    initParser(input, &parser, length);

    initInfoHeader(output);

    parseInfoHeader(&parser, output);

    return 1;
}

int writeOutput(BYTE *output, bmpHeader *header)
{
    FILE *out = fopen("output.bmp", "wb");
    if (fwrite(output, sizeof(BYTE), header->FileSize, out) != header->FileSize)
    {
        printf("Output write error\n");
        return 0;
    }
    fclose(out);
    return 1;
}

long findFileSize(char *filename)
{
    /*This function reads the incoming file and the
     calculates the length using file pointer operations */

    if (filename == NULL)
    {
        printf("Inputs null\n");
        return 0;
    }

    FILE *ptr = fopen(filename, "rb");
    if (ptr == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    long start = ftell(ptr);

    // move file pointer to EOF
    fseek(ptr, 0, SEEK_END);

    long end = ftell(ptr);

    fclose(ptr);

    return end - start;
}
