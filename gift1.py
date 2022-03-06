"""
ID: david.y3
LANG: PYTHON3
TASK: gift1
"""

people = {}
EXPECTING_GIVER = True
lines_passed = 0
recievers = 0
data = open('gift1.in', 'r').readlines()

np = int(data[0].strip())

for x in range(np):
    if x >= np:
        break

    name = data[1:][x].strip()
    people[name] = 0
print(people)
for x in data[(np+1):]:
    x = x.strip()
    print(x)
    lines_passed += 1
    if EXPECTING_GIVER and x in people:
        print(f"Giver: {x}")
        giver = x
        #lines_passed = 0
        EXPECTING_GIVER = False
    elif not x in people:
        print(f"Numbers: {x}")
        amount = int(x.split()[0])
        recievers = int(x.split()[1])
        try:
            people[giver] -= amount - (amount % recievers)
        except ZeroDivisionError:
            pass
        lines_passed = 0
    elif x in people:
        print(f"Reciever: {x}")
        people[x] += amount//recievers

    if lines_passed == recievers:
        EXPECTING_GIVER = True
with open('gift1.out', 'w') as output:
    for person in people:
        output.write(f"{person} {people[person]}\n")
