"""
ID: david.y3
LANG: PYTHON3
TASK: friday
"""
"""
// NAME                 :   David Shen
// GROUP                :   
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   friday
// PROBLEM DESCRIPTION  :   Find num of days who's date is 13 per day in the week
                            Complete search
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :   
// PEOPLE I HELPED      :   
"""

def is_leap(year):
    if year % 4 == 0:
        if year % 100 == 0:
            if year % 400 == 0:
                leap = True
            else:
                leap = False
        else:
            leap = True
    else:
        leap = False
    return leap


daily_values = [0, 0, 0, 0, 0, 0, 0]
days_per_month = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
year = 1900
index = 1

with open('friday.in', 'r') as file:
    years = int(file.read().strip())

for y in range(years):
    for month in days_per_month:
        if is_leap(year) and (month == 28):
            month = 29
        day = 1
        for days in range(month):
            if day == 13:
                daily_values[index] += 1
            day += 1

            index = (index+1) % 7
    year += 1

with open('friday.out', 'w') as file:
    file.write(
        f'{daily_values[6]} {daily_values[0]} {daily_values[1]} {daily_values[2]} {daily_values[3]} {daily_values[4]} {daily_values[5]}')
    file.write('\n')
