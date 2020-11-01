#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, a = width; j < a; j++)
        {
            float avg = ((round(image[i][j].rgbtRed) + round(image[i][j].rgbtBlue) + round(image[i][j].rgbtGreen))/3);
            avg = round(avg);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
        
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, a = width; j < a; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 *image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 *image[i][j].rgbtBlue);
            if (sepiaRed < 256)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            
            else
            {
                image[i][j].rgbtRed = 255;
            }
            
            if (sepiaGreen < 256)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            
            if (sepiaBlue < 256)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, a = (width/2); j < a; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, a = width; j < a; j++)
        {
            int Red = 0;
            int Blue = 0;
            int Green = 0;
            int DownRight = 1;
            int UpLeft = -1;
            int adjpixels = 0;
            temp[i][j] = image[i][j];
            
            //Check if top left corner
            if (i + UpLeft < 0 && j + UpLeft < 0)
            {
                for (int c = 0; c < 2; c++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }
            }
            
            //Check if top Right Corner
            else if (i + UpLeft < 0 && j + DownRight > width - 1)
            {
                for (int c = 0; c < 2; c++)
                {
                    for (int b = 0; b > -2; b--)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            
            //Check if bottom right corner
            else if (i + DownRight > height - 1 && j + DownRight > width - 1)
            {
                for (int c = 0; c > -2; c--)
                {
                    for (int b = 0; b > -2; b--)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            
             //Check if bottom Left Corner
            else if (i + DownRight > height - 1 && j + UpLeft < 0)
            {
                for (int c = 0 ; c > -2; c--)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            
            //Check if on top edge
            else if (i + UpLeft < 0)
            {
                for (int c = 0; c < 2; c++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            
            //Check if on left edge
            else if (j + UpLeft < 0)
            {
                for (int c = -1; c < 2; c++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }
            }
            
            //Check if on bottom edge
            else if (i + DownRight > height - 1)
            {
                for (int c = 0; c > -2; c--)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            
            
            //Check if on right edge
            else if (j + DownRight > width - 1)
            {
                for (int c = -1; c < 2; c++)
                {
                    for (int b = 0; b > -2; b--)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            
            //If not touching any edge
            else
            {
                for (int c = -1; c < 2; c++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        Red += image[i + c][j + b].rgbtRed;
                        Blue += image[i + c][j + b].rgbtBlue;
                        Green += image[i + c][j + b].rgbtGreen;
                        adjpixels++;
                    }
                }    
            }
            temp[i][j].rgbtRed = round(Red / adjpixels);
            temp[i][j].rgbtBlue = round(Blue / adjpixels);
            temp[i][j].rgbtGreen = round(Green / adjpixels);
        }
    }
    
    for (int h = 0; h < height - 1; h++)
    {
        for (int w = 0; w < width - 1; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
        }
    }
    return;
}
