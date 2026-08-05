#ifndef PARSER_H
#define PARSER_H

typedef struct Parser {
    BYTE * start;
    BYTE * current;
    BYTE * end;
} Parser;

int initParser(BYTE * buffer, Parser * parser, DWORD length);

#endif
