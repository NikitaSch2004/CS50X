# TODO
from cs50 import get_string
input = get_string("Text: ")
grade = 0
l = 0
s = 0
w = 0
# Iterate trough the text and get the text l,s and w
for i in input:
    if i.isalpha():
        l += 1
    elif i in [".", "!", "?"]:
        s += 1
    elif i == " ":
        w += 1
w += 1
L = (l * 100) / w
S = (s * 100) / w
grade = round(0.0588 * L - 0.296 * S - 15.8)
# Print what type of Grade is the text  for
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")