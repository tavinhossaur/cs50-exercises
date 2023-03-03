#include <stdio.h>
#include <cs50.h>

// Prototypes
int checksum(long n);

int main()
{
    string text = "This card is";
    
    // Gets the credit card number and checksums it
    long card = get_long("Insert the credit card number: ");
    switch (checksum(card))
    {
        // The case corresponds to the leftmost digit of the credit card number
        case 3:
            printf("%s AMEX\n", text);
            break;
        case 4:
            printf("%s VISA\n", text);
            break;
        case 5:
            printf("%s MASTERCARD\n", text);
            break;
        default:
            printf("%s INVALID\n", text);
            break;
    }
}

// Encapsulated method
int checksum(long n)
{
    // Creating variables
    long number = n;
    int sum = 0;
    
    // Separes the righmost digit
    sum = number % 10;
    // Chop the rightmost digit from the full card number
    number = number / 10;      
    
    while(number)
    {
        // Doubles the righmost digit
        int temp = (number % 10) * 2;
        
        // Check if the double result returned a 2 digit value and 
        if (temp > 9) temp -= 9;
    
        // Add digits to the sum and chops it
        sum += temp;
        number = number / 10;
        temp = number % 10;
        sum += temp;
        number = number / 10;
    }
    
    // Gets leftmost digit
    while (n > 10) n = n / 10;

    // Invalid card
    if (sum % 10) return -1;

    // Returns leftmost digit
    return n;                          
}