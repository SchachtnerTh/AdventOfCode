from math import ceil, log
import sys

class Rule:
    result: int
    factors: list
    ok: int

    def __init__(self, result, factors):
        self.result = result
        self.factors = factors.copy()
        self.ok = 0

    def __str__(self):
        print("H" or '')
        #print ("Result " + str(self.result) + " - ")
        #print (str(self.factors))

def digit(number, base, position):
        # if (debug): print ("3er-System-Darstellung")
        poscount = 0
        it = number
        if it == 0: return 0
        while it != 0:
            ineu = int(it) / int(base)
            digit = int(it) % base
            if (debug): print(digit, end='')
            it = ineu
            if position == poscount:
                if (debug): print("")
                return digit
            else:
                poscount = poscount + 1
        if (debug): print("")
        return 0

factorstr = ""

operators = []
factors = []

debug = 0

# for i in range(27):
#     print(digit(i, 3, 2), end='')
#     print(digit(i, 3, 1), end='')
#     print(digit(i, 3, 0))
# 
# exit()


with open(sys.argv[1]) as file:
    for line in file:
        result, factorstr = line.split(":")
        result = int(result)
        factors = list(map(int, factorstr.split()))
        if (debug): print("Add: " + str(result) + str(factors))
        operators.append(Rule(result, factors.copy()))

ergebnis = 0

print("Anzahl Zeilen: " + str(len(operators)))
lcount = 0


for operator in operators:
    if (debug): print("Has " + str(len(operator.factors)) + " items.")
    count = len(operator.factors)
    if (debug): print ("**** Ergebnis-Zahl: " + str(operator.result) + ", Iterationen: " + str(pow(2, count - 1)) + ", Liste: " + str(operator.factors))
    for iteration in range(pow(2, count - 1)): # Anzahl der möglichen Kombinationen
        if (debug): print("*** Iteration " + str(iteration))
        localresult = operator.factors[0]
        if (debug): print(localresult)
        for part in range(count - 1):
            if (debug): print (iteration & (1 << part))
            if (iteration & (1 << part)):
                if (debug): print("*")
                localresult = localresult * operator.factors[part + 1]
            else:
                if (debug): print("+")
                localresult = localresult + operator.factors[part + 1]
            # print("    Ergebnis:" + str(localresult))
        if (debug): print(localresult)
        if localresult == operator.result:
            if (debug): print("    Ergebnis:" + str(localresult))
            ergebnis = ergebnis + localresult
            operator.ok = 1
            lcount = lcount + 1
            break
print(str(ergebnis))
ergebnis1 = ergebnis

ergebnis = 0

uebrig=len(operators) - lcount
print("Zeilen übrig: " + str(len(operators) - lcount))
ergebnis = 0
lcount2 = 0

for operator in operators:
    if operator.ok == 1: continue
    print(str(lcount2 + 1) + " von " + str(uebrig), end='\r')
    if (debug): print("Has " + str(len(operator.factors)) + " items.")
    count = len(operator.factors)
    if (debug): print ("**** Ergebnis-Zahl: " + str(operator.result) + ", Iterationen: " + str(pow(3, count - 1)) + ", Liste: " + str(operator.factors))
    for iteration in range(pow(3, count - 1)): # Anzahl der möglichen Kombinationen
        if (debug): print("*** Iteration " + str(iteration))
        localresult = operator.factors[0]
        if (debug): print(localresult)
        for part in range(count - 1):
            if (debug): print ("D " + str(digit(iteration, 3, part)) + " aus " + str(iteration) + "," + str(part))
            d = digit(iteration, 3, part)
            if d == 0:
                if (debug): print("||")
                localresult = int(str(localresult) + str(operator.factors[part + 1]))
                # localresult = ((localresult * 10**ceil(log(operator.factors[part + 1],10)))+operator.factors[part + 1])
                
            if d == 1:
                if (debug): print("*")
                localresult = localresult * operator.factors[part + 1]
                
            if d == 2:
                if (debug): print("+")
                localresult = localresult + operator.factors[part + 1]

            if d < 0 or d > 2:
                print("ERROR")
                exit()

            # print("    Ergebnis:" + str(localresult))
            if localresult > operator.result: 
                # print("!")
                break
        if (debug): print(localresult)
        if localresult == operator.result:
            if (debug): print("    Ergebnis:" + str(localresult))
            ergebnis = ergebnis + localresult
            break
    lcount2 = lcount2 + 1
print("")
print("zusätzlich dazugekommen: " + str(ergebnis))
print("Insgesamt: " + str(ergebnis + ergebnis1))