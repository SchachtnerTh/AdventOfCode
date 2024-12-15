import sys

rules=[]
data=[]

def check(pages):
    valid = 1
    for rule in rules:
        #  print(rule)
        first,then = list(map(int, rule.split('|')))
        if (first in pages and then in pages and pages.index(then) < pages.index(first)):
            valid = 0
            t = pages.index(then)
            f = pages.index(first)
            h = pages[t]
            # print(pages)
            pages[t] = pages[f]
            pages[f] = h
            # print(pages)
    return valid



with open(sys.argv[1]) as file:
    part1 = 1
    for line in file:
        if line == "\n":
            part1 = 0
            continue
        if part1 == 1:
            rules.append(line)
        else:
            data.append(line)

# print(rules)
# print(data)
# print("----------------------------------")

sum = 0
sum2 = 0

for manual in data:
    # print(manual)
    pages = []
    pages = list(map(int,manual.split(',')))

    valid = check(pages)

    if valid == 1:
        # print("OK " + str(pages[int(len(pages) / 2)]))
        sum = sum + int(pages[int(len(pages) / 2)])

    else:
        while valid == 0:
            valid = check(pages)
        # print("NG " + str(pages[int(len(pages) / 2)]))
        sum2 = sum2 + int(pages[int(len(pages) / 2)])
    # print(pages)
        
print ("Erste Summe: " + str(sum))
print ("Zweite Summe: " + str(sum2))
# print(data)
exit(0)




class Node:
    def print(self):
        print("Wert: " + str(self.value))
        print("Incoming: " + str(self.incoming))
        print("Outgoing: " + str(self.outgoing))
        print("\n")

def value2order(i):
    for node in orderednodes:
        if node.get('value') == i:
            return node.get('order')
    return -1

nodes = []

for rule in rules:
    first,then = rule.split("|")
    #print ("First: " + first + ", then " + then)

    # search in nodes
    rulefound_first = 0
    rulefound_second = 0
    for node in nodes:
        if node.value == int(first):
            rulefound_first = 1
            node.outgoing.append(int(then))
        if node.value == int(then):
            rulefound_second = 1
            node.incoming.append(int(first))
    if rulefound_first == 0:
        r = Node()
        r.value = int(first)
        r.incoming = []
        r.outgoing = []
        r.outgoing.append(int(then))
        nodes.append(r)
    if rulefound_second == 0:
        r = Node()
        r.value = int(then)
        r.incoming = []
        r.outgoing = []
        r.incoming.append(int(first))
        nodes.append(r)

# for n in nodes:
#    n.print()

orderednodes = []
order = 0


while len(nodes) > 0:
    # find empty incoming
    value = 0
    for n in nodes:
        print(len(n.incoming))
        if len(n.incoming) == 0: 
            value = n.value
            nodes.remove(n)

    if value == 0: 
        print("Fehler")
        quit(-1) # Fehler

    order = order + 1
    ordn = {'value': value, 'order':order}
    orderednodes.append(ordn)

    for n in nodes:
        if value in n.incoming:
            n.incoming.remove(value)

# print(orderednodes)

checksum = 0

for model in data:
    orders = []
    pages = list(map(int, model.split(",")))
    # print (pages)
    for page in pages:
        orders.append(value2order(page))
    # print(orders)
    wrong = 0
    for i,position in enumerate(orders):
        if i < len(orders) - 1:
            if orders[i + 1] <= orders[i]:
                wrong = 1
    if wrong == 0:
        mid = int(len(pages) / 2)
        # print(mid)
        checksum = checksum + pages[mid]
        # print (pages[mid])
print("Checksum: " + str(checksum))