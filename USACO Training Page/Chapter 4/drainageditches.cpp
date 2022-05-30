/*
ID: david.y3
LANG: C++17
TASK: ditch
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   30 May 2022
// PROBLEM ID           :   ditch
// PROBLEM DESCRIPTION  :   Calculate Max Flow through graph
//                          Edmonds–Karp algorithm
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cstring>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

std::map<int, int> flow[201];
bool processed[201];

int main()
{
    std::ifstream fin("ditch.in");
    int n, m, a, b, c;

    fin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        fin >> a >> b >> c;

        flow[a][b] += c;
    }

    long long maxFlow = 0;

    while (true)
    {
        // {{current interesection, current minimum flow capacity}, {path}}
        std::queue<std::pair<std::pair<int, int>, std::vector<int>>> toProcess;
        int minCapacity = -1;
        std::vector<int> pathFound;

        toProcess.push({{1, INT32_MAX}, {}});

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
            if (at == m)
            {
                minCapacity = min;
                pathFound = path;
                break;
            }

            for (std::pair<int, int> ditch : flow[at])
            {
                toProcess.push({{ditch.first, std::min(min, ditch.second)}, path});
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
        maxFlow += minCapacity;

        // Reset
        std::memset(processed, false, sizeof(processed));
    }

    std::ofstream fout("ditch.out");
    fout << maxFlow << '\n';
}