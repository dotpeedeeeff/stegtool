#ifndef PARSER_H
#define PARSER_H

typedef struct Parser {
    BYTE * start;
    BYTE * current;
    BYTE * end;
} Parser;

int initParser(BYTE * buffer, Parser * parser, BYTE length);
int readByte(Parser * parser, BYTE * output);
int readWord(Parser * parser, WORD * output);
int readDWord(Parser * parser, DWORD * output);

#endif
