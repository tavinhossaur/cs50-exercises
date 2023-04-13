#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through the height
    for (int h = 0; h < height; h++)
    {
        // Iterating through the width
        for (int w = 0; w < width; w++)
        {
            // Gets all rgb values from the pixel and calculates the average
            int averageRgb = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3;

            // Apply the average value to the pixel
            image[h][w].rgbtRed = averageRgb;
            image[h][w].rgbtGreen = averageRgb;
            image[h][w].rgbtBlue = averageRgb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary image
    RGBTRIPLE temp;

    // Iterating through the height
    for (int h = 0; h < height; h++)
    {
        // Iterating through the half of the width
        for (int w = 0; w < width / 2; w++)
        {
            // Assigning the original image to the temporary one
            temp = image[h][w];

            // Changing the positions of the pixels
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Maximum radius for the boxblur
    int radius = 3;

    // Iterating through the height
    for (int h = 0; h < height; h++)
    {
        // Iterating through the width
        for (int w = 0; w < width; w++)
        {
            // RGB variables to get the total amount of every color of all pixels
            float red = 0, green = 0, blue = 0;

            // Counter to track the amount of pixels that are in the box
            // when the iteration gets to the border of the image, it will not get all 9 pixels
            // around it, so it's important to keep this value as a variable, not a constant.
            int count = 0;

            // Box height (3px)
            for (int bh = -radius; bh <= radius; bh++)
            {
                // Box width (3px)
                for (int bw = -radius; bw <= radius; bw++)
                {
                    // New height and width
                    int nh = h + bh;
                    int nw = w + bw;

                    // Check if we are in bounds of the image
                    if (nh >= 0 && nw >= 0 && nh < height && nw < width)
                    {
                        // Adding up to the RGB values
                        red += image[nh][nw].rgbtRed;
                        green += image[nh][nw].rgbtGreen;
                        blue += image[nh][nw].rgbtBlue;

                        // Tracking the amount of pixels
                        count++;
                    }
                }
            }

            // Dividing the amount of rgb by the amount of pixels
            red /= count;
            green /= count;
            blue /= count;

            // Changing the values with the new values to create a blur version of the image
            image[h][w].rgbtRed = red;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtBlue = blue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterating through the height
    for (int h = 1; h < height; h++)
    {
        // Iterating through the width
        for (int w = 1; w < width-1; w++)
        {
            int gxRed = 0, gyRed = 0, gxGreen = 0, gyGreen = 0, gxBlue = 0, gyBlue = 0;

            for (int nh = -1; nh <= 1; nh++)
            {
                for (int nw = -1; nw <= 1; nw++)
                {
                    if (h + nh < 0 || h + nh > height - 1) continue;
                    if (w + nw < 0 || w + nw > width - 1) continue;

                    gxBlue += image[h + nh][w + nw].rgbtBlue * gx[nh + 1][nw + 1];
                    gyBlue += image[h + nh][w + nw].rgbtBlue * gy[nh + 1][nw + 1];

                    gxGreen += image[h + nh][w + nw].rgbtGreen * gx[nh + 1][nw + 1];
                    gyGreen += image[h + nh][w + nw].rgbtGreen * gy[nh + 1][nw + 1];

                    gxRed += image[h + nh][w + nw].rgbtRed * gx[nh + 1][nw + 1];
                    gyRed += image[h + nh][w + nw].rgbtRed * gy[nh + 1][nw + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            temp[h][w].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[h][w].rgbtGreen = (green > 255) ? 255 : green;
            temp[h][w].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Apply symmetry horizontally
void symmetry(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through the height
    for (int h = 0; h < height; h++)
    {
        // Iterating through the width
        for (int w = 0; w < width/2; w++)
        {
            // Replicating the rgbs in the image until it gets on the middle
            image[h][w].rgbtRed = image[h][width-w].rgbtRed;
            image[h][w].rgbtGreen = image[h][width-w].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width-w].rgbtBlue;
        }
    }
    return;
}
