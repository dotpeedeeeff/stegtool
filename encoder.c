#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   unsigned int blue;
   unsigned int green;
   unsigned int red;
} offset;

typedef uint8_t BYTE;


// function prototypes
void characterFilter(char *input, char* output);
void offsetCalculator(char *input, offset *output);

int main(void)
{
    char *inText = "Hello.";

    char *filteredText = malloc(sizeof(char) * (strlen(inText) + 1));
    if (filteredText == NULL)
    {
        printf("Memory allocation failure.\n");
        return 1;
    }

    filteredText[0] = '\0';

    characterFilter(inText, filteredText);
    int filteredLength = strlen(filteredText);

    offset *offsetArray = malloc(sizeof(offset) * filteredLength);
    if (offsetArray == NULL)
    {
       printf("Memory allocation failure.\n");
       return 1;
    }

    offsetCalculator(filteredText, offsetArray);

    for (int i = 0; i < filteredLength; i++)
    {
        printf("(%i, %i, %i) ", offsetArray[i].blue, offsetArray[i].green, offsetArray[i].red);
    }
    printf("\n");





    free(filteredText);
    free(offsetArray);
    return 0;
}

void characterFilter(char *input, char *output)
{
    /* This fuction strips down the input string to a
     *reduced set of digits, upper case letters and a few
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

void offsetCalculator(char *input, offset *output)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            output[i].red = input[i] - 'A';
        }
        else if (input[i] >= '0' && input[i] <= '9')
        {
            char buff[] = {' ', '\0'};
            buff[0] = input[i];
            output[i].green = atoi(buff) + 1;
        }
        else if (input[i] == ' ')
        {
            output[i].blue = 1;
        }
        else if (input[i] == '.')
        {
            output[i].blue = 2;
        }
        else
            output[i].blue = 3;
    }
}
