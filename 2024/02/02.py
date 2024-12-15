# coding=UTF-8

import sys

data = []
safecount = 0
unsafe = 0

print ("\nPart 1")

def direction(l):
    for i,a in enumerate(l):
        if (i < len(l) - 1):
            if (l[i] < l[i + 1]):
                return 1
            if (l[i] > l[i + 1]):
                return -1
    return 0


with open(sys.argv[1]) as file:
    for line in file:
        data = list(map(int, line.split()))
        # print(data)
        l = len(data)
        if (l > 1):
            if (direction(data) == 1):
                # wird größer
                # print ("wird größer")
                safe = 1
                for i,a in enumerate(data):
                    if (i < l -1):
                        if safe == 1:
                            if ((data[i + 1] - data[i] > 3) or (data[i + 1] - data[i] < 1)):
                                safe = 0
                # if (safe == 1): print("safe")
            elif (direction(data) == -1):
                # wird kleiner
                # print ("wird kleiner")
                safe = 1
                for i,a in enumerate(data):
                    if (i < l -1):
                        if safe == 1:
                            if ((data[i] - data[i + 1] > 3) or (data[i] - data[i + 1] < 1)):
                                safe = 0
                # if (safe == 1): print("safe")
            else:
                print("FEHLER")
                # exit()
                # Fehler
            if safe == 1: safecount = safecount + 1
            safe = 0
    print("Safe lines: " + str(safecount))

    safe = 0
    safecount = 0

    print ("\nPart 2")
    skipnext = 0

    with open(sys.argv[1]) as file:
        for line in file:
            data = list(map(int, line.split()))
            # print(data)
            data2 = []
            for i,a in enumerate(data):
                if (i < len(data) - 1):
                    data2.append(data[i + 1] - data[i])
            # print(data2)


            # negativ
            ok = 1
            negatives = 0
            positives = 0
            sames = 0
            oor = 0
            for e in data2:
                if (e < 0): 
                    negatives = negatives + 1
                    if (e < -3): 
                        oor = oor + 1
                if (e > 0):
                    positives = positives + 1
                    if (e > 3): 
                        oor = oor + 1
                if (e == 0):
                    sames = sames + 1

            # print ("+/-/max/0: " + str(positives) + "/" + str(negatives) + "/" + str(oor) + "/" + str(sames))

            # Wenn alle positiv sind oder alle negativ UND wenn kein oor dabei ist, ist es safe

            l2 = len(data2)

            if ((positives == l2 or negatives == l2) and (oor == 0)): 
                safecount = safecount + 1
                # print ("safe")
                continue

            if (sames != 1 or oor != 1 or (positives != 0 and negatives != 0)):
                done = 0
                for i,a in enumerate(data2):
                    if done == 0:
                        if (i < l2 -1):
                            data3 = []
                            for j,a in enumerate(data2):
                                if (j < l2 - 1):
                                    if (j < i): data3.append(data2[j])
                                    if (j == i): data3.append(data2[j] + data2[j+1])
                                    if (j > i): data3.append(data2[j+1])
                            neg2 = 0
                            pos2 = 0
                            sam2 = 0
                            oor2 = 0
                            for e2 in data3:
                                if (e2 < 0): 
                                    neg2 = neg2 + 1
                                    if (e2 < -3): 
                                        oor2 = oor2 + 1
                                if (e2 > 0):
                                    pos2 = pos2 + 1
                                    if (e2 > 3): 
                                        oor2 = oor2 + 1
                                if (e2 == 0):
                                    sam2 = sam2 + 1
                            l3 = len(data3)
                            # print ("*")
                            # print (data3)
                            if ((pos2 == l3 or neg2 == l3) and (oor2 == 0)):
                                # print ("***")
                                # print(data3)
                                safecount = safecount + 1
                                done = 1
                                continue

                            # ersten weglassen
                            # print("ersten weglassen")
                            data3 = data2.copy()
                            del data3[0]
                            neg2 = 0
                            pos2 = 0
                            sam2 = 0
                            oor2 = 0
                            for e2 in data3:
                                if (e2 < 0): 
                                    neg2 = neg2 + 1
                                    if (e2 < -3): 
                                        oor2 = oor2 + 1
                                if (e2 > 0):
                                    pos2 = pos2 + 1
                                    if (e2 > 3): 
                                        oor2 = oor2 + 1
                                if (e2 == 0):
                                    sam2 = sam2 + 1
                            l3 = len(data3)
                            # print ("*")
                            # print (data3)
                            if ((pos2 == l3 or neg2 == l3) and (oor2 == 0)):
                                # print ("***")
                                # print(data3)
                                safecount = safecount + 1
                                done = 1
                                continue

                            # letzten weglassen
                            # print("letzten weglassen")
                            data3 = data2.copy()
                            del data3[len(data3) - 1]
                            neg2 = 0
                            pos2 = 0
                            sam2 = 0
                            oor2 = 0
                            for e2 in data3:
                                if (e2 < 0): 
                                    neg2 = neg2 + 1
                                    if (e2 < -3): 
                                        oor2 = oor2 + 1
                                if (e2 > 0):
                                    pos2 = pos2 + 1
                                    if (e2 > 3): 
                                        oor2 = oor2 + 1
                                if (e2 == 0):
                                    sam2 = sam2 + 1
                            l3 = len(data3)
                            # print ("*")
                            # print (data3)
                            if ((pos2 == l3 or neg2 == l3) and (oor2 == 0)):
                                # print ("***")
                                # print(data3)
                                safecount = safecount + 1
                                done = 1
                                continue


            # print("\n")                    

        print("Safe lines: " + str(safecount))
