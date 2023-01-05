#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Usage key in case someone does not follow directions
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //Declaring variables
    FILE *memoryCard = fopen(argv[1], "r");
    BYTE buffer[512];
    int numberOfJpegs = 0;
    char filename[8];
    FILE *img = NULL;
    
    //Use while loop so that we can use the return value of the fread function
    
    while (fread(buffer, sizeof(BYTE), 512, memoryCard) == 512)
    {
        //Checks if it is the start to a new image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Checks if it is the first image
            if (numberOfJpegs == 0)
            {
                sprintf(filename, "%03i.jpg", numberOfJpegs);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                numberOfJpegs++;
            }
            //If it is not the first image
            else if (numberOfJpegs > 0)
            {
            
                //Closes the previous image file if it is not the first image in the set before creating another one
                fclose(img);
                sprintf(filename, "%03i.jpg", numberOfJpegs);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                numberOfJpegs++;
        
            }
        }
        //Continues writing in case it is not the start of a new file
        else if (numberOfJpegs > 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }
    }
    //Closes any remaining opened files
    fclose(memoryCard);
    fclose(img);
}