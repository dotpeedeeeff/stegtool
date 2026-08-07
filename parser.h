#ifndef PARSER_H
#define PARSER_H

typedef struct Parser {
    uint8_t * start;
    uint8_t * current;
    uint8_t * end;
} Parser;

int initParser(uint8_t * buffer, Parser * parser, uint8_t length);
int readByte(Parser * parser, BYTE * output);
int readWord(Parser * parser, WORD * output);
int readDWord(Parser * parser, DWORD * output);

#endif
