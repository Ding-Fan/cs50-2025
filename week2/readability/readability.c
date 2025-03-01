#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

double getColemanLiauIndex(string text);

int main()
{
    // get the text
    string text = get_string("Text: ");

    // print text character by character
    // for (int i = 0; text[i] != '\0'; i++)
    // {
    //     printf("%i: %c\n", i, text[i]);
    // }

    // Coleman-Liau index
    // index = 0.0588 * L - 0.296 * S - 15.8
    int indexResult = round(getColemanLiauIndex(text));

    // output “Grade X” where “X” is the grade level computed, rounded to the nearest integer. If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output “Grade 16+” instead of giving the exact index number. If the grade level is less than 1, your program should output “Before Grade 1”.

    if(indexResult < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(indexResult >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", indexResult);
    }

    return 0;
}

double getColemanLiauIndex(string text)
{
    double colemanLiauIndex = 0.0;
    // count to 100 words
    // get character from start, until space, save it as a word
    // do the same until 100 words, or until the end of the text
    int totalWords = 1; // define the minimum word count as 1, no need to consider the last word, which ends with '\0'
    int totalLetters = 0;
    int totalSentences = 0;
    char c;
    int textIndex = 0;
    do
    {
        c = text[textIndex];
        if (c == ' ')
        {
            // printf("char: %c\n", c);
            totalWords++;
        }
        else if (c == '.' || c == '!' || c == '?')
        {
            totalSentences++;
        }
        
        if (isalpha(c))
        {
            totalLetters++;
        }

        textIndex++;
    } while (c != '\0');

    // L = (Letters ÷ Words) × 100
    double L = totalLetters / (double) totalWords * 100;
    // S = (Sentences ÷ Words) × 100
    double S = totalSentences / (double) totalWords * 100;

    colemanLiauIndex = 0.0588 * L - 0.296 * S - 15.8;

    // printf("totalWords: %i\n", totalWords);
    // printf("totalLetters: %i\n", totalLetters);
    // printf("totalSentences: %i\n", totalSentences);
    // printf("L: %f\n", L);
    // printf("S: %f\n", S);
    // printf("index: %i\n", colemanLiauIndex);

    return colemanLiauIndex;
}
