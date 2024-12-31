import sys
import os
import time
import copy

class Robot:
    px: int
    px: int
    vx: int
    vy: int

    def __init__(self, px:int, py:int, vx:int, vy:int):
        self.px = int(px)
        self.py = int(py)
        self.vx = int(vx)
        self.vy = int(vy)

    def calcPos(self, s:int, wx:int, wy:int):
        self.px = (self.px + s * self.vx) % wx
        self.py = (self.py + s * self.vy) % wy

    def __repr__(self):
        return f"P({self.px:3}|{self.py:3}), v=({self.vx:3},{self.vy:3})\n"

robots = []

def printAllRobots(wx:int, wy:int, rbts:list):
    for i in range(wx): print("-", end="")
    print("\r")
    print("Robots map:")
    for y in range(wy):
        for x in range(wx):
            count = 0
            for r in rbts:
                if r.px == x and r.py == y:
                    count = count + 1
            if count == 0:
                print(".", end="")
            else:
                print(count, end="")
        print("\r")
    for i in range(wx): print("-", end="")
    print("\r")

def calculateSafetyFactor(wx:int, wy:int, rbts:list):
    lr = int(wx / 2)
    ou = int(wy / 2)

    lo = 0
    ro = 0
    lu = 0
    ru = 0

    for r in rbts:
        if r.px < lr and r.py < ou: lo = lo + 1
        if r.px < lr and r.py > ou: lu = lu + 1
        if r.px > lr and r.py < ou: ro = ro + 1
        if r.px > lr and r.py > ou: ru = ru + 1
    return lo*ro*lu*ru

os.system("")
with open(sys.argv[1]) as file:
    for line in file:
        position, velocity = line.split(" ")
        label,values = position.split("=")
        posx,posy = values.split(",")
        label,values = velocity.split("=")
        velx,vely = values.split(",")
        robots.append(Robot(posx, posy, velx, vely))

        print(f"Pos: x={posx}, y={posy}, Velocity: x={velx}, y={vely}")
print(robots)
wx = 101
wy = 103

robotsV1 = copy.deepcopy(robots)

for r in robotsV1:
    r.calcPos(100, wx, wy)

sf = calculateSafetyFactor(wx, wy, robotsV1)
# print("\033[2J")
# printAllRobots(wx,wy)
print("\033[2J")

# 68
# 169
# 270

initialWait = 68
similarImage = 101
countSimilarImage = 70

for r in robots:
    r.calcPos(initialWait, wx, wy)


for r in robots:
    r.calcPos(countSimilarImage * similarImage, wx, wy)
printAllRobots(wx, wy, robots)
print(f"Combined Safety Factor: {sf}")
print(f"First time Christmas tree after {similarImage * countSimilarImage + initialWait} Sekunden.")
exit(0)

for r in robots:
    r.calcPos(68, wx, wy)


for i in range(1000):
    for r in robots:
        r.calcPos(101, wx, wy)
    print("\033[H")
    printAllRobots(wx,wy)
    #time.sleep(1)
    line = wy + 1
    column = wx + 1
    print(f"\033[{line};{column}f *** {i:5} ***",end="")
    
printAllRobots(wx, wy)

