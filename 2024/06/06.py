import sys

fieldrow = []
field = []

def docount(direction, x, y):
    count = 1
    stepcount = 0

    while stepcount < (b * h):
        if direction == "^":
            if y > 0:
                if field[y-1][x] == ".":
                    y = y - 1
                    field[y][x] = "X"
                    count = count + 1
                    stepcount = stepcount + 1
                    continue
                if field[y-1][x] == "X":
                    y = y - 1
                    stepcount = stepcount + 1
                    continue
                if field[y-1][x] == "#" or field[y-1][x] == "O":
                    direction = rotate(direction)
                    stepcount = stepcount + 1
                    continue
                stepcount = stepcount + 1
                continue
            else:
                stepcount = stepcount + 1
                break
        if direction == ">":
            if x < (b-1):
                if field[y][x+1] == ".":
                    x = x + 1
                    field[y][x] = "X"
                    count = count + 1
                    stepcount = stepcount + 1
                    continue
                if field[y][x+1] == "X":
                    x = x + 1
                    stepcount = stepcount + 1
                    continue
                if field[y][x+1] == "#" or field[y][x+1] == "O":
                    direction = rotate(direction)
                    stepcount = stepcount + 1
                    continue
                stepcount = stepcount + 1
                continue
            else:
                stepcount = stepcount + 1
                break
        if direction == "v":
            if y < (h-1):
                if field[y+1][x] == ".":
                    y = y + 1
                    field[y][x] = "X"
                    count = count + 1
                    stepcount = stepcount + 1
                    continue
                if field[y+1][x] == "X":
                    y = y + 1
                    stepcount = stepcount + 1
                    continue
                if field[y+1][x] == "#" or field[y+1][x] == "O":
                    direction = rotate(direction)
                    stepcount = stepcount + 1
                    continue
                stepcount = stepcount + 1
                continue
            else:
                stepcount = stepcount + 1
                break
        if direction == "<":
            if x > 0:
                if field[y][x-1] == ".":
                    x = x - 1
                    field[y][x] = "X"
                    count = count + 1
                    stepcount = stepcount + 1
                    continue
                if field[y][x-1] == "X":
                    x = x - 1
                    stepcount = stepcount + 1
                    continue
                if field[y][x-1] == "#" or field[y][x-1] == "O":
                    direction = rotate(direction)
                    stepcount = stepcount + 1
                    continue
                stepcount = stepcount + 1
                continue
            else:
                stepcount = stepcount + 1
                break
        stepcount = stepcount + 1
    # print("Stepcount: " + str(stepcount))
    if stepcount == (b * h):
        return -1
    else:
        return count

def printField():
    for y in range(h):
        for x in range(b):
            print(field[y][x], end='')
        print("")


def cleanField():
    # print("Lösche Markierungen")
    for y in range(h):
        for x in range(b):
            if field[y][x] == "X" or field[y][x] == "O":
                field[y][x] = "."



with open(sys.argv[1]) as file:
    for line in file:
        fieldrow = list(line)
        if (fieldrow[len(fieldrow) - 1] == '\n'): del fieldrow[len(fieldrow) - 1]
        field.append(fieldrow)
# breadth
b = len(fieldrow)
# height
h = len(field)

print ("Breite: " + str(b))
print ("Höhe:   " + str(h))

def rotate(x):
    if x == "^": return ">"
    if x == ">": return "v"
    if x == "v": return "<"
    if x == "<": return "^"

for y in range(h):
    for x in range(b):
        if field[y][x] == "^" or field[y][x] == "v" or field[y][x] == "<" or field[y][x] == ">":
            startdir = field[y][x]
            startx = x
            starty = y

print("Anfangxposition x: " + str(startx))
print("Anfangsposition y: " + str(starty))

x = startx
y = starty
direction = startdir
field[y][x] = "X"

print ("Unterschiedliche Stellen: " + str(docount(direction, x, y)))

runde = 0

for y in range (h):
    print(".", flush=True)
    for x in range (b):
        print("-", end="")
        cleanField()
        # printField()
        # print ("field[" + str(y) + "][" + str(x) + "]")
        if (field[y][x] == "."):
            field[y][x] = "O"
        # printField()
        field[starty][startx] = "X"
        if docount(startdir, startx, starty) == -1:
            #print (".")
            runde = runde + 1

print (runde)
