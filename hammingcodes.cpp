/*
ID: david.y3
LANG: C++
TASK: hamming
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

int getHamming(int a, int b)
{
    return __builtin_popcount(a ^ b);
}

int main()
{
    std::ifstream fin("hamming.in");
    int n, b, d;
    fin >> n >> b >> d;
    int found = 0, maxNum = std::pow<int>(2, b);
    std::vector<int> solutions;
    for (int i = 0; i < maxNum && found < n; i++)
    {
        bool works = true;
        for (int sol : solutions)
        {
            int hamming = getHamming(sol, i);
            if (hamming < d)
            {
                works = false;
                break;
            }
        }
        if (works)
        {
            solutions.push_back(i);
            found++;
        }
    }
    std::sort(solutions.begin(), solutions.end());

    std::ofstream fout("hamming.out");
    for (int i = 0; i < solutions.size(); i++)
    {
        fout << solutions.at(i);
        // if (i < solutions.size() - 1) fout << ' ';
        if ((i + 1) % 10 == 0 && i < solutions.size() - 1)
            fout << '\n';
        else if (i < solutions.size() - 1)
            fout << ' ';
    }
    fout << '\n';
}