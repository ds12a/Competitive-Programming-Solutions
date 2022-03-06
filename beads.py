"""
ID: david.y3
LANG: PYTHON3
TASK: beads
"""

with open('beads.in', 'r') as file:
    data = file.readlines()
    num_beads = int(data[0].strip())
    beads = data[1].strip()

next = ()
longest = 0
current = 0
sample = ""
ls = ""
MISMATCH_OCCURED = False

for index in range(num_beads):
    character = beads[index]

    if character == 'r':
        next = ('r', 'w')
    elif character == 'b':
        next = ('b', 'w')

    right = beads[index:]

    i = index
    while True:
        bead = beads[i % num_beads]

        if bead in next:
            current += 1
            sample += bead
            if current > longest:
                longest = current
                ls = sample
        else:
            if MISMATCH_OCCURED:
                if current > longest:
                    longest = current

                current = 0
                MISMATCH_OCCURED = False
                sample = ""
                break
            else:
                character = beads[i % num_beads]
                if character == 'r':
                    next = ('r', 'w')
                elif character == 'b':
                    next = ('b', 'w')
                else:
                    next = ('w')
                sample += bead
                MISMATCH_OCCURED = True
        i += 1
        if (i % num_beads) == index:
            sample = ""
            break
    current = 0
print(longest)
print(ls)
with open('beads.out', 'w') as file:
    file.write(f"{len(ls)}\n")
