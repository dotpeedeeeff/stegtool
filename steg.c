#include "bmp.h"
#include "parser.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADERSIZE 14

int initHeader(bmpHeader *header);
int parseHeader(Parser *parser, bmpHeader *header);
int initInfoHeader(infoHeader *infoheader);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("File argument missing.\n");
        return 1;
    }

    // open image file
    FILE *ptr = fopen(argv[1], "rb");
    if (ptr == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    // read bmp header to buffer
    BYTE headerBuffer[HEADERSIZE];

    int headerCount = fread(headerBuffer, sizeof(BYTE), HEADERSIZE, ptr);

    if (!(headerCount == HEADERSIZE))
    {
        printf("File read malfunction.\n");
        return 1;
    }

    // create header and parser structs
    bmpHeader header;
    infoHeader infoheader;
    Parser parser;
    // initalise parser and bmpHeader
    initHeader(&header);
    initInfoHeader(&infoheader);
    initParser(headerBuffer, &parser, HEADERSIZE);

    // parse bmpHeader
    if(!parseHeader(&parser, &header))
    {
        printf("Parsing failed\n");
        return 1;
    }





    printf("Signature: %x\n", header.Signature);
    printf("File Size: %i\n", header.FileSize);
    printf("Reserved: %i\n", header.reserved);
    printf("Offset: %i\n", header.DataOffset);


    fclose(ptr);
    return 0;
}

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

