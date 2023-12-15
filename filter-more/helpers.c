#include "helpers.h"
#include "math.h"
#include "stdio.h"

int calculate_color(int gxcolor, int gycolor);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
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
    // i is height, j is width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumblue = 0;
            int sumgreen = 0;
            int sumred = 0;
            int count = 0;
            for (int n = -1; n < 2; n++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (0 <= i + n && i + n < height && 0 <= j + m && j + m < width)
                    {
                        sumblue += image[i + n][j + m].rgbtBlue;
                        sumgreen += image[i + n][j + m].rgbtGreen;
                        sumred += image[i + n][j + m].rgbtRed;
                        count += 1;
                    }
                }
            }
            temp[i][j].rgbtBlue = round(sumblue / (float) count);
            temp[i][j].rgbtGreen = round(sumgreen / (float) count);
            temp[i][j].rgbtRed = round(sumred / (float) count);
        }
    }

    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = temp[k][l];
        }
    }
    return;
}

typedef struct
{
    int blue;
    int red;
    int green;
} color;

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gxkernel[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gykernel[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    RGBTRIPLE temp[height][width];
    // i is height, j is width, going from row to row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            color gx = {0, 0, 0};
            color gy = {0, 0, 0};

            // n is height and m is row
            int z = 0;
            for (int n = -1; n < 2; n++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (0 <= i + n && i + n < height && 0 <= j + m && j + m < width)
                    {
                        gx.blue += image[i + n][j + m].rgbtBlue * gxkernel[z];
                        gx.green += image[i + n][j + m].rgbtGreen * gxkernel[z];
                        gx.red += image[i + n][j + m].rgbtRed * gxkernel[z];
                        gy.blue += image[i + n][j + m].rgbtBlue * gykernel[z];
                        gy.green += image[i + n][j + m].rgbtGreen * gykernel[z];
                        gy.red += image[i + n][j + m].rgbtRed * gykernel[z];
                    }
                    z++;
                }
            }
            // square root of Gx^2 + Gy^2
            temp[i][j].rgbtBlue = calculate_color(gx.blue, gy.blue);
            temp[i][j].rgbtGreen = calculate_color(gx.green, gy.green);
            temp[i][j].rgbtRed = calculate_color(gx.red, gy.red);
        }
    }

    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = temp[k][l];
        }
    }
    return;
}

int calculate_color(int gxcolor, int gycolor)
{
    return round(fminf(sqrt(pow(gxcolor, 2.0) + pow(gycolor, 2.0)), 255.0));
}
