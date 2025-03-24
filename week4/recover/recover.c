#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    // The files you generate should each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.

}
