#include <string.h>
#include <stdlib.h>

char* strtok(char* s, char* delm)
{
    // Stores the state of string
    static char* input = NULL;
 
    // Initialize the input string
    if (s != NULL)
    {
        input = s;
    }

    // Case for final token
    if (input == NULL)
    {
        return NULL;
    }
 
    // Stores the extracted string
    char* result = (char*)malloc(sizeof(char)*(strlen(input) + 1));
    int i = 0;
 
    // Start extracting string and
    // store it in array
    for (; input[i] != '\0'; i++) 
    {
 
        // If delimiter is not reached
        // then add the current character
        // to result[i]
        if (input[i] != delm[0])
        {
            result[i] = input[i];
        } else 
        {
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }
 
    // Case when loop ends
    result[i] = '\0';
    input = NULL;
 
    // Return the resultant pointer
    // to the string
    return result;
}