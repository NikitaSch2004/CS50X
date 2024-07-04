#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string pText = "";
    char c[26];
    //command line arguments
    if (!(argc == 2))
    {

        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Usage : key must contain 26 characters.\n");
        return 1;
    }
    else if (strlen(argv[1]) == 26)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    //for loop to write the key in a char array
    for (int x = 0; x < 26; x++)
    {
        c[x] = argv[1][x];
        //check for duplicate characters in key
        if (c[x] == c[x - 1])
        {
            printf("Usage: duplicate characters in key\n");
            return 1;
        }
    }
    //prompts the user for a string to be encrypted
    pText = get_string("plaintext:  ");
    //encryption
    printf("ciphertext: ");
    for (int j = 0; j < strlen(pText); j++)
    {
        //checks for upper alphabetical letters and encrypts them
        if (isalpha(pText[j]) && isupper(pText[j]))
        {
            printf("%c", toupper(c[pText[j] % 65]));
        }
        //checks for lower alphabetical letters and encrypts them
        else if (isalpha(pText[j]) && islower(pText[j]))
        {
            printf("%c", tolower(c[pText[j] % 97]));
        }
        //prints everything that is not a letter
        else
        {
            printf("%c", pText[j]);
        }
    }
    printf("\n");
}