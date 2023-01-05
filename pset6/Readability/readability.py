import cs50


def main():
    
    # Gets the inputted lines from the user
    
    inputtedText = cs50.get_string("Text: ")
    numberOfLetters = 0
    numberOfWords = 1
    numberOfSentences = 0
    
    # Iterates through the text and finds the number of words/letters/sentences
    
    for i in range(len(inputtedText)):
        if(inputtedText[i].isalpha()):
            numberOfLetters += 1
        elif(inputtedText[i] == ' '):
            numberOfWords += 1
        elif((inputtedText[i] == '!') or (inputtedText[i] == '?') or (inputtedText[i] == '.')):
            numberOfSentences += 1
            
    L = (numberOfLetters / numberOfWords) * 100
    S = (numberOfSentences / numberOfWords) * 100

    # Calculates the index throught the given formula
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Uses index to determine grade level
    
    if (index < 1):
        print("Before Grade 1\n")

    elif (index > 16):
        print("Grade 16+\n")
    
    else:
        print("Grade " + str(index))


main()