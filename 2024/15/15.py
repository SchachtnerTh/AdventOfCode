import sys
import time
import copy

whO = []
movements = ""

class Warehouse:
    warehouse = []
    rx: int
    ry: int

    def __init__(self, warehouse, rx, ry):
        self.warehouse = copy.deepcopy(warehouse)
        if rx != 0 and ry != 0:
            self.rx = rx
            self.ry = ry
        else:
            self.rx = -1
            self.ry = -1
            # print(len(self.warehouse[0]))
            for y, row in enumerate(self.warehouse):
                for x, col in enumerate(row):
                    if col == "@":
                        self.rx = x
                        self.ry = y
            print(self.rx,self.ry)

    def printWh(self, whx):
        # print("\033[2J")
        for row in range(len(self.warehouse)):
            for col in range(len(self.warehouse[0])):
                print(whx[row][col], end="")
            print("\r")

    def tryMove2(self, x, y, direction):
        if direction == "^": ny = y - 1; nx = x
        if direction == ">": ny = y; nx = x + 1
        if direction == "v": ny = y + 1; nx = x
        if direction == "<": ny = y; nx = x - 1

        if self.warehouse[ny][nx] == "O":
            self.tryMove2(nx, ny, direction)
        if self.warehouse[ny][nx] == ".":
            self.warehouse[ny][nx] = self.warehouse[y][x]
            self.warehouse[y][x] = "."
            if self.warehouse[ny][nx] == "@":
                self.ry = ny
                self.rx = nx

    def tryMove(self, direction):
        if direction == "^":
            if self.ry == 0:
                return
            # prüfe von der aktuellen y-Position nach oben bis zum ersten "#", ob ein "." da ist. Wenn ja, dann move
            canMove = 0
            for y in range(self.ry - 1, 0, -1):
                if self.warehouse[y][self.rx] == ".":
                    canMove = 1
                    break
                if self.warehouse[y][self.rx] == "#":
                    break
            if canMove:
                for ny in range(y, self.ry):
                    self.warehouse[ny][self.rx] = self.warehouse[ny + 1][self.rx]
                self.warehouse[self.ry][self.rx] = "."
                self.ry = self.ry - 1
        if direction == "v": 
            if self.ry == len(self.warehouse) - 1:
                return
            # prüfe von der aktuellen y-Position nach unten bis zum ersten "#", ob ein "." da ist. Wenn ja, dann move
            canMove = 0
            for y in range(self.ry + 1, len(self.warehouse) - 1):
                if self.warehouse[y][self.rx] == ".":
                    canMove = 1
                    break
                if self.warehouse[y][self.rx] == "#":
                    break
            if canMove:
                for ny in range(y, self.ry, -1):
                    self.warehouse[ny][self.rx] = self.warehouse[ny - 1][self.rx]
                self.warehouse[self.ry][self.rx] = "."
                self.ry = self.ry + 1

        if direction == "<":
            if self.rx == 0:
                return
            # prüfe von der aktuellen x-Position nach links bis zum ersten "#", ob ein "." da ist. Wenn ja, dann move
            canMove = 0
            for x in range(self.rx - 1, 0, -1):
                if self.warehouse[self.ry][x] == ".":
                    canMove = 1
                    break
                if self.warehouse[self.ry][x] == "#":
                    break
            if canMove:
                for nx in range(x, self.rx):
                    self.warehouse[self.ry][nx] = self.warehouse[self.ry][nx + 1]
                self.warehouse[self.ry][self.rx] = "."
                self.rx = self.rx - 1

        if direction == ">": 
            if self.rx == len(self.warehouse[0]) - 1:
                return
            # prüfe von der aktuellen x-Position nach links bis zum ersten "#", ob ein "." da ist. Wenn ja, dann move
            canMove = 0
            for x in range(self.rx + 1, len(self.warehouse[0]) - 1):
                if self.warehouse[self.ry][x] == ".":
                    canMove = 1
                    break
                if self.warehouse[self.ry][x] == "#":
                    break
            if canMove:
                for nx in range(x, self.rx - 1, -1):
                    self.warehouse[self.ry][nx] = self.warehouse[self.ry][nx - 1]
                self.warehouse[self.ry][self.rx] = "."
                self.rx = self.rx + 1
        self.warehouse[self.ry][self.rx] = "\033[31m@\033[0m"

rx = 0
ry = 0

with open(sys.argv[1]) as file:
    part = 1
    l = 0
    for line in file:

        if line == "\n":
            part = 2

        if part == 1:
            whrow = list(line)
            if "@" in whrow:
                rx = whrow.index("@")
                ry = l
            whO.append(whrow)

        if part == 2:
            movements = movements + line.rstrip()
        l = l + 1

#print(warehouse)
#print(movements)
#print (rx,ry)

wh = Warehouse(whO, rx, ry)

for mv in list(movements):
    # wh.tryMove(mv)
    wh.tryMove2(wh.rx, wh.ry, mv)
    #print("\033[2J")
    #wh.printWh()
    #time.sleep(.1)

# wh.printWh()

gpssum = 0

for y,l in enumerate(wh.warehouse):
    for x,c in enumerate(l):
        if c == "O":
            gpssum = gpssum + y * 100 + x

print(f"GPS-Summe: {gpssum}")

warehouse2 = []

for row in whO:
    newrow = ""
    for col in row:
        #print(col)
        if col == "#": newrow = newrow + "##"
        if col == "O": newrow = newrow + "[]"
        if col == ".": newrow = newrow + ".."
        if col == "@": newrow = newrow + "@."
    newrow = list(newrow)
    warehouse2.append(newrow)

# print(warehouse2)
wh2 = Warehouse(warehouse2, 0, 0)