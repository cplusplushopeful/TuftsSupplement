import cs50


def main():
    
    number = cs50.get_int("Number: ")
    number = str(number)
    if (checksum(number)):
        if(len(number) == 13):
            if(mastercard(number) == True):
                print("MASTERCARD\n")
            else:
                print("INVALID\n")
        elif(len(number) == 16):
            if(visa(number) == True):
                print("VISA\n")
            elif(mastercard(number) == True):
                print("MASTERCARD\n")
            else:
                print("INVALID\n")
        elif(len(number) == 15):
            if(amex(number) == True):
                print("AMEX\n")
            else:
                print("INVALID\n")
    else:
        print("INVALID\n")
    
# Checks if the sum follow parameters


def checksum(digits):
    total = 0
    j = 0
    for i in range(1, len(digits), 2):
        j = 2 * int(digits[len(digits) - 1 - i])
        if(j > 9):
            total += (j % 10) + int((j / 10))
        else:
            total += j
    for i in range(0, len(digits), 2):
        total += int(digits[len(digits) - 1 - i])
    if ((total % 10) == 0):
        return True
        
# Checks if mastercard


def mastercard(key):
    firstTwo = key[0] + key[1]
    firstTwo = int(firstTwo)
    if(51 <= firstTwo <= 55):
        return True
    else:
        return False
        
# Checks if AMEX card


def amex(key):
    firstTwo = key[0] + key[1]
    print(firstTwo)
    if((firstTwo == "34") or (firstTwo == "37")):
        return True
    else:
        return False

# Checks if visa card


def visa(key):
    first = key[0]
    if (first == "4"):
        return True
    else:
        return False


main()
