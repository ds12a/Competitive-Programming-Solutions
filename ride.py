"""
ID: david.y3
LANG: PYTHON3
TASK: ride
"""

letters = ('A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z')
comet_product = 1
group_product = 1

data = open('ride.in', 'r').readlines()

comet = data[0].strip()
group = data[1].strip()


for comet_character in comet:
    comet_product *= letters.index(comet_character)+1

for group_character in group:
    group_product *= letters.index(group_character)+1

if comet_product%47 == group_product%47:
    status = "GO\n"
else:
    status = "STAY\n"

with open('ride.out','w') as output:
    output.write(status)
