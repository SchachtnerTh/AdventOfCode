# -*- coding: utf-8
import re
import sys
print (sys.argv[1])
sum = 0
with open(sys.argv[1]) as file:
    Matrix = [line.strip() for line in file]
lines = len(Matrix)
cols = len(Matrix[0])
for line in range(lines):
    findings = re.finditer(r'\d+', Matrix[line])
    # findings = re.findall(r'\d+', Matrix[line])
    for occurrance in findings:
        i = occurrance.start()
        # i = Matrix[line].index(occurrance)
        l = len(occurrance.group())
        li = rechts = o = u = False
        if i > 0:
            li = True
        if i < cols - l:
            rechts = True
        if line > 0:
            o = True
        if line < lines - 1:
            u = True
#        print (i, l, occurrance)
        part = False
#        print (o, rechts, u, li)
        if (li and Matrix[line][i - 1] != ".") or (rechts and Matrix[line][i + l] != "."): 
            part = True
#            print ("l/r")
        for pos in range(l):
            if (o and Matrix[line - 1][i + pos] != ".") or (u and Matrix[line + 1][i + pos] != "."): 
                part = True
#                print ("o/u")
        if (o == True and li == True and Matrix[line - 1][i - 1] != ".") or (o == True and rechts == True and Matrix[line - 1][i + l] != ".") or (u == True and li == True and Matrix[line + 1][i - 1] != ".") or (u == True and rechts == True and Matrix[line + 1][i + l] != "."): 
            part = True
#            print ("diag")
#        if (o == True and li == True and Matrix[line - 1][i - 1] != "."): 
#            part = True
#            print ("diag o-li")
#        if (o == True and rechts == True and Matrix[line - 1][i + l] != "."): 
#            part = True
#            print ("diag o-re: Matrix[" + str(line-1) + "][" + str(i+l) + "]")
#        if (u == True and li == True and Matrix[line + 1][i - 1] != "."): 
#            part = True
#            print ("diag u-li")
#        if (u == True and rechts == True and Matrix[line + 1][i + l] != "."): 
#            part = True
#            print ("diag u-re")
        if part:
            print(occurrance.group() + " is part")
            sum += int(occurrance.group())
            print (sum)
        else:
            print ("NOT: " + str(occurrance.group()) + "("+str(line)+","+str(i)+")")
            print(sum)
# for line in Matrix: print(line)
print ("y: " + str(lines) + ", x: " + str(cols))
print ("Ergebnis: " , sum)
