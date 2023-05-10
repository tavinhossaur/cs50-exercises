from cs50 import get_int

height = get_int("Insert the desired height: ")

for i in range(height):
    for j in range(height-1, i, -1):
        print(" ", end="")
    for k in range(-1, i):
        print("#", end="")

    print(" ", end="")

    for l in range(i+1):
        print("#", end="")
    print(" ", end="")

    print()

