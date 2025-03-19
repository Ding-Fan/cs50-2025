#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over the rows(height)
    for (int y = 0; y < height; y++)
    {
        // iterate over the columns(width)
        for (int x = 0; x < width; x++)
        {
            // In fact, to ensure each pixel of the new image
            // still has the same general brightness or darkness
            // as the old image, we can take the average
            // of the red, green, and blue values to determine
            // what shade of grey to make the new pixel.

            // from the image, get the pixel at y height and x width
            RGBTRIPLE *pixel = &image[y][x];

            // get the average of RGB values
            int avg = round(
                (
                    (*pixel).rgbtRed +
                    (*pixel).rgbtGreen +
                    (*pixel).rgbtBlue
                ) / 3.0
            );

            // turn the pixel to grayscale
            (*pixel).rgbtRed = avg;
            (*pixel).rgbtGreen = avg;
            (*pixel).rgbtBlue = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // placing the original image in front of a mirror. So any pixels on the left side of the image should end up on the right, and vice versa.
    //
    // iterate over the rows(height)
    for (int y = 0; y < height; y++)
    {
        // iterate over the columns(width)
        // because reflect vertically
        // stop at the middle of the image
        // reverse the row of pixels array in place
        for (int x = 0; x < width / 2; x++)
        {
            // Think about the shallow copy/deep copy on struct here
            // Does this work? Why?
            RGBTRIPLE temp = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // box blur,” which works by
    // taking each pixel and, for each color value,
    // giving it a new value by
    // averaging the color values of neighboring pixels.
    // 3 x 3 maybe

    // create a new image to store the new pixel values
    RGBTRIPLE new_image[height][width];

    // iterate over the rows(height)
    for (int y = 0; y < height; y++)
    {
        // iterate over the columns(width)
        for (int x = 0; x < width; x++)
        {
            int box_sum_red = 0;
            int box_sum_green = 0;
            int box_sum_blue = 0;
            int count = 0;

            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if (y + i < 0 || y + i >= height || x + j < 0 || x + j >= width)
                    {
                        continue;
                    }
                    count++;
                    box_sum_red += image[y + i][x + j].rgbtRed;
                    box_sum_green += image[y + i][x + j].rgbtGreen;
                    box_sum_blue += image[y + i][x + j].rgbtBlue;
                }
            }


            new_image[y][x].rgbtRed = round(box_sum_red /(float) count);
            new_image[y][x].rgbtGreen = round(box_sum_green /(float) count);
            new_image[y][x].rgbtBlue = round(box_sum_blue /(float) count);
        }
    }

    // alter the original image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = new_image[y][x];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
