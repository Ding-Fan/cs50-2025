#include <cs50.h>
#include <stdio.h>

void make_pyramid();
void make_pyramid_core(int height);
void make_pyramid_row(int height, int rowNumber);

char space = ' ';

int main()
{
    make_pyramid();
    return 0;
}

void make_pyramid()
{
    int height;
    do
    {
        height = get_int("Height(should be between 1 and 8): ");
    }
    while (height < 1 || height > 8);

    make_pyramid_core(height);
}

void make_pyramid_row(int height, int rowNumber)
{
    // right aligned
    int paddingNumber = height - rowNumber;
    for (int columnNumber = 1; columnNumber <= height; columnNumber++)
    {
        if (paddingNumber >= columnNumber)
        {
            printf("%c", space);
        }
        else
        {
            printf("#");
        }
    }

    printf("%c%c", space, space); // two spaces gap

    // left aligned
    for (int columnNumber = 0; columnNumber < rowNumber; columnNumber++)
    {
        printf("#");
    }

    printf("\n");
}

void make_pyramid_core(int height)
{
    for (int rowNumber = 1; rowNumber <= height; rowNumber++)
    {
        make_pyramid_row(height, rowNumber);
    }
}
