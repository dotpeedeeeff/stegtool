#include "bmp.h"
#include "parser.h"
#include <string.h>


int initParser(BYTE * buffer, Parser * parser, BYTE length)
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


int readByte(Parser * parser, BYTE * output)
{
    if (parser && output)
    {
        if (parser->end >= parser-> current + 1)
        {
            memcpy(output, parser->current, sizeof(BYTE));
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int readWord(Parser * parser, WORD * output)
{
    if (parser && output)
    {
        if (parser->end >= parser->current + 2)
        {
            memcpy(output, parser->current, sizeof(WORD));
            parser->current += 2;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int readDWord(Parser * parser, DWORD * output)
{
    if (parser && output)
    {
        if (parser->end >= parser->current + 4)
        {
            memcpy(output, parser->current, sizeof(DWORD));
            parser->current += 4;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int readPixel(Parser * parser, pixelData * output)
{
    if (parser && output)
    {
        if (parser-> end >= parser->current + 3)
        {
            memcpy(output, parser->current, sizeof(pixelData));
            parser->current += 3;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

