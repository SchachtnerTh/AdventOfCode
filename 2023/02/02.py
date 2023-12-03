import re

redcubes = 12
greencubes = 13
bluecubes = 14
gamesum = 0
sumpower = 0
with open("input") as file:
    for line in file:
        maxred = 0
        maxgreen = 0
        maxblue = 0
        p1 = line.split(":")
        # in p1 ist sowohl die Nummer des Spiels als auch alle Züge
        p1[0] = re.search(r'\d+', p1[0]).group()
        p1[1] = p1[1].split(";")
        # Jetzt sind zwar alle Züge noch in p1, aber in Listenform
        for runde in p1[1]:
            # In runde ist jetzt eine komplette Runde (mit mehreren Farben)
            blue = 0
            green = 0
            red = 0
            zug = runde.split(",")
            # zug ist jetzt eine Liste mit allen Zügen in einer Runde
            for x in zug:
                info = x.split()
                if (info[1] == "red"):
                    red = info[0]
                if (info[1] == "green"):
                    green = info[0]
                if (info[1] == "blue"):
                    blue = info[0]
#            print("rot: ", red, ", blau: ", blue, ", green: ", green)
            red = int(red)
            blue = int(blue)
            green = int (green)
            if red > maxred:
                maxred = red
            if blue > maxblue:
                maxblue = blue
            if green > maxgreen:
                maxgreen = green
        if (maxblue <= bluecubes) and (maxgreen <= greencubes) and (maxred <= redcubes):
            gamesum += int(p1[0])
            print ("Spiel ", p1[0], " wäre möglich gewesen.")
        else:
            print ("Spiel ", p1[0], " wäre NICHT möglich gewesen.");
        power = maxblue * maxgreen * maxred
        sumpower += power
print("Lösung Teil 1: ", gamesum)
print("Lösung Teil 2: ", sumpower)

