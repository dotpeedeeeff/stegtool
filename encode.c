#include <ctype.h>
#include "bmp.h"
#include "encode.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int encode(pixelData *pixeldata, uint32_t pixels, char *message)
{
    // check for NULL inputs
    if (pixeldata == NULL || message == NULL)
    {
        printf("Data read error\n");
        return 0;
    }

    // Allocate space for filtered string and initialise
    char *filteredText = calloc((strlen(message) + 1), sizeof(char));
    if (filteredText == NULL)
    {
        printf("Memory allocation failure.\n");
        return 0;
    }
    filteredText[0] = '\0';

    // filter out unwanted chars
    characterFilter(message, filteredText);

    // check message will fit inside image
    uint32_t stringLength = strlen(filteredText);

    if (stringLength > calcMaxMessage(pixels))
    {
        printf("Message too long\n");
        return 0;
    }
    uint32_t messageLength = stringLength * 2;

    // create reference values

    for (uint32_t i = 4; i < (messageLength + 4); i+= 2)
    {
            pixeldata[i].Blue = pixeldata[i + 1].Blue;
            pixeldata[i].Green = pixeldata[i + 1].Green;
            pixeldata[i].Red = pixeldata[i + 1].Red;
    }
    // allocate and initialise shift array
    pixelData *shiftarray = calloc((2 * messageLength) + 4, sizeof(pixelData));
    if (shiftarray == NULL)
    {
        printf("Memory allocation error\n");
        return 0;
    }

    // populate shift array
    for (uint32_t i = 0, j = 5; i < stringLength; i++)
    {
        if (filteredText[i] >= 'A' && filteredText[i] <= 'Z')
        {
            shiftarray[j].Red = encodeRed(filteredText[i]);
        }
        else if (filteredText[i] >= '0' && filteredText[i] <= '9')
        {
            shiftarray[j].Green = encodeGreen(filteredText[i]);
        }
        else
            shiftarray[j].Blue = encodeBlue(filteredText[i]);
        j += 2;
    }

    // add shift array to the pixel array
    for (uint32_t i = 0; i < (messageLength + 5); i++)
    {
        pixeldata[i].Blue = pixelAddition(pixeldata[i].Blue, shiftarray[i].Blue);
        pixeldata[i].Green = pixelAddition(pixeldata[i].Green, shiftarray[i].Green);
        pixeldata[i].Red = pixelAddition(pixeldata[i].Red, shiftarray[i].Red);

    }

    // set reference pixel
    setLength(pixeldata, messageLength);

    free(filteredText);
    free(shiftarray);
    return 1;
}

uint8_t encodeBlue(char input)
{
    if (input == ' ')
    {
        return 1;
    }
    else
        return 2;
}

uint8_t encodeGreen(char input)
{
    return input - 0x2F;
}

uint8_t encodeRed(char input)
{
    return input - 0x40;
}

void characterFilter(char *input, char *output)
{
    /* This fuction strips down the input string to a
     * reduced set of digits, upper case letters and a few
     * simple punctuations*/

    int length = strlen(input);
    char buffer[2] = {' ', '\0'};
    for (int i = 0; i < length; i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            buffer[0] = input[i];
            strncat(output, buffer, 1);
        }
        else if (input[i] >= 'a' && input[i] <= 'z')
        {
            buffer[0] = toupper(input[i]);
            strncat(output, buffer, 1);
        }
        else if (input[i] >= '0' && input[i] <= '9')
        {
            buffer[0] = input[i];
            strncat(output, buffer, 1);
        }
        else if (input[i] == ' ' || input[i] == '.' || input[i] == '?')
        {
            buffer[0] = input[i];
            strncat(output, buffer, 1);
        }

        else
            continue;

    }
}

uint32_t calcMaxMessage(uint32_t pixels)
{
    return (pixels - 4) / 2;
}

int setLength(pixelData *pixeldata, uint32_t messageLength)
{
    if (pixeldata == NULL)
    {
        printf("Data read error\n");
        return 0;
    }
    uint8_t valueGreen = messageLength / 255;
    uint8_t valueBlue = messageLength % 255;

    pixeldata[0].Green = valueGreen;
    pixeldata[0].Blue = valueBlue;
    pixeldata[0].Red = pixeldata[1].Red;

    return 1;
}

uint8_t pixelAddition(uint8_t input1, uint8_t input2)
{
    /* This function adds two pixel values, if the total
     will be greater than 255, the output is subtracted*/
    if (input1 + input2 > 255)
    {
        return input1 -= input2;
    }
    else
    {
        return input1 += input2;
    }
}
