#ifndef PARSER_H
#define PARSER_H

typedef struct Parser {
    uint8_t * start;
    uint8_t * current;
    uint8_t * end;
} Parser;

int initParser(uint8_t * buffer, Parser * parser, uint8_t length);
int readByte(Parser * parser, uint8_t * output);
int readWord(Parser * parser, uint16_t * output);
int readDWord(Parser * parser, uint32_t * output);

#endif
