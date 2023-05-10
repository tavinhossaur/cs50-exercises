import sys

def main():
    # Recieving the number and getting the lenght
    number = input("Number: ")
    length = len(str(number))

    evenPosSum = 0
    oddPosSum = 0
    total = 0

    # Base case for invalidating more quickily the card number
    if length != 13 and length != 15 and length != 16:
        print("INVALID")
        sys.exit()

    # Card checking algorithm
    for i in range(-2, (-length-1), -2):
        multSum = int(number[i]) * 2
        
        if multSum >= 10:
            evenPosSum = evenPosSum + multSum - 9
        else:
            evenPosSum = evenPosSum + multSum

    for i in range(-1, (-length-1), -2):
        tempOdd = int(number[i])
        oddPosSum = oddPosSum + tempOdd

    total = evenPosSum + oddPosSum

    # Checking the card
    if total % 2 == 0:
        if int(number[0]) == 3 and int(number[1]) == 4 or int(number[1]) == 7:
            print("AMEX")

        elif int(number[0]) == 5 and int(number[1]) == 1 or int(number[1]) == 2 or int(number[1]) == 3 or int(number[1]) == 4 or int(number[1]) == 5:
            print("MASTERCARD")

        elif int(number[0]) == 4:
            print("VISA")

        else:
            print("INVALID")


if __name__ == "__main__":
    main()