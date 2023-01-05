#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[]){
    if(argc == 2){
        string k = argv[1];
        bool isADigit = false;
        for(int i = 0; i < strlen(k); i++)
        {
            char j = k[i];
            if(isdigit(j))
            {
                isADigit = true;
            }
            else
            {
                printf("Usage caesar");
                return 1;
            }
        }
    }
    else{
        printf("No");
    }
    
}




