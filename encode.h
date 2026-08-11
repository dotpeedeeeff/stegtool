#ifndef ENCODE_H
#define ENCODE_H

uint8_t pixelAddition(uint8_t input1, uint8_t input2);
int encode(pixelData *pixeldata, uint32_t pixels, char *message);
void characterFilter(char *input, char *output);
uint32_t calcMaxMessage(uint32_t pixels);
uint8_t encodeBlue(char input);
uint8_t encodeGreen(char input);
uint8_t encodeRed(char input);
int setLength(pixelData *pixeldata, uint32_t messageLength);



#endif
