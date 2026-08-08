#include "bmp.h"
#include "parser.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADERSIZE 14
#define INFOHEADERSIZE 40

int initHeader(bmpHeader *header);
int initInfoHeader(infoHeader *infoheader);
int parseHeader(Parser *parser, bmpHeader *header);
int parseInfoHeader(Parser *parser, infoHeader *infoheader);


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

    // read header to buffer
    BYTE headerBuffer[HEADERSIZE];
    int headerCount = fread(headerBuffer, sizeof(BYTE), HEADERSIZE, ptr);
    if (headerCount != HEADERSIZE)
    {
        printf("File read error\n");
        return 1;
    }

    // create header and parser structs
    bmpHeader header;
    infoHeader infoheader;
    Parser parser;
    // initalise header and infoheader

    //WORD *list[] = {&header.signature}

    void(*headerptrs[]) = {
        &header.Signature,
        &header.FileSize,
        &header.reserved,
        &header.DataOffset
    };

    initHeader(&header);
    initInfoHeader(&infoheader);

    printf("Signature is: %p\n", (WORD**)headerptrs[0]);

    // initialise parser and parse header
    initParser(headerBuffer, &parser, HEADERSIZE);
    if(!parseHeader(&parser, &header))
    {
        printf("Parsing failed\n");
        return 1;
    }

    //read infoheader to buffer
    BYTE infoheaderBuffer[INFOHEADERSIZE];
    int infoHeaderCount = fread(infoheaderBuffer, sizeof(BYTE), INFOHEADERSIZE, ptr);
    if (infoHeaderCount != INFOHEADERSIZE)
    {
        printf("File read error\n");
        return 1;
    }

    //re-initialise parser and parse infoheader
    initParser(infoheaderBuffer, &parser, INFOHEADERSIZE);
    if(!parseInfoHeader(&parser, &infoheader))
    {
        printf("Parsing failed\n");
        return 1;
    }

    int bytesRemaining = header.FileSize - header.DataOffset;
    // int pixelCount = infoheader.Width * infoheader.Height;

    pixelData *pixeldata = malloc(sizeof(BYTE) * bytesRemaining);
    if (pixeldata == NULL)
    {
        printf("Allocation fail\n");
        return 1;
    }
    int pixelDataCount = fread(pixeldata, sizeof(BYTE), bytesRemaining, ptr);
    if (pixelDataCount != bytesRemaining)
    {
        printf("File read error\n");
        return 1;
    }


    printf("Length: %i\n", pixeldata[0].Blue);


    free(pixeldata);
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
