#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int Letters = 0; // average letters per 100 words
int Sentences = 0; // average sentences per 100 words
int Words = 1;

int count_letters(string text, long i);
int count_sentences(string text, long i);
int count_words(string text, long i);
void print_grade(float index);
float calculate_index(string text);

int main(void)
{
    string text = get_string("Text: ");
    float index = calculate_index(text);
    print_grade(index);
}

int count_letters(string text, long i)
{
    if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
    {
        Letters += 1;
    }
    else
    {
        Letters += 0;
    }
    return Letters;
}

int count_sentences(string text, long i)
{
    if (text[i] == '.' || text[i] == '!' || text[i] == '?')
    {
        Sentences += 1;
    }
    else
    {
        Sentences += 0;
    }
    return Sentences;
}

int count_words(string text, long i)
{
    if (text[i] == ' ')
    {
        Words += 1;
    }
    else
    {
        Words += 0;
    }
    return Words;
}

void print_grade(float index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}

float calculate_index(string text)
{
    for (long i = 0; i < strlen(text); i++)
    {
        count_sentences(text, i);
        count_letters(text, i);
        count_words(text, i);
    }
    float L = (float)Letters / Words * 100.0;
    float S = (float)Sentences / Words * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}