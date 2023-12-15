# TODO
import string

LETTERS = 0
SENTENCES = 0
WORDS = 1

# index = 0.0588 * L - 0.296 * S - 15.8
# L = average number of letters per 100 words
# S = average number of sentences per 100 words


def main():
    text = input("Text: ")
    index = calculate_index(text)
    print_index(index)


def calculate_index(text):
    global WORDS, SENTENCES, LETTERS
    for i in range(len(text)):
        if text[i].isalpha():
            LETTERS += 1
        elif text[i] in [".", "!", "?"]:
            SENTENCES += 1
        elif text[i] == " ":
            WORDS += 1
    L = LETTERS / WORDS * 100
    s = SENTENCES / WORDS * 100
    index = 0.0588 * L - 0.296 * s - 15.8
    return index


def print_index(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


if __name__ == "__main__":
    main()
