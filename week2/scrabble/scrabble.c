#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int getScore(string word);
int findIndex(char target, char array[]);

char letters[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z'};

int scores[] = {
    1, 3, 3, 2, 1, 4, 2, 4,
    1, 8, 5, 1, 3, 1, 1, 3,
    10, 1, 1, 1, 1, 4, 4, 8,
    4, 10};

int main(void)
{
    string first = get_string("Player 1: ");
    string second = get_string("Player 2: ");

    int firstScore = 0;
    int secondScore = 0;

    firstScore = getScore(first);
    secondScore = getScore(second);

    if (firstScore > secondScore)
    {
        printf("Player 1 wins!");
    }
    else if (firstScore < secondScore)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }

    printf("\n");

    return 0;
}

int getScore(string word)
{
    int length = strlen(word);
    int score = 0;
    for (int i = 0; i < length; i++)
    {
        int index = findIndex(toupper(word[i]), letters);
        if (index != -1)
        {
            score += scores[index];
        }
    }
    return score;
}

int findIndex(char target, char array[])
{
    int length = strlen(array);
    int result = -1;
    for (int i = 0; i < length; i++)
    {
        if (array[i] == target)
        {
            result = i;
            break;
        }
    }

    return result;
}