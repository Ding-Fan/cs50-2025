#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

bool keyValidation(string key);
string encryptText(string plainText, string key);

int main(int argc, string argv[])
{
    // printf("argc: %i\n", argc);
    if (argc <= 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    // printf("key: %s\n", key);

    if(!keyValidation(key))
    {
        return 1;
    }

    // printf("Key validation passed.\n");

    // get the plain text
    string plainText = get_string("plaintext: ");

    string cipherText = encryptText(plainText, key);

    printf("ciphertext: %s\n", cipherText);

    return 0;
}

bool keyValidation(string key)
{
    // key is invalid (as by 
    // not containing 26 characters
    // containing any character that is not an alphabetic character
    // or not containing each letter exactly once)

    int keyLength = strlen(key);
    if(keyLength != 26) {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";  // Modifiable array

    for(int i = 0; i < keyLength; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }

        for(int j = 0; j < 26; j++)
        {
            if(tolower(key[i]) == alphabet[j])
            {
                alphabet[j] = '0';
                break;
            }
        }
    }

    if(strcmp(alphabet, "00000000000000000000000000") != 0)
    {
        printf("Key must contain each letter exactly once.\n");
        return false;
    }

    return true;
}

string encryptText(string plainText, string key)
{
    int plainTextLength = strlen(plainText);
    int keyLength = strlen(key);
    string cipherText = plainText;

    for(int i = 0; i < plainTextLength; i++)
    {
        if(isalpha(plainText[i]))
        {
            if(isupper(plainText[i]))
            {
                cipherText[i] = toupper(key[plainText[i] - 'A']);
            }
            else
            {
                cipherText[i] = tolower(key[plainText[i] - 'a']);
            }
        }
    }

    return cipherText;
}