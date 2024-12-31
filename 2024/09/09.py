import sys

class Fileblock:
    id
    count: int

    def __init__(self, id, count):
        self.id = id
        self.count = count

    def __repr__(self):
        a = f"({self.count}x {self.id})"
        return a

with open(sys.argv[1]) as file:
    for line in file:
        points = list(line.rstrip())

type = 0
id = 0

full = []
full2 = []

print()

for i in points:
    count = int(i)
    if type == 0:
        for c in range(count):
            full.append(id)
        id = id + 1
        type = 1
    else:
        for c in range(count):
            full.append('.')
        type = 0

type = 0
id = 0
for i in points:
    if type == 0:
        full2.append(Fileblock(id, i))
        id = id + 1
        type = 1
    else:
        full2.append(Fileblock('.', i))
        type = 0

## Hier ist full noch unoptimiert

while True:
    f = full.index('.') # first free space
    l = len(full)

    s1 = l - 1
    while full[s1] == '.':
        s1 = s1 - 1

    lastDigitPos = s1

    if f > lastDigitPos: break

    full[f] = full[lastDigitPos]
    full[lastDigitPos] = '.'

pos = 0

checksum = 0

while pos < l:
    if full[pos] == '.': break
    checksum = checksum + full[pos] * pos
    pos = pos + 1

# print(full)
# print(full2)
print(checksum)

l = len(full2)
for i in range(l - 1, 0, -1):
    if full2[i].id != '.':
        # wir haben eie tauschbare Datei
        for j in range(l):
            if j >= i: break
            if full2[j].id == '.' and int(full2[j].count) >= int(full2[i].count):
                full2[j].id = full2[i].id
                full2[i].id = '.'
                addfree = int(full2[j].count) - int(full2[i].count)
                full2[j].count = full2[i].count
                full2.insert(j + 1, Fileblock('.', addfree))
                # consolidate free
                neighbours = 1
                while neighbours == 1:
                    neighbours = 0
                    for k in range(l - 1, 0, -1):
                        if k < len(full2) and full2[k].id == '.' and full2[k - 1].id == '.':
                            neighbours = 1
                            full2[k - 1].count = int(full2[k].count) + int(full2[k - 1].count)
                            del full2[k]
                        if neighbours == 1 : break
                break

for i in range(l - 1, 0, -1):
    if i < len(full2) and int(full2[i].count) == 0: del full2[i]

full3 = []

for w in range(len(full2)):
    for u in range(int(full2[w].count)):
        full3.append(full2[w].id)

checksum2 = 0
pos = 0

while pos < len(full3):
    if full3[pos] != '.':
        checksum2 = checksum2 + full3[pos] * pos
    pos = pos + 1


# print(full2)
# print(full3)
print(checksum2)