#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])

{
    //Checks if user has given the correct input when calling the program
    if (argc == 2)
    
    {
        //Checks if the given key is a number or not
        string k = argv[1];
        bool isADigit = false;
        for (int i = 0; i < strlen(k); i++)
        {
            char j = k[i];
            if (isdigit(j))
            
            {
                isADigit = true;
            }
            else
            {
                //If user has not inputted according to the given format, it will output a usage key
                printf("Usage: ./caesar key");
                return 1;
            }
        }
        //Since key is a string, this converts it to an integer so that math can be done with it
        int key = atoi(k);
        string ciphertext = "";
        string plaintext = get_string("Plaintext: ");
        char cipheredCharacter;
        printf("ciphertext: ");
        //Encryption process
        for (int i = 0; i < strlen(plaintext); i++)
        {
            //Checks if character is an alphabet or alphanumeric/number
            if (isalpha(plaintext[i]))
            {
                //Converts to alphabetic index depending on whether letter is lowercase or uppercase
                if (isupper(plaintext[i]))
                {
                    char reducedPlain = plaintext[i] - 65;
                    cipheredCharacter = (reducedPlain + key) % 26;
                    cipheredCharacter += 65;
                }
                else
                {
                    char reducedPlain = plaintext[i] - 97;
                    cipheredCharacter = (reducedPlain + key) % 26;
                    cipheredCharacter += 97;
                }
                printf("%c", cipheredCharacter);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");

    }
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }
}