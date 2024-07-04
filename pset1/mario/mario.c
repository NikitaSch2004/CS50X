#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    //integers used in program
    int z = 2;
    int x = 8;
    int j = 0;
    int n;
    //user inputs the height of the pyramid between 1-8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    //main part where empty spaces and # are arranged into a pyramid
    for (int i = 0; i < n; i++)
    {
        for (j = n - 1; j > i; j--)
        {
            //outputs empty spaces
            printf(" ");
        }
        for (int k = 0; k <= j; k++)
        {
            //outputs # in form of a pyramid
            printf("#");
        }
        for (int c = 0; c < z; c++)
        {
            //outputs empty spaces between the two pyramids
            printf(" ");
        }

        for (int b = 0; b < j + 1; b++)
        {
            //outputs 2nd # pyramid
            printf("#");
        }
        //outputs the height of the piramid
        printf("\n");
    }
}