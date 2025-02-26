#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{
    // two ways to manipulate the card number
    // 1. store it in a string, then use index [] to get the digits
    // 2. store it in a long, then use modulo % to get the digits
    // I chose the second way

    // get the number, store it in a long
    long cardNumber = get_long("Number: ");
    long cardNumberCopy = cardNumber;
    // verify the number
    // printf("%li\n", cardNumberCopy);

    // create a array to store the number
    int digits[20];

    // get the last digit
    int i = 0;

    while (cardNumberCopy > 0)
    {
        // get the last digit
        int lastDigit = cardNumberCopy % 10;
        // store the last digit in the array
        digits[i] = lastDigit;
        // remove the last digit
        cardNumberCopy = cardNumberCopy / 10;
        // move to the next digit
        i++;
    }


    // now the i is the length of the card number
    int length = i;

    // print the array
    // for (int j = 0; j < i; j++)
    // {
    //     printf("%i ", digits[j]);
    // }

    // get every other digit, starting with the number’s second-to-last digit
    // multiply them by 2, and add the products’ digits together
    int sum = 0;
    for (int j = 1; j < length; j += 2)
    {
        int digit = digits[j] * 2;
        // if the product is a two-digit number, add its digits together
        if (digit > 9)
        {
            sum += digit % 10; // left digit
            sum += digit / 10; // right digit
        }
        else
        {
            sum += digit;
        }
    }

    // add the sum to the sum of the digits that weren’t multiplied by 2

    for (int j = 0; j < length; j += 2)
    {
        sum += digits[j];
    }

    // check if the last digit of the sum is 0
    if (sum % 10 == 0)
    {

        // American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. 
        //
        // All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem); and all Visa numbers start with 4.


        // check if the card number is valid
        // American Express uses 15-digit numbers, start with 34 or 37
        if (length == 15 && (digits[length - 1] == 3 && (digits[length - 2] == 4 || digits[length - 2] == 7)))
        {
            printf("AMEX\n");
        }
        // MasterCard uses 16-digit numbers, start with 51, 52, 53, 54, or 55
        else if (length == 16 && (digits[length - 1] == 5 && (digits[length - 2] == 1 || digits[length - 2] == 2 || digits[length - 2] == 3 || digits[length - 2] == 4 || digits[length - 2] == 5)))
        {
            printf("MASTERCARD\n");
        }
        // Visa uses 13- and 16-digit numbers, start with 4
        else if ((length == 13 || length == 16) && digits[length - 1] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}