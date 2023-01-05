#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void){
    
    //Gets the inputted lines from the user
    string inputtedText = get_string("Text: ");
    int numberOfLetters = 0;
    int numberOfWords = 1;
    int numberOfSentences = 0;
    
    //Checks the number of words/sentences/letters in the inputted text
    for(int i = 0; i < strlen(inputtedText); i++){
        if(isalpha(inputtedText[i])){
            numberOfLetters++;
        }else if(inputtedText[i] ==  ' '){
            numberOfWords++;
        }else if((inputtedText[i] == '!') || (inputtedText[i] == '?') || (inputtedText[i] == '.')){
            numberOfSentences++;
        }
    }
    
    //Calculates the average number of letters and sentences per 100 words of the same kind of text
    float L = (numberOfLetters / (float) numberOfWords) * 100;
    float S = (numberOfSentences / (float) numberOfWords) * 100;
    
    //Calculates Coleman-Liau index (grade level)
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    //Outputs grade level depending on index value
    if(index < 1){
        printf("Before Grade 1\n");
    }else if(index > 16){
        printf("Grade 16+\n");
    }else{
        printf("Grade %i\n", index);   
    }

}

