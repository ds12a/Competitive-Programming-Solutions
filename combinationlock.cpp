/*
ID: david.y3
LANG: C++
TASK: combo
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   combo
// PROBLEM DESCRIPTION  :   Print combonations that open lock given master
//                          Use counting
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :
#include <cmath>

#include <fstream>
#include <iostream>
#include <unordered_set>

int n, a;

int keepInDial(int x)
{
    if (x > n)
        return keepInDial(x - n);
    else if (x < 1)
        return keepInDial(n + x);
    else
        return x;
}

bool within2(int x, int y)
{
    return std::abs(x - y) <= 2 || std::abs(x - y) >= (n - 2);
}

int getOverlap(int x, int y)
{
    std::unordered_set<int> withinBoth;
    for (int i = 0; i <= 2; i++)
    {
        if (within2(x + i, y))
            withinBoth.insert(keepInDial(x + i));
        if (within2(x - i, y))
            withinBoth.insert(keepInDial(x - i));
    }
    return withinBoth.size();
}
int getNumWithin2(int x)
{
    std::unordered_set<int> within = {x};
    for (int i = 1; i <= 2; i++)
    {
        within.insert(keepInDial(x + i));
        within.insert(keepInDial(x - i));
    }
    return within.size();
}
int main()
{
    std::ifstream fin("combo.in");

    int farmer[3], master[3];

    fin >> n;

    for (int i = 0; i < 3; i++)
    {
        fin >> farmer[i];
    }
    for (int i = 0; i < 3; i++)
    {
        fin >> master[i];
    }

    // Multiply possiblities to get total
    long long totalCombos =
        getNumWithin2(farmer[0]) * getNumWithin2(farmer[1]) * getNumWithin2(farmer[2]) +
        getNumWithin2(master[0]) * getNumWithin2(master[1]) * getNumWithin2(master[2]) -
        getOverlap(farmer[0], master[0]) * getOverlap(farmer[1], master[1]) * getOverlap(farmer[2], master[2]);

    std::ofstream fout("combo.out");
    
    fout << totalCombos << '\n';
}