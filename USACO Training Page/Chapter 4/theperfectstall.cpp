/*
ID: david.y3
LANG: C++17
TASK: stall4
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   3 June 2022
// PROBLEM ID           :   stall4
// PROBLEM DESCRIPTION  :   Calculate Max Flow through graph (Max-matching)
//                          Edmonds–Karp algorithm
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cstring>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

std::map<int, int> flow[405];
bool processed[405];

const int DRAIN = 403;
const int SOURCE = 402;

int main()
{
    std::ifstream fin("stall4.in");
    int n, m, s, a;

    fin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        fin >> s;

        for (int j = 0; j < s; j++)
        {
            fin >> a;

            flow[SOURCE][a] = 1;
            flow[a][201 + i]++;
        }

        flow[201 + i][DRAIN] = 1;
    }

    int maxMilk = 0;

    while (true)
    {
        // {{current interesection, current minimum flow capacity}, {path}}
        std::queue<std::pair<std::pair<int, int>, std::vector<int>>> toProcess;
        int minCapacity = -1;
        std::vector<int> pathFound;

        toProcess.push({{SOURCE, INT32_MAX}, {}});

        // BFS
        while (!toProcess.empty())
        {
            int at = toProcess.front().first.first;
            int min = toProcess.front().first.second;
            std::vector<int> path = toProcess.front().second;

            toProcess.pop();

            if (processed[at] || min == 0)
            {
                continue;
            }
            processed[at] = true;

            path.push_back(at);

            // Drain reached
            if (at == DRAIN)
            {
                minCapacity = min;
                pathFound = path;
                break;
            }

            for (std::pair<int, int> f : flow[at])
            {
                toProcess.push({{f.first, std::min(min, f.second)}, path});
            }
        }
        // No more paths
        if (minCapacity == -1)
        {
            break;
        }

        // Adjust capacities
        for (unsigned int i = 0; i < pathFound.size() - 1; i++)
        {
            flow[pathFound[i]][pathFound[i + 1]] -= minCapacity;
            flow[pathFound[i + 1]][pathFound[i]] += minCapacity;
        }

        // Increment to answer
        maxMilk += minCapacity;

        // Reset
        std::memset(processed, false, sizeof(processed));
    }

    std::ofstream fout("stall4.out");
    fout << maxMilk << '\n';
}