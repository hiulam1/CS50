# TODO
import re


def main():
    number = get_number()
    if check_number(number):
        check_card(number)
    else:
        print("INVALID")


def get_number():
    number = input("Number: ")
    return number


def check_number(number):
    list = [int(x) for x in number]
    sum = 0
    for i in range(-2, -len(number) - 1, -2):
        if list[i] * 2 >= 10:
            j = list[i] * 2
            j = j % 10 + 1
            sum += j
        else:
            sum += list[i] * 2
    for i in range(-1, -len(number) - 1, -2):
        sum += list[i]
    if sum % 10 == 0:
        return True
    else:
        return False


def check_card(number):
    amex = r"^(34|37)\d{13}$"
    mastercard = r"^5[1-5]\d{14}$"
    visa = r"^4(\d{12}|\d{15})"
    if re.fullmatch(amex, number):
        print("AMEX")
    elif re.fullmatch(mastercard, number):
        print("MASTERCARD")
    elif re.fullmatch(visa, number):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
