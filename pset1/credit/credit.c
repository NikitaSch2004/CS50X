#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{   
    int len;
    int total_digits = 0;
    int odd = 0;
    int even = 0;
    int v = 0;
    long Card;
    bool validation;
    
// Prompt User for Credit Card Number
    do
    {
        Card = get_long("Number: ");
    }
    while (Card < 0);
    long c = Card;
    long l = Card;
    
    //checks the first 2 digits 
    int AMEX = c / pow(10, 13);
    int MASTER = c / pow(10, 14);
    int VISA1 = c / pow(10, 12);
    int VISA2 = c / pow(10, 15);

    //Lunh's algorithm for validating the card
    for (len = 0; l != 0; len++)
    {
        l = l / 10;
    }
    for (int count = 0; c != 0; c /= 10, count++)
    {
        v = c % 10;
        
        if (count % 2 != 0)
        {
            even = v * 2;
            total_digits += even % 10 + even / 10;
        }
        else
        {
            odd += v;
        }
    }
    total_digits += odd;
    
    if (total_digits % 10 != 0)
    {
        validation = false;
    }
    else
    {
        validation = true;
    }
    //output
    if (len == 15 && validation == true && AMEX == 34)
    {
        printf("AMEX\n");
    }
    else if (len == 15 && validation == true && AMEX == 37)
    {
        printf("AMEX\n");
    }
    else if (len == 16 && validation == true && MASTER == 51)
    {
        printf("MASTERCARD\n");
    }
    else if (len == 16 && validation == true && MASTER == 52)
    {
        printf("MASTERCARD\n");
    }
    else if (len == 16 && validation == true && MASTER == 53)
    {
        printf("MASTERCARD\n");
    }
    else if (len == 16 && validation == true && MASTER == 54)
    {
        printf("MASTERCARD\n");
    }
    else if (len == 16 && validation == true && MASTER == 55)
    {
        printf("MASTERCARD\n");
    }
    else if (len == 13 && validation == true && VISA1 == 4)
    {
        printf("VISA\n");
    }
    else if (len == 16 && validation == true && VISA2 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

