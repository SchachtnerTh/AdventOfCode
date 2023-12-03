def get_count(linearray, teil):
    summe = 0
    for line in linearray:
        lval = re.findall(r"[0-9]", line)
        zsum = int(lval[0]) * 10 + int(lval[-1])
        print (int(lval[0]) * 10 + int(lval[-1]))
        summe += zsum

    print ("Teil ", teil, ": " , summe)

import re
with open("input.1") as file:
    lines = [line.rstrip() for line in file]



#for line in lines:
##    print (line)
#    lval = re.findall(r"[0-9]", line)
##    print (lval)
##    print (lval[0])
##    print (lval[-1])
#    zsum = int(lval[0]) * 10 + int(lval[-1])
#    print (int(lval[0]) * 10 + int(lval[-1]))
#    summe += zsum

# get_count(lines, 1)
lines2 = []
for line in lines:
    posmin=99 
    number = "one"
    number2 = "1"
    if (line.find("one") != -1):
        posmin = line.find("one")
    pos2 = line.find("two")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "two"
        number2 = "2"
    pos2 = line.find("three")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "three"
        number2 = "3"
    pos2 = line.find("four")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "four"
        number2 = "4"
    pos2 = line.find("five")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "five"
        number2 = "5"
    pos2 = line.find("six")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "six"
        number2 = "6"
    pos2 = line.find("seven")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "seven"
        number2 = "7"
    pos2 = line.find("eight")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "eight"
        number2 = "8"
    pos2 = line.find("nine")
    if (pos2 != -1) and (pos2 < posmin):
        posmin = pos2
        number = "nine"
        number2 = "9"

    print ("posmin: ", posmin, ", number: ", number)
    line = line.replace(number, number2)
    lines2 += [line]

summe2 = 0
for line in lines2:
    lval = re.findall(r"[0-9]", line)
    zsum = int(lval[0]) * 10
    print (int(lval[0]) * 10)
    summe2 += zsum

print ("Erste Teilsumme Teil 2: ", summe2)


lines3 = []
for line in lines:
    posmax = 0
    number = "one"
    number2 = "1"
    posmax = line.rfind("one")
    pos2 = line.rfind("two")
    if pos2 > posmax:
        posmax = pos2
        number = "two"
        number2 = "2"
    pos2 = line.rfind("three")
    if pos2 > posmax:
        posmax = pos2
        number = "three"
        number2 = "3"
    pos2 = line.rfind("four")
    if pos2 > posmax:
        posmax = pos2
        number = "four"
        number2 = "4"
    pos2 = line.rfind("five")
    if pos2 > posmax:
        posmax = pos2
        number = "five"
        number2 = "5"
    pos2 = line.rfind("six")
    if pos2 > posmax:
        posmax = pos2
        number = "six"
        number2 = "6"
    pos2 = line.rfind("seven")
    if pos2 > posmax:
        posmax = pos2
        number = "seven"
        number2 = "7"
    pos2 = line.rfind("eight")
    if pos2 > posmax:
        posmax = pos2
        number = "eight"
        number2 = "8"
    pos2 = line.rfind("nine")
    if pos2 > posmax:
        posmax = pos2
        number = "nine"
        number2 = "9"

    print ("posmax: ", posmax, ", number: ", number)
    line = line.replace(number, number2)
    lines3 += [line]

summe3 = 0
for line in lines3:
    lval = re.findall(r"[0-9]", line)
    zsum = int(lval[-1])
    print (int(lval[-1]))
    summe3 += zsum
print (lines3)
print ("Zweite Teilsumme Teil 2: ", summe3)
print ("Teil 2 gesamt: ", summe2 + summe3)

##   line = line.replace("one", "1")
##    line = line.replace("two", "2")
##    line = line.replace("three", "3")
##    line = line.replace("four", "4")
##    line = line.replace("five", "5")
##    line = line.replace("six", "6")
##    line = line.replace("seven", "7")
##    line = line.replace("eight", "8")
##    line = line.replace("nine", "9")
##    lines2 += [line]
##
##print(lines2)
##get_count(lines2, 2)
