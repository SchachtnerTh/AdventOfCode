import sys

arealist = []    # Die Liste, in der die gesamte Karte enthalten ist.
regionlist = []  # Die Liste, in der die einzelnen Gebiete aufgelistet sind (List of Area)

OBEN   = 1
RECHTS = 2
UNTEN  = 4
LINKS  = 8

class Point:
    x: int
    y: int

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __eq__(self, p):
        if p.x == self.x and p.y == self.y:
            return True
        else:
            return False

class PerimeterElement:
    p: Point
    fencedir: int

class Area:
    area: int
    perimeter: int
    plotlist: list
    plant: str
    perimeterfence: list

    def __init__(self, thisplot: Point):
        self.plant = arealist[thisplot.y][thisplot.x]
        self.plotlist = []
        self.perimeterfence = []
        self.plotlist.append(thisplot)
        self.perimeter = self.checkPerimeter(thisplot)
        self.area = 1

    def __contains__(self, p: Point):
        for point in self.plotlist:
            if point == p:
                return True
        return False
    
    def checkPerimeter(self, p: Point):
        # Perimeter kann 0, 1, 2, 3 oder 4 sein, je nachdem wie viele Grenzen ein Plot hat
        perims = 0
        tempPerimeterElement = 0
        if (p.y == 0): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | OBEN
        if (p.x == 0): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | LINKS
        if (p.y == h - 1): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | UNTEN
        if (p.x == w - 1): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | RECHTS

        if (p.x > 0 and arealist[p.y][p.x - 1] != self.plant): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | LINKS
        if (p.x < w - 1 and arealist[p.y][p.x + 1] != self.plant): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | RECHTS
        if (p.y > 0 and arealist[p.y - 1][p.x] != self.plant): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | OBEN
        if (p.y < h - 1 and arealist[p.y + 1][p.x] != self.plant): 
            perims = perims + 1
            tempPerimeterElement = tempPerimeterElement | UNTEN

        if tempPerimeterElement != 0:
            pe = PerimeterElement()
            pe.p = p
            pe.fencedir = tempPerimeterElement
            self.perimeterfence.append(pe)

        return perims
    
    def addPlot(self, p:Point):
        self.plotlist.append(p)
        self.area = self.area + 1
        self.perimeter = self.perimeter + self.checkPerimeter(p)

    def __repr__(self):
        return f"Plant: {self.plant}, area: {self.area}, peri: {self.perimeter}, count: {len(self.plotlist)}\n"

def findNeighbours(a: Area, p: Point):
    if (p.x > 0): 
        q = Point(p.x - 1, p.y)
        if arealist[q.y][q.x] == a.plant and q not in a.plotlist:
            a.addPlot(q)
            findNeighbours(a, q)
    if (p.x < w - 1): 
        q = Point(p.x + 1, p.y)
        if arealist[q.y][q.x] == a.plant and q not in a.plotlist:
            a.addPlot(q)
            findNeighbours(a, q)
    if (p.y > 0): 
        q = Point(p.x, p.y - 1)
        if arealist[q.y][q.x] == a.plant and q not in a.plotlist:
            a.addPlot(q)
            findNeighbours(a, q)
    if (p.y < h - 1): 
        q = Point(p.x, p.y + 1)
        if arealist[q.y][q.x] == a.plant and q not in a.plotlist:
            a.addPlot(q)
            findNeighbours(a, q)



with open(sys.argv[1]) as file:
    for line in file:
        line = line.rstrip()
        plotrow = []
        for plot in list(line):
            plotrow.append(plot)
        arealist.append(plotrow)

h = len(arealist)
w = len(arealist[0])

for row in range(h):
    for col in range(w):
        used = False
        p = Point(col,row)
        for a in regionlist:
            if p in a.plotlist:
                used = True
        if not used:
            a = Area(p)
            regionlist.append(a)
            findNeighbours(a, p)

sum1 = 0

for r in regionlist:
    sum1 = sum1 + r.area * r.perimeter

print(f"Kosten: {sum1}")

sides = 0

# Jetzt iteriere durch alle Gebiete
j = 0
for a in regionlist:
    j = j + 1
    regionsides = 0
    # output = f"{j:2}. Fläche ({a.plant}): {a.area:2}, Zaunlänge: {a.perimeter:2}, Plots mit Zaun: {len(a.perimeterfence):2}"
    # print(output)

    for direction in 1,4:
        # Erst die y-Werte prüfen
        tmplist = []

        # Zaun oben
        for fenceelement in a.perimeterfence:
            if fenceelement.fencedir & direction == 0: continue
            tmplist.append(fenceelement.p)

        # In der Liste sind jetzt alle Fences, die oben einen Zaun haben
        # Suche raus, welche y-Werte das sind
        tmplist2 = []
        for p in tmplist:
            tmplist2.append(p.y)
        tmpset2 = set(tmplist2) # nur die unique values interessieren uns

        
        for uniquey in tmpset2:
            tmplist3 = []
            # jetzt erstelle für jeden y-Wert eine Liste und schau, ob sie zusammenhängend ist
            for p in tmplist:
                if p.y == uniquey:
                    tmplist3.append(p)
            # jetzt ist in tmplist3 eine Liste an Beeten, die alle die selbe y-Koordinate haben und die alle oben einen Zaun haben
            tmplist4 = []
            for p in tmplist3:
                tmplist4.append(p.x)
            # Jetzt haben wir eine Liste der x-Werte der Beete aus tmplist3
            tmplist4.sort()
            # Die x-Werte sind jetzt sortiert.
            # Jetzt bilde die Differenzen
            difflist = []
            for i in range(len(tmplist4) - 1):
                difflist.append(tmplist4[i + 1] - tmplist4[i])
            fencecount = 1
            for i in difflist:
                if i > 1:
                    fencecount = fencecount + 1
            regionsides = regionsides + fencecount

    for direction in 2,8:
    # Jetzt die x-Werte prüfen
        tmplist = []

        # Zaun oben
        for fenceelement in a.perimeterfence:
            if fenceelement.fencedir & direction == 0: continue
            tmplist.append(fenceelement.p)

        # In der Liste sind jetzt alle Fences, die oben einen Zaun haben
        # Suche raus, welche x-Werte das sind
        tmplist2 = []
        for p in tmplist:
            tmplist2.append(p.x)
        tmpset2 = set(tmplist2) # nur die unique values interessieren uns

        
        for uniquey in tmpset2:
            tmplist3 = []
            # jetzt erstelle für jeden x-Wert eine Liste und schau, ob sie zusammenhängend ist
            for p in tmplist:
                if p.x == uniquey:
                    tmplist3.append(p)
            # jetzt ist in tmplist3 eine Liste an Beeten, die alle die selbe x-Koordinate haben und die alle links einen Zaun haben
            tmplist4 = []
            for p in tmplist3:
                tmplist4.append(p.y)
            # Jetzt haben wir eine Liste der y-Werte der Beete aus tmplist3
            tmplist4.sort()
            # Die y-Werte sind jetzt sortiert.
            # Jetzt bilde die Differenzen
            difflist = []
            for i in range(len(tmplist4) - 1):
                difflist.append(tmplist4[i + 1] - tmplist4[i])
            fencecount = 1
            for i in difflist:
                if i > 1:
                    fencecount = fencecount + 1
            regionsides = regionsides + fencecount
    # print(f"Sides in region: {regionsides}, Area: {a.area}, Price: {regionsides * a.area}")
    sides = sides + regionsides * a.area
print(f"Kosten neu: {sides}")