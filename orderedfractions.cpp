/*
ID: david.y3
LANG: C++
TASK: frac1
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main()
{
    std::ifstream fin("frac1.in");
    int n;
    fin >> n;
    std::vector<std::pair<int, int>> fractions;
    for (int i = 0; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (j == 0 || gcd(i, j) != 1)
                continue;
            fractions.push_back({i, j});
        }
    }
    std::sort(fractions.begin(), fractions.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
        return ((double)a.first) / a.second < ((double)b.first) / b.second;
    });
    std::ofstream fout("frac1.out");
    for (std::pair<int, int> fraction : fractions)
    {
        fout << fraction.first << '/' << fraction.second << '\n';
    }
}