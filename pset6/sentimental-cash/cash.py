# TODO
from cs50 import get_float
change = 0
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break
change *= 100
penny = 1
nickel = 5
dime = 10
quarter = 25
coins = 0

# Number of quarter
while change >= quarter:
    change -= quarter
    coins += 1
# Number of dimes
while change >= dime:
    change -= dime
    coins += 1
# Number of nickels
while change >= nickel:
    change -= nickel
    coins += 1
# Number of pennies
while change >= penny:
    change -= penny
    coins += 1
# Print number of coins
print(coins)