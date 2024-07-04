#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string pText = "";
    int k;
    //command line arguments
    if (!(argc == 2))
    {

        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            //checks and converts the argv[1] into an integer
            k = atoi(argv[1]);
            if (k < 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    //prompts the user for a string to be encrypted
    pText = get_string("plaintext:  ");
    //encryption part by Caesar's formu;a
    printf("ciphertext: ");
    for (int j = 0; j < strlen(pText); j++)
    {
        //checks for upper alphabetical letters and encrypts them
        if (isalpha(pText[j]) && isupper(pText[j]))
        {
            printf("%c", (((pText[j] - 65) + k) % 26) + 65);
        }
        //checks for lower alphabetical letters and encrypts them
        else if (isalpha(pText[j]) && islower(pText[j]))
        {
            printf("%c", (((pText[j] - 97) + k) % 26) + 97);
        }
        //prints everything that is not a letter
        else
        {
            printf("%c", pText[j]);
        }
    }
    printf("\n");
}