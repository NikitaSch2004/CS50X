#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //integers used in the program
    int j = 0;
    int n;
    //user inputs a number between 1-8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    //main part where empty spaces and # are aranged into a pyramid
    for (int i = 0; i < n; i++)
    {
        for (j = n - 1; j > i; j--)
        {
            //outputs the empty spaces
            printf(" ");
        }
        for (int k = 0; k <= j; k++)
        {
            //outpus # in pyramid form
            printf("#");
        }
        //outupts the height number of the pyramid
        printf("\n");
    }

}

