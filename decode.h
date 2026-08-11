#ifndef DECODE_H
#define DECODE_H

int findLength(pixelData pixeldata[]);
int decode(pixelData *pixeldata);
char decodeBlue(uint8_t input);
char decodeGreen(uint8_t input);
char decodeRed(uint8_t input);
int writeTextFile(int stringLength, char *output);

#endif
