/*
ID: david.y3
LANG: C++
TASK: milk
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    std::ifstream fin("milk.in");
    int n, m, a, b;
    std::vector<std::pair<int, int>> farmers; // price, unitsAvailable
    fin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        fin >> a >> b;
        farmers.push_back({a, b});
    }
    std::sort(farmers.begin(), farmers.end());
    int farmerID = 0, totalCost = 0;
    while (n > 0)
    {
        totalCost += std::min(n, farmers[farmerID].second) * farmers[farmerID].first;
        n -= farmers[farmerID].second;
        farmerID++;
    }
    std::ofstream fout("milk.out");
    fout << totalCost << '\n';
}