/*
ID: david.y3
LANG: C++
TASK: fact4
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   22 March 2022
// PROBLEM ID           :   fact4
// PROBLEM DESCRIPTION  :   Last non zero digit of n!
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>

int main()
{
    std::ifstream fin("fact4.in");
    int n;

    fin >> n;

    int lastNonZeroDigit = 1;

    for (int i = 1; i <= n; i++)
    {
        lastNonZeroDigit *= i;

        while (lastNonZeroDigit % 10 == 0)
        {
            lastNonZeroDigit /= 10;
        }
        lastNonZeroDigit %= 1000;
    }

    std::ofstream fout("fact4.out");
    fout << lastNonZeroDigit % 10 << '\n';
}