import sys

places=0
pmap=[]

class Point:
    x: int
    y: int

    def __init__(self, x, y):
        self.x = x
        self.y = y

class Trail:
    begin: Point
    end: list
    num: int

    def __init__(self, p:Point):
        self.begin=p
        self.end = []
        self.num = 0

    def addEnd(self, e:Point):
        found = 0
        for p in self.end:
            if p.x == e.x and p.y == e.y:
                found = 1
        if found == 0:
            self.end.append(e)

def checkEnd(t:Trail, x, y):
    if pmap[y][x] == 9:
        t.addEnd(Point(x,y))
        #print(f"- Ende bei ({x},{y})")
        return

    newval = pmap[y][x] + 1
    if x > 0:
        if pmap[y][x-1] == newval: 
            #print("nach links")
            checkEnd(t, x-1, y)
    if x < w - 1:
        if pmap[y][x+1] == newval: 
            #print("nach rechts")
            checkEnd(t, x+1, y)
    if y > 0:
        if pmap[y-1][x] == newval: 
            #print("nach oben")
            checkEnd(t, x, y-1)
    if y < h - 1:
        if pmap[y+1][x] == newval: 
            #print("nach unten")
            checkEnd(t, x, y+1)

def checkEnd2(t:Trail, x, y):
    if pmap[y][x] == 9:
        t.addEnd(Point(x,y))
        #print(f"- Ende bei ({x},{y})")
        return
    numberofways = 0
    newval = pmap[y][x] + 1

    if x > 0:       
        if pmap[y][x-1] == newval: numberofways = numberofways + 1
    if x < w - 1:   
        if pmap[y][x+1] == newval: numberofways = numberofways + 1
    if y > 0:      
        if pmap[y-1][x] == newval: numberofways = numberofways + 1
    if y < h - 1:   
        if pmap[y+1][x] == newval: numberofways = numberofways + 1

    if t.num == 0 and numberofways > 0:
        t.num = 1
    t.num = t.num + (numberofways - 1)

    if x > 0:
        if pmap[y][x-1] == newval: 
            #print("nach links")
            checkEnd2(t, x-1, y)
    if x < w - 1:
        if pmap[y][x+1] == newval: 
            #print("nach rechts")
            checkEnd2(t, x+1, y)
    if y > 0:
        if pmap[y-1][x] == newval: 
            #print("nach oben")
            checkEnd2(t, x, y-1)
    if y < h - 1:
        if pmap[y+1][x] == newval: 
            #print("nach unten")
            checkEnd2(t, x, y+1)


trails = []

with open(sys.argv[1]) as file:
    for line in file:
        points = list(map(int,line.rstrip()))
        pmap.append(points)

w = len(pmap[0])
h = len(pmap)

scores = 0
scores2 = 0
# Suche Anfänge
for y in range(h):
    for x in range(w):
        if pmap[y][x] == 0:
            #print(f"Anfang bei ({x},{y})")
            b = Point(x,y)
            t = Trail(b)
            #print(f"Beginn bei ({x},{y})")
            checkEnd(t, x, y)
            scores = scores + len(t.end)
            checkEnd2(t, x, y)
            #print(t.num)
            scores2 = scores2 + t.num
            #print(len(t.end))

print(scores, scores2)