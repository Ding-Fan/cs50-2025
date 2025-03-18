#include "helpers.h"
#include <math.h>

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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
