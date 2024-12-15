# coding=UTF-8

import sys
import re

matchsum = 0


print("Teil 1")

oneline = ""
with open(sys.argv[1]) as file:
    for line in file:
        oneline = oneline + line

print(str(len(oneline)))
    
matches = re.findall("mul\(([0-9]+),([0-9]+)\)", oneline, re.DOTALL)
for match in matches:
    matchsum = matchsum + int(match[0]) * int(match[1])
print(matchsum)

print("Teil 2")
# Der String muss zuerst geteilt werden

matchsum = 0

oneline = oneline.replace("\n", "")
oneline = oneline.replace("\r", "")
print(oneline)
print(len(oneline))

match2 = re.sub("don't\(\).*?do\(\)", "", oneline)
print("Länge jetzt: " + str(len(match2)))
match2 = re.sub("don't\(\).*do\(\)", "", match2)
print("Länge jetzt: " + str(len(match2)))
print(match2)
matches = re.findall("mul\(([0-9]+),([0-9]+)\)", match2, re.DOTALL)


for match in matches:
    print (match[0] + " * " + match[1])
    matchsum = matchsum + int(match[0]) * int(match[1])
print(matchsum)
