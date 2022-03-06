/*
ID: david.y3
LANG: C++
TASK: wormhole
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

std::set<std::pair<int, int>> wormholes;
std::map<std::pair<int, int>, int> toInt;
std::vector<std::pair<int, int>> toWormhole;
int n, nextWormhole[12], solutions = 0;

int getRight(int current)
{
    auto it = wormholes.upper_bound(toWormhole[current]);
    // std::cerr << toWormhole[current].first << ' ' << toWormhole[current].second << ' ' << it->first << ' ' <<
    // it->second << '\n';
    if (it == wormholes.end() || it->first != toWormhole[current].first)
        return -1;

    return toInt[*it];
}
bool hasCycle()
{
    int start;
    for (int i = 0; i < n; i++)
    {
        // explore start from `i`
        start = i;

        // let's explore with minimum N steps
        // we can be sure that after N steps, it will restarts over again creating cycle
        for (int c = 0; c < n; c++)
        {
            start = getRight(nextWormhole[start]);
            // -1 = that's mean the cow doesn't found any wormhole and stepping out of bound
            // return false as there's no cycle
            if (start == -1)
                break;
        }
        if (start != -1)
            return true;
    }

    return false;
}

void solve()
{
    // find last point who's not paired yet
    int i;
    for (i = 0; i < n; i++)
        if (nextWormhole[i] == -1)
            break;

    // if all point already paired
    if (i == n)
    {
        if (hasCycle() == true)
            solutions++;
        return;
    }

    for (int j = i + 1; j < n; j++)
    {
        // if not paired yet, then pair it
        if (nextWormhole[i] == -1 && nextWormhole[j] == -1)
        {
            // pair the two points together
            nextWormhole[i] = j, nextWormhole[j] = i;
            // go down the tree and generate all left pairs
            solve();
            // reset for other pair with `i`
            nextWormhole[i] = nextWormhole[j] = -1;
        }
    }
}
int main()
{
    std::ifstream fin("wormhole.in");
    fin >> n;
    int a, b;
    for (int i = 0; i < n; i++)
    {
        fin >> a >> b;
        wormholes.insert({b, a});
        toWormhole.push_back({b, a});
        toInt[{b, a}] = i;
        nextWormhole[i] = -1;
    }
    solve();
    std::ofstream fout("wormhole.out");
    fout << solutions << '\n';
}