#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

string encrypt_text(string key, string text);
int check_key(int argc, string argv[]);
int check_alph(string key);
int check_duplicates(string key);

int main(int argc, string argv[])
{
    if (check_key(argc, argv) == 1)
    {
        return 1;
    }
    else
    {
        string key = argv[1];
        string text = get_string("plaintext:  ");
        string encypted_text = encrypt_text(key, text);
        printf("ciphertext: %s\n", encypted_text);
    }
}

string encrypt_text(string key, string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                int code = text[i] - 'a';
                text[i] = tolower(key[code]);
            }
            else if (isupper(text[i]))
            {
                int code = text[i] - 'A';
                text[i] = toupper(key[code]);
            }
        }
        else
        {
            text[i] = text[i];
        }
    }
    return text;
}

int check_key(int argc, string argv[])
{
    string key = argv[1];
    if (argc == 2 && strlen(argv[1]) == 26 && check_alph(key) == 0 && check_duplicates(key) == 0)
    {
        return 0;
    }
    else if (argc == 2 && strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (argc == 2 && check_alph(key) == 1)
    {
        printf("Key must not contain non-alphabetical characters.\n");
        return 1;
    }
    else if (argc == 2 && check_duplicates(key) == 1)
    {
        printf("Key must not contain duplicate letters.\n");
        return 1;
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}

int check_alph(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            return 1;
        }
    }
    return 0;
}

int check_duplicates(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        for (int count = i + 1; count < strlen(key); count++)
        {
            if (tolower(key[i]) == tolower(key[count]))
            {
                return 1;
            }

        }
    }
    return 0;
}