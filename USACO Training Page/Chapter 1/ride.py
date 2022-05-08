"""
ID: david.y3
LANG: PYTHON3
TASK: ride
"""
"""
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   ride
// PROBLEM DESCRIPTION  :   
//                          Simulation
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :
"""

# Instead of this tuple, I could have instead used ASCII values
letters = ('A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z')

comet_product = 1
group_product = 1

# Read-only from file
data = open('ride.in', 'r').readlines()

# Trim extra whitespace
comet = data[0].strip()
group = data[1].strip()

# Compute products
for comet_character in comet:
    comet_product *= letters.index(comet_character) + 1

for group_character in group:
    group_product *= letters.index(group_character) + 1

# Compute status
if comet_product % 47 == group_product % 47:
    status = "GO\n"
else:
    status = "STAY\n"

with open('ride.out','w') as output:
    output.write(status)
