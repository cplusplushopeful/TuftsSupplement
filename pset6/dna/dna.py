import csv
import sys


def main():
    # Creating variables
    anotherList = []
    fullList = []
    finalName = ""

    # Error checking input
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Opening files and extracting information
    with open(sys.argv[1]) as file:
        reader = csv.reader(file)
        for row in reader:
            fullList.append(row)
    with open(sys.argv[2]) as file2:
        dnasequence = file2.read()

    for i in range(1, len(fullList[0])):

        # Calls a function using STR and DNA sequences as parameters, adds the return value to a list
        # this return value contains the STR numbers for the mystery sequence in question, which allows
        # for comparison
        anotherList.append(findsequence(fullList[0][i], dnasequence))

    # Compares the list created in line 28 to each individual in the given CSV file
    for i in range(1, len(fullList)):
        count = 0
        for j in range(len(fullList[0]) - 1):
            if(anotherList[j] == int(fullList[i][j + 1])):
                count += 1
            if(count == len(fullList[0]) - 1):
                finalName = fullList[i][0]

    # Error checking
    if finalName == "":
        finalName = "No match"

    print(finalName)


def findsequence(STR, sequence):

    # Creating variables
    noStep = len(STR)
    count = 0
    maximum = 0

    # Iterates through entire sequence and identifies the
    # maximum number of short tandem repeats
    for i in range(0, len(sequence)):
        current = sequence[i: i + noStep]
        if(current == STR):
            count += 1

            # Once the program reaches a substring that it identifies as the same
            # it begins a loop to check for the number of consecutive repeats
            while (sequence[i: i + noStep] == sequence[i + noStep: i + (2 * noStep)]):
                count += 1
                i += noStep
            if (count > maximum):
                maximum = count
        else:
            count = 0
    return maximum


main()
