/*
ID: david.y3
LANG: C++
TASK: inflate
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   inflate
// PROBLEM DESCRIPTION  :   Maximize points earnable within given time
//                          Dynamic programming over max points in time, time as index
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int maxPointsWithinTime[10001];

int main()
{
    std::ifstream fin("inflate.in");
    int m, n;

    fin >> m >> n; // Total minutes, problem classes

    std::vector<std::pair<int, int>> problemInfo; // points, time

    int points, timeNeeded;
    for (int i = 0; i < n; i++)
    {
        fin >> points >> timeNeeded;
        maxPointsWithinTime[timeNeeded] = points;
        problemInfo.push_back({points, timeNeeded});
    }

    for (int t = 0; t <= m; t++)
    {
        for (int i = 0; i < problemInfo.size(); i++)
        {
            if (t - problemInfo[i].second >= 0)
            {
                maxPointsWithinTime[t] = std::max(maxPointsWithinTime[t], maxPointsWithinTime[t - problemInfo[i].second] + problemInfo[i].first);
            }
        }
    }

    std::ofstream fout("inflate.out");
    fout << maxPointsWithinTime[m] << '\n';
}