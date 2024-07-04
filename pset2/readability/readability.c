#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int x;
    double L, S, grade;
    int l = 0;
    double w = 0;
    int s = 0;
    //inputs the user for Text:
    string input = get_string("Text: ");
    for (int i = 0; i < strlen(input) ; i++)
    {
        //sorts out the letters from the string
        if (isalpha(input[i]))
        {
            l++;
        }
        //calculates the number of sentences in string
        else if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            s++;
        }
        //calculates the number of words in the string
        else if (input[i] == ' ')
        {
            w++;
        }
    }
    w++;
    //average letters per 100 words
    L = (l * 100) / w;
    //average sentences per 100 words
    S = (s * 100) / w;
    //determines U.S grade reading level by Coleman-Liau formula
    grade = round(0.0588 * L - 0.296 * S - 15.8);
    x = grade;
    //outputs the grade
    if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (x > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", x);
    }
}