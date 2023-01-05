#include <cs50.h>
#include <stdio.h>




int main(void)
{
    int rowsInput;
    do{
        rowsInput = get_int("How many rows would you like to have? ");
    }
    while(rowsInput < 1 || rowsInput > 8);
    
    for(int i = 1; i <= rowsInput; i++){
    
        for(int j = 1; j <= rowsInput - i; j++){
            printf(" ");
        }    
    
        for(int k = 1; k <= i; k++){
            printf("#");
        }
    
        printf("\n");
    }

}