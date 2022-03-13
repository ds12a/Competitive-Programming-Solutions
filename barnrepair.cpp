/*
ID: david.y3
LANG: C++
TASK: barn1
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   barn1
// PROBLEM DESCRIPTION  :   Print max stalls that can be covered
//                          Subtract largest stalls to not cover from total stalls 
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

bool isOccupied[201];
int m, s, c, a;
std::vector<int> gapLens;

int main()
{
    std::ifstream fin("barn1.in");

    fin >> m >> s >> c;

    for (int i = 0; i < c; i++)
    {
        fin >> a;
        isOccupied[a] = true;
    }

    int gapLen = 0;

    for (int i = 1; i <= s; i++)
    {
        if (isOccupied[i])
        {
            gapLens.push_back(gapLen);
            gapLen = 0;
            continue;
        }
        gapLen++;
    }

    gapLens.push_back(gapLen);

    int stallsCovered = s;

    stallsCovered -= gapLens[0] + gapLens[gapLens.size() - 1];

    gapLens.erase(gapLens.begin());
    gapLens.erase(std::prev(gapLens.end()));

    std::sort(gapLens.rbegin(), gapLens.rend());

    while (m > 1 && gapLens.size() > 0)
    {
        stallsCovered -= gapLens[0];
        gapLens.erase(gapLens.begin());
        m--;
    }

    std::ofstream fout("barn1.out");
    fout << stallsCovered << '\n';
}