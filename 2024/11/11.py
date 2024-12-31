import sys

stones = []
origstones = []

with open(sys.argv[1]) as file:
    for line in file:
        stones = list(map(int, line.split()))

print(stones)
origstones = stones.copy()

class CacheElement:
    begin: int
    result: list
    rounds: int

    def __init__(self, begin, result, rounds):
        self.begin = begin
        self.rounds = rounds
        self.result = result.copy()

class Cache:
    cache: list

    def addOrUpdate(self, begin, result, rounds):
        replaced = 0
        for element in self.cache:
            if element.begin == begin and element.rounds < rounds:
                replaced = 1
                element.rounds = rounds
                element.result = result.copy()
        if replaced == 0:
            ce = CacheElement(begin, result, rounds)
            self.cache.append(ce)

    def __init__(self):
        self.cache = []




for j in range(25):
    print(j, end=' ', flush=True)
    stonesnew = []
    for i, stone in enumerate(stones):
        if stone == 0:
            stone = 1
            stonesnew.append(stone)
        else:
            if len(str(stone)) % 2 == 0:
                s = str(stone)
                idx = int(len(str(stone))/2)

                stone = int(s[:idx])
                stone2 = int(s[idx:])
                stonesnew.append(stone)
                stonesnew.append(stone2)
            else:
                stone = stone * 2024
                stonesnew.append(stone)
    stones = stonesnew.copy()
    print(len(stones))

print (len(stonesnew))       # in eine andere Liste
print("---------------------------")

uniquestones = []

for stone in stonesnew:
    if not stone in uniquestones:
        uniquestones.append(stone)

print (f"Anzahl unterschiedliche Steine: {len(uniquestones)}")

stonelist = []

for s2 in uniquestones:
    stones2 = []
    stones2.append(s2)
    
    for sl in stonelist:
        if sl.begin == s2: 
            print("*", end='')
            continue

    ce = CacheElement(s2, [], 0)
    for j in range(25):
        stonesnew = []
        # print(j, end=' ', flush=True)
        for i, stone in enumerate(stones2):
            if stone == 0:
                stone = 1
                stonesnew.append(stone)
            else:
                if len(str(stone)) % 2 == 0:
                    s = str(stone)
                    idx = int(len(str(stone))/2)

                    stone = int(s[:idx])
                    stone2 = int(s[idx:])
                    stonesnew.append(stone)
                    stonesnew.append(stone2)
                else:
                    stone = stone * 2024
                    stonesnew.append(stone)
        stones2 = stonesnew.copy()
        #print(len(stones))
    print(f"Länge: {len(stones2)}")
    ce.result = stones2.copy()
    ce.rounds = 25
    stonelist.append(ce)

print(len(stonelist))

class Stonecount:
    stone: int
    count: int

stonecountlist = []


stones.sort()
count = 1
old = 0
for i in stones:
    if i == old:
        count = count + 1
    else:
        print(f"Count for {old}: {count}")
        sc = Stonecount()
        sc.stone = old
        sc.count = count
        stonecountlist.append(sc)
        old = i
        count = 1

for item in stonecountlist:
    print(f"Stein {item.stone} kommt  {item.count} mal vor.")

sr2unique = []
sr2full=[]
for item in stonelist:
    for st in item.result:
        sr2full.append(st)
        if not st in sr2unique:
            sr2unique.append(st)

print(f"Anzahl unterschiedlicher Steine nach Runde 2: {len(sr2unique)}")
print(f"Anzahl Steine nach Runde 2: {len(sr2full)}")
kk=0
kkk=0

for s2 in sr2unique:
    stones2 = []
    stones2.append(s2)
    
    found = 0
    for sl in stonelist:
        if sl.begin == s2: 
            # print("*", end='')
            found = 1
            break
    if found == 1: continue

    ce = CacheElement(s2, [], 0)
    for j in range(25):
        stonesnew = []
        # print(j, end=' ', flush=True)
        for i, stone in enumerate(stones2):
            if stone == 0:
                stone = 1
                stonesnew.append(stone)
            else:
                if len(str(stone)) % 2 == 0:
                    s = str(stone)
                    idx = int(len(str(stone))/2)

                    stone = int(s[:idx])
                    stone2 = int(s[idx:])
                    stonesnew.append(stone)
                    stonesnew.append(stone2)
                else:
                    stone = stone * 2024
                    stonesnew.append(stone)
        stones2 = stonesnew.copy()
        #print(len(stones))
    # print(f"Länge: {len(stones2)}")
    kk = kk + 1
    if kk % 100 == 0: print(kk)
    ce.result = stones2.copy()
    ce.rounds = 25
    stonelist.append(ce)



# exit(0)






stonecountlist2 = []


sr2full.sort()
count = 1
old = 0
for i in sr2full:
    if i == old:
        count = count + 1
    else:
        print(f"Count for {old}: {count}")
        sc = Stonecount()
        sc.stone = old
        sc.count = count
        stonecountlist2.append(sc)
        old = i
        count = 1

for item in stonecountlist2:
    print(f"Stein {item.stone} kommt  {item.count} mal vor.")



for i in uniquestones:
    for k in stonelist:
        if k.begin == i:
            ss = k
            break
    #print(f"checking {len(i.result)} stones.")
    for j in ss.result:
        if not j in uniquestones:

            stones2 = []
            stones2.append(j)

            ce = CacheElement(j, [], 0)
            for j in range(25):
                stonesnew = []
                # print(j, end=' ', flush=True)
                for i, stone in enumerate(stones2):
                    if stone == 0:
                        stone = 1
                        stonesnew.append(stone)
                    else:
                        if len(str(stone)) % 2 == 0:
                            s = str(stone)
                            idx = int(len(str(stone))/2)

                            stone = int(s[:idx])
                            stone2 = int(s[idx:])
                            stonesnew.append(stone)
                            stonesnew.append(stone2)
                        else:
                            stone = stone * 2024
                            stonesnew.append(stone)
                stones2 = stonesnew.copy()
            #print(f"Länge: {len(stones2)}")
            kkk=kkk + 1
            if kkk % 1000 == 0: print(kkk)
            ce.result = stones2.copy()
            ce.rounds = 25

            # prüfe sicherheitshalber nochmal, ob die Liste scon besteht
            found2 = 0
            for t in stonelist:
                if t.begin == ce.begin:
                    found2 = 1
                    # print ("**")
            if found2 == 0:
                stonelist.append(ce)
                uniquestones.append(j)

            
print(len(uniquestones))

summe = 0

for l1 in stonecountlist:
    # aus der ersten Runde
    for t in stonelist:
        if t.begin == l1.stone:
            for l2 in t.result:
                for sl in stonelist:
                    if sl.begin == l2:
                        c = len(sl.result)
                for t2 in stonecountlist2:
                    if t2.stone == l2:
                        summe = summe + l1.count * t2.count * c
print(summe)


summe = 0
for l1 in stonecountlist2:
    for item in stonelist:
        if l1.stone == item.begin:
            summe = summe + l1.count * len(item.result)
print(summe)
