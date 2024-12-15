import sys

fieldrow = []
field = []

with open(sys.argv[1]) as file:
    for line in file:
        fieldrow = list(line)
        if (fieldrow[len(fieldrow) - 1] == '\n'): del fieldrow[len(fieldrow) - 1]
        field.append(fieldrow)
# breadth
b = len(fieldrow)
# height
h = len(field)

# erster Parameter ist Zeile (y-Wert)

print("Field is " + str(b) + " x " + str(h) + ".")

def findStr(angle, x, y):
    xmascount = 0
    match angle:
        case  0: 
            if y >= 3: 
                if field[y    ][x    ] == 'X' and field[y - 1][x    ] == 'M' and field[y - 2][x    ] == 'A' and field[y - 3][x    ] == 'S': xmascount = xmascount + 1;
        case 45: 
            if y >= 3 and x <= b - 4: 
                if field[y    ][x    ] == 'X' and field[y - 1][x + 1] == 'M' and field[y - 2][x + 2] == 'A' and field[y - 3][x + 3] == 'S': xmascount = xmascount + 1;
        case 90: 
            if x <= b - 4:            
                if field[y    ][x    ] == 'X' and field[y    ][x + 1] == 'M' and field[y    ][x + 2] == 'A' and field[y    ][x + 3] == 'S': xmascount = xmascount + 1;
        case 135:
            if y <= h - 4 and x <= b - 4:            
                if field[y    ][x    ] == 'X' and field[y + 1][x + 1] == 'M' and field[y + 2][x + 2] == 'A' and field[y + 3][x + 3] == 'S': xmascount = xmascount + 1;
        case 180:
            if y <= h - 4:
                if field[y    ][x    ] == 'X' and field[y + 1][x    ] == 'M' and field[y + 2][x    ] == 'A' and field[y + 3][x    ] == 'S': xmascount = xmascount + 1;
        case 225:
            if y <= h - 4 and x >= 3:
                if field[y    ][x    ] == 'X' and field[y + 1][x - 1] == 'M' and field[y + 2][x - 2] == 'A' and field[y + 3][x - 3] == 'S': xmascount = xmascount + 1;
        case 270:
            if x >= 3:            
                if field[y    ][x    ] == 'X' and field[y    ][x - 1] == 'M' and field[y    ][x - 2] == 'A' and field[y    ][x - 3] == 'S': xmascount = xmascount + 1;
        case 315:
            if x >= 3 and y >= 3:
                if field[y    ][x    ] == 'X' and field[y - 1][x - 1] == 'M' and field[y - 2][x - 2] == 'A' and field[y - 3][x - 3] == 'S': xmascount = xmascount + 1;
    return xmascount;

def findStr2(x, y):
    xmascount = 0
    if y >= 3: 
        if field[y    ][x    ] == 'X' and field[y - 1][x    ] == 'M' and field[y - 2][x    ] == 'A' and field[y - 3][x    ] == 'S': xmascount = xmascount + 1;
    if y >= 3 and x <= b - 4: 
        if field[y    ][x    ] == 'X' and field[y - 1][x + 1] == 'M' and field[y - 2][x + 2] == 'A' and field[y - 3][x + 3] == 'S': xmascount = xmascount + 1;
    if x <= b - 4:            
        if field[y    ][x    ] == 'X' and field[y    ][x + 1] == 'M' and field[y    ][x + 2] == 'A' and field[y    ][x + 3] == 'S': xmascount = xmascount + 1;
    if y <= h - 4 and x <= b - 4:            
        if field[y    ][x    ] == 'X' and field[y + 1][x + 1] == 'M' and field[y + 2][x + 2] == 'A' and field[y + 3][x + 3] == 'S': xmascount = xmascount + 1;
    if y <= h - 4:
        if field[y    ][x    ] == 'X' and field[y + 1][x    ] == 'M' and field[y + 2][x    ] == 'A' and field[y + 3][x    ] == 'S': xmascount = xmascount + 1;
    if y <= h - 4 and x >= 3:
        if field[y    ][x    ] == 'X' and field[y + 1][x - 1] == 'M' and field[y + 2][x - 2] == 'A' and field[y + 3][x - 3] == 'S': xmascount = xmascount + 1;
    if x >= 3:            
        if field[y    ][x    ] == 'X' and field[y    ][x - 1] == 'M' and field[y    ][x - 2] == 'A' and field[y    ][x - 3] == 'S': xmascount = xmascount + 1;
    if x >= 3 and y >= 3:
        if field[y    ][x    ] == 'X' and field[y - 1][x - 1] == 'M' and field[y - 2][x - 2] == 'A' and field[y - 3][x - 3] == 'S': xmascount = xmascount + 1;
    return xmascount;

def findStr3(x, y):
    if x > 0 and x < b - 1 and y > 0 and y < h - 1:
        #
        #  M S   S M   M M   S S
        #   A     A     A     A
        #  M S   S M   S S   M M
        #

        if ((
            (field[y - 1][x - 1] == 'M' and field[y + 1][x + 1] == "S") or 
            (field[y - 1][x - 1] == 'S' and field[y + 1][x + 1] == "M")) and (
                (field[y - 1][x + 1] == 'M' and field[y + 1][x - 1] == "S") or 
                (field[y - 1][x + 1] == 'S' and field[y + 1][x - 1] == "M"))) : 
            print("Found (" + str(x) + "," + str(y) + ")")
            return 1
        else:
            return 0
    else:
        return 0

fullxmascount = 0
mascount = 0

for y in range(h):
    for x in range(b):
        if field[y][x] == 'X' : fullxmascount = fullxmascount + findStr2(x, y)

for y in range(h):
    for x in range(b):
        if field[y][x] == 'A' : 
            print("Found A (" + str(x) + "," + str(y) + ")")
            mascount = mascount + findStr3(x,y)


print (fullxmascount)
print (mascount)