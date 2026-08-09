#ifndef HELPER_H
#define HELPER_H

#include "parser.h"

int initHeader(bmpHeader *header);
int initInfoHeader(infoHeader *infoheader);
int parseHeader(Parser *parser, bmpHeader *header);
int parseInfoHeader(Parser *parser, infoHeader *infoheader);
int loadHeader(bmpHeader *header, char *filename);
int loadImage(BYTE *image, bmpHeader *header, char *filename);
int loadInfoHeader(BYTE *input, infoHeader *output, int length);
int writeOutput(BYTE *output, bmpHeader *header);

#endif
