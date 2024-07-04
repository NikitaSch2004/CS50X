# TODO
from cs50 import get_int
# Input
while True:
    input = get_int("Number: ")
    if input > 0:
        break
# Variables
Legit = False
input = str(input)
input = input[::-1]
inputInt = []
sum = 0
parity = 0
AMEX = 15
VISA1 = 16
VISA2 = 13
MASTER = 16
# Get number from second to last and doubles them
for i in input[1::2]:
    inputInt += [int(i)*2]
# add numbers that are not doubled
for k in input[0::2]:
    sum += int(k)
# add number that are doubled
for j in inputInt:
    if not len(str(j)) == 1:
        while j > 0:
            sum += j % 10
            j //= 10
    sum += j
# check if it is Legit
if sum % 10 == 0:
    Legit = True
# Reverse the input
input = input[::-1]
# If it is Legit check what type of card it is
if Legit:
    if input[0] == "4":
        if len(input) == VISA1 or len(input) == VISA2:
            print("VISA")
    elif int(input[0:2]) in range(51, 56):
        if len(input) == MASTER:
            print("MASTERCARD")
    elif input[0:2] == "34" or input[0:2] == "37":
        print("AMEX")
else:
    print("INVALID")