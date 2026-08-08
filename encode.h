#ifndef ENCODE_H
#define ENCODE_H

int encode(pixelData *pixeldata, uint32_t pixels, char *message);
void characterFilter(char *input, char *output);
uint32_t calcMaxMessage(uint32_t pixels);
uint8_t encodeBlue(char input);
uint8_t encodeGreen(char input);
uint8_t encodeRed(char input);


#endif
