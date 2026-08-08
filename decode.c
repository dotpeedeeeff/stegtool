#include "bmp.h"
#include "decode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int decode(pixelData *pixeldata)
{

    /* Read the blue value of the first pixel to determine
     message lenght*/
    int messageLength = findLength(pixeldata);
    int stringLength = messageLength / 2;

    // allocate memory to hold the array of pixel shifts.
    pixelData *shiftarray = malloc(sizeof(pixelData) * (stringLength));
    if (shiftarray == NULL)
    {
        printf("Memory allocation error\n");
        return 0;
    }

    /* For each pixel in the encoded zone, find the difference between
     the reference pixel and the shifted pixel. Write the difference to
     the array of pixel shifts*/

    for (int i = 5, j = 0; i < (messageLength + 4); i+=2)
    {
        shiftarray[j].Blue = abs(pixeldata[i - 1].Blue - pixeldata[i].Blue);
        shiftarray[j].Green = abs(pixeldata[i - 1].Green - pixeldata[i].Green);
        shiftarray[j].Red = abs(pixeldata[i - 1].Red - pixeldata[i].Red);
        j++;
    }

    // allocate memory for final output string and initialise termination
    char *outputString = malloc(sizeof(char) * (stringLength + 1));
    if (outputString == NULL)
    {
        printf("Memory allocation error\n");
        return 0;
    }
    outputString[0] = '\0';

    /* For each item in the shift array decode each char and add to
     the output string*/
    for (int i = 0; i < stringLength; i++)
    {
        if (shiftarray[i].Blue == 1 || shiftarray[i].Blue == 2)
        {
            char buffer[] = {' ', '\0'};
            buffer[0] = decodeBlue(shiftarray[i].Blue);
            strncat(outputString, buffer, 1);
            continue;
        }
        else if (shiftarray[i].Red <= 26 && shiftarray[i].Red >= 1)
        {
            char buffer[] = {' ', '\0'};
            buffer[0] = decodeRed(shiftarray[i].Red);
            strncat(outputString, buffer, 1);
            continue;
        }
        else if (shiftarray[i].Green <= 9)
        {
            char buffer[] = {' ', '\0'};
            buffer[0] = decodeGreen(shiftarray[i].Green);
            strncat(outputString, buffer, 1);
            continue;
        }
        else
            return 0;
    }

    // Print decoded text to the terminal.
    printf("Decoded text: %s\n", outputString);

    free(shiftarray);
    free(outputString);
    return 1;
}

int findLength(pixelData pixeldata[])
{
    return pixeldata[0].Blue;
}

char decodeBlue(uint8_t input)
{
    if (input == 1)
        return ' ';
    else
        return '.';
}

char decodeGreen(uint8_t input)
{
    return input + 0x2F;
}

char decodeRed(uint8_t input)
{
    return input + '@';
}


