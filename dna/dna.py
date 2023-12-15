import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    persons = []
    file = sys.argv[1]
    with open(file) as file:
        dict_reader = csv.DictReader(file)
        for person in dict_reader:
            persons.append(person)
        sequences = persons[0].copy()
    sequences.pop("name")
    subsequences = list(sequences.keys())

    # TODO: Read DNA sequence file into a variable
    dna_file = sys.argv[2]
    with open(dna_file) as dna_file:
        dnafile = csv.reader(dna_file)
        for sequence in dnafile:
            sequence = str(sequence)

    # TODO: Find longest match of each STR in DNA sequence
    for subsequence in subsequences:
        max_subsequence = str(longest_match(sequence, subsequence))
        sequences[subsequence] = max_subsequence

    # TODO: Check database for matching profiles
    for person in persons:
        if sequences.items() <= person.items():
            match = person["name"]
            print(match)
            break
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
