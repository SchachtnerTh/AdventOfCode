import sys

stones = []
origstones = []

class StonelistItem:
    stones: list
    count: int
    next25: int
    begin: int

    def __init__(self, begin: int, stoneliste: list):
        self.stones = stoneliste.copy()
        self.count = len(self.stones)
        self.begin = begin
        self.next25 = 0

    def __repr__(self):
        return f"Aus Stein {self.begin} werden nach 25 Runden {self.count} Steine und nach 50 Runden {self.next25}."

    def __str__(self):
        return f"Aus Stein {self.begin} werden nach 25 Runden {self.count} Steine und nach 50 Runden {self.next25}."
    
    def get25(self):
        if self.next25 != 0:
            return self.next25
        else:
            summe2 = 0
            for stone in self.stones:
                if stone in stonelist:
                    sli = stonelist[stone]
                else:
                    sli = StonelistItem(stone, stone25(stone))
                    stonelist[stone] = sli
                summe2 = summe2 + sli.count
            self.next25 = summe2
            return summe2




stonelist = {}

def stone25(initstone: int):
    stones = []
    stones.append(initstone)
    for blink in range(25):
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
    return stonesnew

with open(sys.argv[1]) as file:
    for line in file:
        stones = list(map(int, line.split()))

print(stones)
origstones = stones.copy()

summe1 = 0
for stone in stones:
    if stone in stonelist:
        sli = stonelist[stone].stones
    else:
        sli = StonelistItem(stone, stone25(stone))
        stonelist[stone] = sli
    summe1 = summe1 + sli.count

sum3 = 0
for i in stones:
    print (f"Stone {i}")
    for level2 in stonelist[i].stones:
        # print(f" - sub for stone1 {i} and stone2 {level2}")
        if level2 not in stonelist:
            sli = StonelistItem(level2, stone25(level2))
            stonelist[level2] = sli
        sum3 = sum3 + stonelist[level2].get25()

# print (sum3)
# print(stonelist)
print(f"Nach 25 Runden sind es insgesamt {summe1} Steine.")
print(f"Nach 25 Runden sind es insgesamt {sum3} Steine.")