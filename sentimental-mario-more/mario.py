# TODO


def main():
    height = get_height()
    line = height
    print_pyramid(height, line)


def get_height():
    while True:
        height = input("Height: ")
        if height.isdigit():
            height = int(height)
            if height <= 8 and height > 0:
                return height


def print_pyramid(height, line):  # height is an int
    if height == 0:
        return
    else:
        spaces = height - 1
        blocks = line - spaces
        print(" " * spaces, end="")
        print("#" * blocks, end="")
        print("  ", end="")
        print("#" * blocks)
        print_pyramid(height - 1, line)


if __name__ == "__main__":
    main()
