#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avgColor;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgColor = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avgColor;
            image[i][j].rgbtGreen = avgColor;
            image[i][j].rgbtBlue = avgColor;
        }
    }
    return;
}
//
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaBlue;
    float sepiaGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}
//
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int a = width - 1, b = 0;
        while (b < a)
        {
            int tempR, tempG, tempB;
            tempR = image[i][b].rgbtRed;
            image[i][b].rgbtRed = image[i][a].rgbtRed;
            image[i][a].rgbtRed = tempR;
            tempG = image[i][b].rgbtGreen;
            image[i][b].rgbtGreen = image[i][a].rgbtGreen;
            image[i][a].rgbtGreen = tempG;
            tempB = image[i][b].rgbtBlue;
            image[i][b].rgbtBlue = image[i][a].rgbtBlue;
            image[i][a].rgbtBlue = tempB;
            a--;
            b++;
        }
    }
    return;
}
//
//calculates and returns the Average red color from a 3x3 matrix of pixels
float getAvgColorR(int h, int w, int R[h][w], int y, int x)
{
    float avgColor = 0;
    //top left edge
    if (y == 0 && x == 0)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += R[i][j];
            }
        }
        avgColor /= 4;
    }
    //top-right edge
    else if (y == 0 && x == w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += R[i][j - 1];
            }
        }
        avgColor /= 4;
    }
    //bottom-left edge
    else if (y == h - 1 && x == 0)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += R[i - 1][j];
            }
        }
        avgColor /= 4;
    }
    //bottom-right edge
    else if (y == h - 1 && x == w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += R[i - 1][j - 1];
            }
        }
        avgColor /= 4;
    }
    //if pixel is positioned on top side of image excluding edges
    else if (y == 0 && x > 0 && x < w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += R[i][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on right side of image excluding edges
    else if (x == w - 1 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += R[i - 1][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on bottom side of image exluding edges
    else if (y == h - 1 && x > 0 && x < w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += R[i - 1][j - 1];
            }
        }
        avgColor /= 6;
    }
    else if (x == 0 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += R[i - 1][j];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned not on an edge nor side of image
    else if (x > 0 && x < w - 1 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += R[i - 1][j - 1];
            }
        }
        avgColor /= 9;
    }
    return avgColor;
}
//
//calculates and returns the Average green color from a 3x3 matrix of pixels
float getAvgColorG(int h, int w, int G[h][w], int y, int x)
{
    float avgColor = 0;
    //top left edge
    if (y == 0 && x == 0)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += G[i][j];
            }
        }
        avgColor /= 4;
    }
    //top-right edge
    else if (y == 0 && x == w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += G[i][j - 1];
            }
        }
        avgColor /= 4;
    }
    //bottom-left edge
    else if (y == h - 1 && x == 0)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += G[i - 1][j];
            }
        }
        avgColor /= 4;
    }
    //bottom-right edge
    else if (y == h - 1 && x == w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += G[i - 1][j - 1];
            }
        }
        avgColor /= 4;
    }
    //if pixel is positioned on top side of image excluding edges
    else if (y == 0 && x > 0 && x < w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += G[i][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on right side of image excluding edges
    else if (x == w - 1 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += G[i - 1][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on bottom side of image exluding edges
    else if (y == h - 1 && x > 0 && x < w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += G[i - 1][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned not on an edge nor side of image
    else if (x == 0 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += G[i - 1][j];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned not on an edge nor side of image
    else if (x > 0 && x < w - 1 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += G[i - 1][j - 1];
            }
        }
        avgColor /= 9;
    }
    return avgColor;
}
//
//calculates and returns the Average blue color from a 3x3 matrix of pixels
float getAvgColorB(int h, int w, int B[h][w], int y, int x)
{
    float avgColor = 0;
    //top left edge
    if (y == 0 && x == 0)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += B[i][j];
            }
        }
        avgColor /= 4;
    }
    //top-right edge
    else if (y == 0 && x == w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += B[i][j - 1];
            }
        }
        avgColor /= 4;
    }
    //bottom-left edge
    else if (y == h - 1 && x == 0)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += B[i - 1][j];
            }
        }
        avgColor /= 4;
    }
    //bottom-right edge
    else if (y == h - 1 && x == w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += B[i - 1][j - 1];
            }
        }
        avgColor /= 4;
    }
    //if pixel is positioned on top side of image excluding edges
    else if (y == 0 && x > 0 && x < w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += B[i][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on right side of image excluding edges
    else if (x == w - 1 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += B[i - 1][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on bottom side of image exluding edges
    else if (y == h - 1 && x > 0 && x < w - 1)
    {
        for (int i = y; i < y + 2; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += B[i - 1][j - 1];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned on left side of image excluding edges
    else if (x == 0 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 2; j++)
            {
                avgColor += B[i - 1][j];
            }
        }
        avgColor /= 6;
    }
    //if pixel is positioned not on an edge nor side of image
    else if (x > 0 && x < w - 1 && y > 0 && y < h - 1)
    {
        for (int i = y; i < y + 3; i++)
        {
            for (int j = x; j < x + 3; j++)
            {
                avgColor += B[i - 1][j - 1];
            }
        }
        avgColor /= 9;
    }
    return avgColor;
}
//
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //makes a copy of image and also 3 2d arrays for each color
    RGBTRIPLE imageCopy[height][width];
    int R[height][width];
    int G[height][width];
    int B[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //assign rgb values to each 2d array
            imageCopy[i][j] = image[i][j];
            R[i][j] = imageCopy[i][j].rgbtRed;
            G[i][j] = imageCopy[i][j].rgbtGreen;
            B[i][j] = imageCopy[i][j].rgbtBlue;
        }
    }
    float avgR = 0, avgG = 0, avgB = 0;
    //iterates through each pixel and adds blur effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Get red color and rewrites it
            avgR = round(getAvgColorR(height, width, R, i, j));
            //asign to pixel
            image[i][j].rgbtRed = avgR;
            //get green color rewrites it
            avgG = round(getAvgColorG(height, width, G, i, j));
            //assign to pixel
            image[i][j].rgbtGreen = avgG;
            //get blue color and rewrites it
            avgB = round(getAvgColorB(height, width, B, i, j));
            //assign to pixel
            image[i][j].rgbtBlue = avgB;
        }
    }
    return;
}