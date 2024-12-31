import sys
import re
import math

def euklid(a, b):
    while b:
        a, b = b, a % b
    return a



class Point:
    x: int
    y: int
    
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, value):
        if value.x == self.x and value.y == self.y:
            return True
        else:
            return False

    def __repr__(self):
        return f"({self.x},{self.y})"

class Clawmachine:
    ax:int
    ay:int
    bx:int
    by:int
    prizex:int
    prizey:int

    def __repr__(self):
        return f"\nButton A: X+{str(self.ax)}, Y+{self.ay}\nButton B: X+{self.bx}, Y+{self.by}\nPrize: X+{self.prizex}, Y+{self.prizey}"

def checksolution (m:Clawmachine):
    ggT = euklid(m.ax, m.bx)
    if m.prizex % ggT != 0: return False
    ggT = euklid(m.ay, m.by)
    if m.prizey % ggT != 0: return False
    return True
    
machines = []
pointlist = []

with open(sys.argv[1]) as file:
    i = 0
    ax=0
    ay=0
    bx=0
    by=0
    px=0
    py=0
    for line in file:
        if i == 0:
            tmp1,tmp2, ax1, ay1 = line.split()
            ax = re.findall("\d+", ax1)[0]
            ay = re.findall("\d+", ay1)[0]
        if i == 1:
            tmp1,tmp2, bx1, by1 = line.split()
            bx = re.findall("\d+", bx1)[0]
            by = re.findall("\d+", by1)[0]
        if i == 2:
            tmp1,px1,py1 = line.split()
            px = re.findall("\d+", px1)[0]
            py = re.findall("\d+", py1)[0]
            cm = Clawmachine()
            cm.ax = int(ax)
            cm.ay = int(ay)
            cm.bx = int(bx)
            cm.by = int(by)
            cm.prizex = int(px)
            cm.prizey = int(py)
            machines.append(cm)

        i = (i + 1) % 4
debug = False
# if debug: print(machines)

#machines[0]

costs1 = 0

for m in machines:
    if checksolution(m):
        a = (m.prizex * m.by - m.prizey * m.bx) / (m.ax * m.by - m.bx * m.ay)
        b = (m.prizey * m.ax - m.prizex * m.ay) / (m.ax * m.by - m.ay * m.bx)
        if ((m.prizex * m.by - m.prizey * m.bx) % (m.ax * m.by - m.bx * m.ay) == 0 and (m.prizey * m.ax - m.prizex * m.ay) % (m.ax * m.by - m.ay * m.bx) == 0):
            # nur, wenn die Lösung aufgeht...
            # print(a,b)
            costs1 = costs1 + 3 * a + b
#    else:
#        print("Keine Lösung")
print (f"Kosten Aufgabe 1: {int(costs1)}")


for m in machines:
    m.prizex = m.prizex + 10000000000000
    m.prizey = m.prizey + 10000000000000

costs2 = 0
for m in machines:
    if checksolution(m):
        a = (m.prizex * m.by - m.prizey * m.bx) / (m.ax * m.by - m.bx * m.ay)
        b = (m.prizey * m.ax - m.prizex * m.ay) / (m.ax * m.by - m.ay * m.bx)
        if ((m.prizex * m.by - m.prizey * m.bx) % (m.ax * m.by - m.bx * m.ay) == 0 and (m.prizey * m.ax - m.prizex * m.ay) % (m.ax * m.by - m.ay * m.bx) == 0):
            # nur, wenn die Lösung aufgeht...
            # print(a,b)
            costs2 = costs2 + 3 * a + b
#    else:
#        print("Keine Lösung")
print (f"Kosten Aufgabe 2: {int(costs2)}")
