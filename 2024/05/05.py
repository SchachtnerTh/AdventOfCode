import sys

rules=[]
data=[]

def check(pages):   # die aktuellen Seiten werden an die Funktion übergeben
    valid = 1       # gehe davon aus, dass alles passt
    for rule in rules:  # durchlaufe alle Regeln
        first,then = list(map(int, rule.split('|')))    # Teile die Regeln in einen "first"-Teil und in einen "then"-Teil
        if (first in pages and then in pages and pages.index(then) < pages.index(first)):   # Wenn aus einer Regel beide Seiten in den aktuellen Seiten enthalten sind, aber die falsche Reihenfolge haben...
            valid = 0                   # setze zuerst valid auf 0, da es ja einen Fehler gibt
            t = pages.index(then)       # Hole die Position, an der die Seite "then" steht
            f = pages.index(first)      # Hole die Position, an der die Seite "first" steht

            h = pages[t]                # Schreibe die Seite "then" in eine Hilfsvariable
            pages[t] = pages[f]         # Schreibe an diese Stelle die Seite "first"
            pages[f] = h                # Schreibe an die Stelle, an die die Seite "first" steht, jetzt die Seite "then", die vorher in der Hilfsvariable zwischengespeichert wurde
                                        # ... und mach das auch mit allen anderen Regeln noch
    return valid                        # liefere "valid" zurück (also 1, wenn alles gepasst hat oder 0 wenn mindestens einmal vertauscht wurde)

with open(sys.argv[1]) as file:
    rules_section = 1   # Lies zuerst alle Regeln in eine Liste
    for line in file:
        if line == "\n":
            rules_section = 0   # Wenn eine leere Zeile kommt, schalte um und lies die folgenden Zeilen in eine andere Liste (data).
            continue
        if rules_section == 1:
            rules.append(line)  # Hänge an die erste Liste an (rules)
        else:
            data.append(line)   # Hänge an die zweite Liste an (data)

sum = 0
sum2 = 0

for manual in data:
    # print(manual)
    pages = []
    pages = list(map(int,manual.split(',')))                # Lies alle Seiten in eine Liste

    valid = check(pages)                                    # Prüfe, ob die Seiten so passen und sortiere um, wenn nicht

    if valid == 1:                                          # Wenn alles passt, aktualisiere die Summe (Teilaufgabe 1)
        # print("OK " + str(pages[int(len(pages) / 2)]))
        sum = sum + int(pages[int(len(pages) / 2)])

    else:
        while valid == 0:                                   # Wenn nicht alles passt, führe die Check- und Umordnung so lange durch, bis alles passt ...
            valid = check(pages)
        # print("NG " + str(pages[int(len(pages) / 2)]))
        sum2 = sum2 + int(pages[int(len(pages) / 2)])       # ... und bilde dann eine weitere Summe (Teilaufgabe 2)
    # print(pages)
        
print ("Erste Summe: " + str(sum))
print ("Zweite Summe: " + str(sum2))