#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int n = 0; n < height; n++)
    {
        for (int i = 0; i < width; i++)
        {
            float average = ((image[n][i].rgbtBlue + image[n][i].rgbtRed + image[n][i].rgbtGreen) / 3.0) + 0.5;
            image[n][i].rgbtBlue = average;
            image[n][i].rgbtRed = average;
            image[n][i].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int n = 0; n < height; n++)
    {
        for (int i = 0; i < width; i++)
        {
            float sepiaRed = (.393 * image[n][i].rgbtRed + .769 * image[n][i].rgbtGreen + .189 * image[n][i].rgbtBlue) + 0.5;
            float sepiaGreen = (.349 * image[n][i].rgbtRed + .686 * image[n][i].rgbtGreen + .168 * image[n][i].rgbtBlue) + 0.5;
            float sepiaBlue = (.272 * image[n][i].rgbtRed + .534 * image[n][i].rgbtGreen + .131 * image[n][i].rgbtBlue) + 0.5;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[n][i].rgbtBlue = sepiaBlue;
            image[n][i].rgbtRed = sepiaRed;
            image[n][i].rgbtGreen = sepiaGreen;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempList[height][width]; 

    //Temporary list to get unaffected values from
    for (int n = 0; n < height; n++)
    {
        for (int i = 0; i < width; i++)
        {
            tempList[n][i] = image[n][i];
        }
    }
    
    //Copies the values from the unaffected list to the reflected area
    for (int n = 0; n < height; n++)
    {
        for (int i = 0; i < width; i++)
        {
            image[n][i] = tempList[n][(width - 1 - i)];
        }
    }
    return;
}



void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE tempList[height][width]; 


    //Creates unaffected list that will be used to average values
    for (int n = 0; n < height; n++)
    {
        for (int i = 0; i < width; i++)
        {
            tempList[n][i] = image[n][i];
        }
    }
    
    
    //Creats the averaged rgb values
    for (int n = 0; n < height; n++)
    {
        for (int i = 0; i < width; i++)
        {   
            
            float averageRed = 0;
            float averageGreen = 0;
            float averageBlue = 0;
            int numberOfSpaces = 0;
            for (int j = -1; j < 2; j++)
            {
                if (n + j >= 0 && n + j < height)
                {
                    for (int k = -1; k < 2; k++)
                    {
                        if (i + k >= 0 && i + k < width)
                        {
                            averageRed += tempList[n + j][i + k].rgbtRed;
                            averageBlue += tempList[n + j][i + k].rgbtBlue;
                            averageGreen += tempList[n + j][i + k].rgbtGreen;
                            numberOfSpaces++;

                        }    
                    }
                }
            }
            
            
            image[n][i].rgbtRed = round(averageRed / numberOfSpaces);
            image[n][i].rgbtBlue = round(averageBlue / numberOfSpaces);
            image[n][i].rgbtGreen = round(averageGreen / numberOfSpaces);
            
    
        }
        
    }

    return;
}
