import csv
import sys

CFR
def main():
    DNA = {}
    results = []
    keys = []
    candidatesNr = 0
    # TODO: Check for command-line usage
    if not len(sys.argv) == 3:
        sys.exit("dna.py DICTIONARY TXT")
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            DNA[candidatesNr] = row
            candidatesNr += 1
    # TODO: Read DNA sequence file into a variable
    CandidateDNA = open(sys.argv[2], "r")
    dnaSeq = CandidateDNA.read()
    # TODO: Find longest match of each STR in DNA sequence
    for i in range(0, 1):
        for key in DNA[i]:
            if key == "name":
                continue
            else:
                keys += [key]
    for i in range(0, len(keys)):
        results += [longest_match(dnaSeq, keys[i])]
    # TODO: Check database for matching profiles
    for i in range(0, candidatesNr):
        matches = 0
        j = 0
        for key in keys:
            if results[j] == int(DNA[i][key]):
                matches += 1
            j += 1
        if matches == len(keys):
            print(DNA[i]["name"])
            sys.exit(0)
    print("no match")
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
