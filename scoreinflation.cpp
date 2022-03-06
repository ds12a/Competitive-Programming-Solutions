/*
ID: david.y3
LANG: C++
TASK: inflate
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int maxPointsWithinTime[10001]{0};

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
                maxPointsWithinTime[t] = std::max(
                    maxPointsWithinTime[t], maxPointsWithinTime[t - problemInfo[i].second] + problemInfo[i].first);
            }
        }
    }

    std::ofstream fout("inflate.out");
    fout << maxPointsWithinTime[m] << '\n';
}