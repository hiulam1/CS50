#include <cs50.h>
#include <stdio.h>
#include <math.h>

int add_digits(long number, long i, int multiple);
string checksum(long number);
string checkcard(long number);

int main(void)
{
    // get card number
    long number = get_long("Number: ");
    //check number if it is a valid number, if so which credit card is it
    printf("%s", checksum(number));
}

string checksum(long number)
{
    //add_digits function to add digits with the last argument being the multiplier and the second argument
    int sum = add_digits(number, 100, 2) + add_digits(number, 10, 1);
    if (sum % 10 == 0)
    {
        return checkcard(number);
    }
    else
    {
        return ("INVALID\n");
    }

}

int add_digits(long number, long last, int multiple)
{
    int remainder = 0;
    int sum = 0;
    for (long x = last; x <= number * 10; x *= 100)
    {
        long j = x / 10;
        remainder = ((number % x) / j) * multiple;
        if (remainder >= 10)
        {
            remainder = remainder % 10 + remainder / 10;
        }
        sum += remainder;
    }
    return sum;
}

string checkcard(long number)
{
    if ((((long)(pow(10, 13) * 35)) <= number && number < ((long)(pow(10, 13) * 36))) || (((long)(pow(10, 13) * 37)) <=  number
            && number < ((long)(pow(10, 13) * 38))))
    {
        return ("AMEX\n");
    }
    else if ((long)(pow(10, 14) * 51) <=  number && number < (long)(pow(10, 14) * 56))
    {
        return ("MASTERCARD\n");
    }
    else if ((((long)(pow(10, 12) * 4)) <=  number && number < ((long)(pow(10, 12) * 5))) || (((long)(pow(10, 15) * 4)) <=  number
             && number < ((long)(pow(10, 15) * 5))))
    {
        return ("VISA\n");
    }
    else
    {
        return ("INVALID\n");
    }
}