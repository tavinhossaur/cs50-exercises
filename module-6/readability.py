from cs50 import get_string
import re

text = get_string("Insert the text to be analised: ")
text = text.strip()

lttrs = 0
# Starts at 1 because of the last word
wrds = 1
stncs = 0

for c in text:
    # Amount of letters
    if c == '.' or c == '!' or c == '?' or c == ',':
        lttrs -= 1
    lttrs += 1
    # Amount of words
    if c.isspace():
        wrds += 1
    # Amount of sentences
    if c == '.' or c == '?' or c == '!':
        stncs += 1

lttrs = len(text.replace('\u0020', ''))

print("\n> " + str(lttrs) + " " + str(wrds) + " " + str(stncs))

# Coleman-Liau Formula
lttrs = lttrs / wrds * 100
stncs = stncs / wrds * 100
index = 0.0588 * lttrs - 0.296 * stncs - 15.8

if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    index = round(index, 2)
    print("Grade: " + str(index))
