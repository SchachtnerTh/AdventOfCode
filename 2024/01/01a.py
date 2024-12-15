# coding=UTF-8

import sys

alist = []
blist = []
with open(sys.argv[1]) as file:
    for line in file:
        a,b = line.split()
        alist.append(int(a))
        blist.append(int(b))

print("Part 1:")
alist.sort()
blist.sort()
diff = 0

for i, a in enumerate(alist):
    diff = diff + abs(a - blist[i])

print("Distanzensumme: " + str(diff))

print("Part 2:")

similarity = 0

for a in alist:
    s = blist.count(a)
    similarity = similarity + a * s

print("Ähnlichkeitensumme: " + str(similarity))