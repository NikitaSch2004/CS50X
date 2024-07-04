#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = 0;
            //get average of rgb color
            avg += round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            //assign to red pixel
            image[i][j].rgbtRed = avg;
            //assing to green pixel
            image[i][j].rgbtGreen = avg;
            //assing to blue pixel
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int a = width - 1, b = 0;
        while (b < a)
        {
            //temporary variable used to change the colors of pixels from left to right
            int temp;
            //change values of red pixel from left to right
            temp = image[i][b].rgbtRed;
            image[i][b].rgbtRed = image[i][a].rgbtRed;
            image[i][a].rgbtRed = temp;
            //change values of green pixel from left to right
            temp = image[i][b].rgbtGreen;
            image[i][b].rgbtGreen = image[i][a].rgbtGreen;
            image[i][a].rgbtGreen = temp;
            //change values of blue pixel from left to right
            temp = image[i][b].rgbtBlue;
            image[i][b].rgbtBlue = image[i][a].rgbtBlue;
            image[i][a].rgbtBlue = temp;
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
//funcion for getting the value and see if there is an edge or not
int getValue(int h, int w, RGBTRIPLE imageCopy[h][w], int y, int x, int Gy[3][3], int Gx[3][3], char s)
{
    float value = 0, Gx_value = 0, Gy_value = 0;
    switch (s)
    {
        //gets values for red Y and X axis
        case 'R':
        {
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if ((y + i >= 0 && x + j >= 0) && (y + i < h && x + j < w))
                    {
                        Gx_value += imageCopy[y + i][x + j].rgbtRed * Gx[i + 1][j + 1];
                        Gy_value += imageCopy[y + i][x + j].rgbtRed * Gy[i + 1][j + 1];
                    }
                }
            }
            value = sqrt(pow(Gy_value, 2) + pow(Gx_value, 2));
            if (value > 255)
            {
                return 255;
            }
            else if (value < 0)
            {
                return 0;
            }
            else if (value >= 0 && value <= 255)
            {
                return round(value);
            }
            break;
        }
        //gets values for green Y and X axis
        case 'G':
        {
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if ((y + i >= 0 && x + j >= 0) && (y + i < h && x + j < w))
                    {
                        Gx_value += imageCopy[y + i][x + j].rgbtGreen * Gx[i + 1][j + 1];
                        Gy_value += imageCopy[y + i][x + j].rgbtGreen * Gy[i + 1][j + 1];
                    }
                }
            }
            value = sqrt(pow(Gy_value, 2) + pow(Gx_value, 2));
            if (value > 255)
            {
                return 255;
            }
            else if (value < 0)
            {
                return 0;
            }
            else if (value >= 0 && value <= 255)
            {
                return round(value);
            }
            return 0;
            break;
        }
//gets values for blue Y and X axis
        case 'B':
        {
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if ((y + i >= 0 && x + j >= 0) && (y + i < h && x + j < w))
                    {
                        Gx_value += imageCopy[y + i][x + j].rgbtBlue * Gx[i + 1][j + 1];
                        Gy_value += imageCopy[y + i][x + j].rgbtBlue * Gy[i + 1][j + 1];
                    }
                }
            }
            value = sqrt(pow(Gy_value, 2) + pow(Gx_value, 2));
            if (value > 255)
            {
                return 255;
            }
            else if (value < 0)
            {
                return 0;
            }
            else if (value >= 0 && value <= 255)
            {
                return round(value);
            }
            return 0;
            break;
        }
    }
    return 0;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ImageCopy[height][width];
    int Gx_edge[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_edge[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //copy the image in a temporary array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ImageCopy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getValue(height, width, ImageCopy, i, j, Gy_edge, Gx_edge, 'R');
            image[i][j].rgbtGreen = getValue(height, width, ImageCopy, i, j, Gy_edge, Gx_edge, 'G');
            image[i][j].rgbtBlue = getValue(height, width, ImageCopy, i, j, Gy_edge, Gx_edge, 'B');
        }
    }
    return;
}