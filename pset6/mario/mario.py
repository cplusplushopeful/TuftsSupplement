import cs50


def main():
    
    # Asks for the height from the user
    height = cs50.get_int("Height: ")
    
    # Checks if the height is within the given parameters, otherwise repeats
    if(height < 1 or height > 8):
        main()
    
    # Outputs the pyramid
    for i in range(1, height + 1, 1):
        print((" " * (height - i)) + ("#" * i) + "  " + ("#" * i))
    
    
main()