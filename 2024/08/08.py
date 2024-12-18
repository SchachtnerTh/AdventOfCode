import sys

points=[]
pmap=[]

class Location:
    x: int
    y: int

    def __init__(self, x:int, y:int):
        self.x = x
        self.y = y

    def __str__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"
    
    def __repr__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"

class AntennaRegister:
    letter: str
    locations: list

    def __str__(self):
        a="Letter: " + self.letter + '\n'
        for l in self.locations:
            a = a + str(l)
        return a

antlist = []

ants = AntennaRegister()

with open(sys.argv[1]) as file:
    for line in file:
        points = list(line.rstrip())
        pmap.append(points)

print(len(pmap))

w = len(pmap[0])
h = len(pmap)

print (f"Size: {w}x{h}")

for y in range(h):
    for x in range(w):
        if pmap[y][x] != '.':
            c = pmap[y][x]
            found = 0
            for ant in antlist:
                if ant.letter == c:
                    ant.locations.append(Location(x,y))
                    found = 1
            if found == 0:
                a = AntennaRegister()
                a.letter = c
                a.locations=[]
                a.locations.append(Location(x,y))
                antlist.append(a)

count = 0

nodelist = []

for ant in antlist:
    #print(str(ant))
    lcount = len(ant.locations)
    for i in range(lcount):
        for j in range(lcount):
            if i == j: continue
            vec = Location(ant.locations[j].x - ant.locations[i].x, ant.locations[j].y - ant.locations[i].y)
            # Der Vektor beschreibt den Weg von i nach j -> j = i + vec
            # Der Gegenknoten ist dann j2 = i - vec
            j2 = Location(ant.locations[i].x - vec.x, ant.locations[i].y - vec.y)
            if j2.x >= 0 and j2.x < w and j2.y >= 0 and j2.y < h:
                found = 0
                for n in nodelist:
                    if n.x == j2.x and n.y == j2.y:
                        found = 1
                if found == 0:
                    nodelist.append(j2)
            # print(vec)
# print(nodelist)
print(len(nodelist))

nodelist2 = []

for ant in antlist:
    #print(str(ant))
    lcount = len(ant.locations)
    for i in range(lcount):
        for j in range(lcount):
            if i == j: continue
            vec = Location(ant.locations[j].x - ant.locations[i].x, ant.locations[j].y - ant.locations[i].y)
            # Der Vektor beschreibt den Weg von i nach j -> j = i + vec
            # Der Gegenknoten ist dann j2 = i - vec

            inrange = 1
            pos = 1
            while inrange == 1:
                j2 = Location(ant.locations[i].x - pos * vec.x, ant.locations[i].y - pos * vec.y)
                if j2.x >= 0 and j2.x < w and j2.y >= 0 and j2.y < h:
                    pos = pos + 1
                    found = 0
                    for n in nodelist2:
                        if n.x == j2.x and n.y == j2.y:
                            found = 1
                    if found == 0:
                        nodelist2.append(j2)
                else:
                    inrange = 0
            # print(vec)
    for a in ant.locations:
        found2 = 0
        for n in nodelist2:
            if n.x == a.x and n.y == a.y:
                found2 = 1
        if found2 == 0:
            #print(a)
            nodelist2.append(a)
# print(nodelist)
print(len(nodelist2))