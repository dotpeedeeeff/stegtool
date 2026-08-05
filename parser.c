#include "bmp.h"
#include "parser.h"
#include <stddef.h>

int initParser(BYTE * buffer, Parser * parser, DWORD length)
{
    // This function initalises the parser after checking for null pointers
    if (!buffer)
    {
        return 0;
    }
    if (!parser)
    {
        return 0;
    }

    parser->start = buffer;
    parser->current = buffer;
    parser->end = buffer + length;

    return 1;
}

/*
int readByte()

int readWord()

int readDWord()

int readPixel()
*/
