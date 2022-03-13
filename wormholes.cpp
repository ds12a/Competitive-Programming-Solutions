/*
ID: david.y3
LANG: C++
TASK: wormhole
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   wormhole
// PROBLEM DESCRIPTION  :   Determine how many states can lead to infinite loops
//                          Complete search
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

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
        // start from i
        start = i;

        // run for n steps
        for (int c = 0; c < n; c++)
        {
            start = getRight(nextWormhole[start]);

            if (start == -1)
            {
                // No wormhole to go to, no cycle, return false
                break;
            }
        }
        // after n steps and start still is wormhole, there is cycle!
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
        // Test if infinite cycle exists
        if (hasCycle() == true)
            solutions++;
        return;
    }

    for (int j = i + 1; j < n; j++)
    {
        // if not paired yet, then pair it
        if (nextWormhole[i] == -1 && nextWormhole[j] == -1)
        {
            // pair the two together
            nextWormhole[i] = j, nextWormhole[j] = i;
            // generate remaining pairs
            solve();
            // reset
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
    // I HATE WRITING SOLVE FUNCTIONS BUT I HAVE TO
    solve();

    std::ofstream fout("wormhole.out");
    fout << solutions << '\n';
}