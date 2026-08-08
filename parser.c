#include <stdint.h>
#include "parser.h"
#include <string.h>


int initParser(uint8_t * buffer, Parser * parser, uint8_t length)
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


int readByte(Parser * parser, uint8_t * output)
{
    if (parser && output)
    {
        if (parser->end >= parser-> current + 1)
        {
            memcpy(output, parser->current, sizeof(uint8_t));
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

int readWord(Parser * parser, uint16_t * output)
{
    if (parser && output)
    {
        if (parser->end >= parser->current + 2)
        {
            memcpy(output, parser->current, sizeof(uint16_t));
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

int readDWord(Parser * parser, uint32_t * output)
{
    if (parser && output)
    {
        if (parser->end >= parser->current + 4)
        {
            memcpy(output, parser->current, sizeof(uint32_t));
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
