from cs50 import get_float

coins = {"quarter" : 0, "dime" : 0, "nickel" : 0, "penny" : 0}

change = -1

while(change < 0):
    change = get_float("Insert the change: ")

cents = int(change*100)

while(cents != 0):

    if cents >= 25:
        cents = cents - 25
        coins["quarter"] = coins["quarter"] + 1

    elif cents >= 10 and cents < 25:
        cents = cents - 10
        coins["dime"] = coins["dime"] + 1

    elif cents >= 5 and cents < 10:
        cents = cents - 5
        coins["nickel"] = coins["nickel"] + 1

    else:
        cents = cents - 1
        coins["penny"] = coins["penny"] + 1

total = coins["quarter"] + coins["dime"] + coins["nickel"] + coins["penny"]

print(f"\nAmount of coins used in total: {total}\n"
+ "\n$0.25 > " + str(coins["quarter"])
+ "\n$0.10 > " + str(coins["dime"])
+ "\n$0.05 > " + str(coins["nickel"])
+ "\n$0.01 > " + str(coins["penny"]))

print()