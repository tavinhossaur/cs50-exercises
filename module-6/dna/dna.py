from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    strs = []
    persons = []

    # Read the database file
    # 'with' is to implicitly make a try catch when opening a file
    # and there's no need to close it too
    with open(argv[1], mode="r") as database:
        reader = csv.DictReader(database)

        # Populating the list of STRs
        # '[1:]' gets all the indexes after the index 1, which is the name
        strs = reader.fieldnames[1:]

        for row in reader:
            # Add person to 'persons'
            persons.append(row)

    # Initializing dictionary for counting the sequences
    strCount = dict.fromkeys(strs, 0)

    # Read the sequence file
    with open(argv[2], mode="r") as sequenceFile:
        # Get the first line
        sequence = sequenceFile.readline()
        # Iterate through the database
        for STR in strs:
            # Check for repeats
            strCount[STR] = checkSequences(sequence, STR)

    # Check if a person has the same amount of STR repeats
    for person in persons:
        counter = 0

        # Adds up to the counter if it matches
        for STR in strs:
            if int(person[STR]) != strCount[STR]:
                continue
            counter += 1

        # Print the name of the person if it has a match
        if counter == len(strs):
            print(person['name'])
            exit(0)

    print("No match")
    exit(1)

def checkSequences(sequence, STR):
    # Amount of bases in the STR
    L = len(STR)

    hgstRepeat = 0
    for i in range(len(sequence)):
        # Tracks the amount of repeats
        repeats = 0

        # If the i'st char plus the length of the STR makes a match
        # add up to the counter and start the while loop
        if sequence[i: i + L] == STR:
            # First match
            repeats += 1

            # Keep adding until it's the sequence is equal
            while sequence[i: i + L] == sequence[i + L: i + (2 * L)]:
                repeats += 1
                # Changing to next potential repeat location
                i += L

        # Update the highest repeat if the amount of repeats from the iteration gets higher
        if repeats > hgstRepeat:
            hgstRepeat = repeats

    return hgstRepeat

if __name__ == "__main__":
    main()