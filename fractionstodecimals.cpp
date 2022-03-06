/*
ID: david.y3
LANG: C++
TASK: fracdec
*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>

std::queue<int> digits;
std::unordered_map<int, int> startingLoc;

int calculateDecimal(int a, int b)
{
    int r = a % b;
    // std::cerr << a << ' ' << b << ' ' << ' ' << a/b << ' ' << r << '\n';
    digits.push(a / b);
    if (startingLoc.count(r) && r != 0)
    {
        return startingLoc[r];
    }

    startingLoc[r] = startingLoc.size();
    if (r == 0)
        return -1;
    return calculateDecimal(10 * r, b);
}

int main()
{
    std::ifstream fin("fracdec.in");
    std::ofstream fout("fracdec.out");

    int a, b, n = 0, start, charsPrinted = 0;

    fin >> a >> b;
    fout << a / b;

    charsPrinted = std::max(0, (int)log10(a / b)) + 1;
    startingLoc[a % b] = startingLoc.size();
    start = calculateDecimal(10 * (a % b), b);

    if (!digits.empty())
    {
        fout << ".";
        charsPrinted++;
    }
    while (!digits.empty())
    {
        if (n == start)
        {
            fout << "(";
            charsPrinted++;
        }
        if (charsPrinted % 76 == 0)
            fout << '\n';
        fout << digits.front();
        charsPrinted++;
        digits.pop();
        n++;
    }
    if (start != -1)
        fout << ")";
    fout << '\n';
}