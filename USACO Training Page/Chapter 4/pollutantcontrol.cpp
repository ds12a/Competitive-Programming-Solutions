/*
ID: david.y3
LANG: C++17
TASK: milk6
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   24 June 2022
// PROBLEM ID           :   milk6
// PROBLEM DESCRIPTION  :   Min cut problem but need to identify which edges need to be cut
//                          Max-flow algo, dijkstra, complete search
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <cstring>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

std::map<int, int> routeFlow[33], routeFlowCopy[33];
std::pair<std::pair<int, int>, int> routeEdges[2001];

bool processed[33];
int minFlow[33];
int n, m;

auto cmp = [](std::pair<std::pair<int, int>, std::vector<int>> &a,
              std::pair<std::pair<int, int>, std::vector<int>> &b) { return a.first.second < b.first.second; };

int getMinCost()
{
    std::memset(processed, false, sizeof(processed));
    std::memset(minFlow, 0, sizeof(minFlow));
    int minCost = 0;

    while (true)
    {
        // {{at, min capacity}, path}
        int minCapacity = -1;
        std::vector<int> bestPath;

        std::priority_queue<std::pair<std::pair<int, int>, std::vector<int>>,
                            std::vector<std::pair<std::pair<int, int>, std::vector<int>>>, decltype(cmp)>
            next(cmp);

        next.push({{1, INT32_MAX}, {}});

        while (!next.empty())
        {
            int at = next.top().first.first;
            int min = next.top().first.second;
            std::vector<int> path = next.top().second;

            next.pop();

            if (processed[at] || min == 0)
            {
                continue;
            }

            path.push_back(at);
            processed[at] = true;

            if (at == n)
            {
                bestPath = path;
                minCapacity = min;
                break;
            }

            for (std::pair<int, int> p : routeFlow[at])
            {
                if (std::min(p.second, min) > minFlow[p.first])
                {
                    minFlow[p.first] = std::min(p.second, min);

                    next.push({{p.first, std::min(p.second, min)}, path});
                }
            }
        }
        if (minCapacity == -1)
        {
            break;
        }

        for (unsigned int i = 0; i < bestPath.size() - 1; i++)
        {
            routeFlow[bestPath[i]][bestPath[i + 1]] -= minCapacity;
            routeFlow[bestPath[i + 1]][bestPath[i]] += minCapacity;
        }

        minCost += minCapacity;

        std::memset(processed, false, sizeof(processed));
        std::memset(minFlow, 0, sizeof(minFlow));
    }

    return minCost;
}

int main()
{
    std::ifstream fin("milk6.in");
    std::vector<int> sortedIDs;

    fin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int s, e, c;

        fin >> s >> e >> c;

        routeFlow[s][e] += c;
        routeEdges[i] = {{s, e}, c};

        sortedIDs.push_back(i);
    }
    std::copy(std::begin(routeFlow), std::end(routeFlow), std::begin(routeFlowCopy));

    int minCost = getMinCost(), removedSum = 0;
    std::vector<int> toRemove;

    std::sort(sortedIDs.begin(), sortedIDs.end(),
              [](int a, int b) { return routeEdges[a].second > routeEdges[b].second; });

    for (int i : sortedIDs)
    {
        std::copy(std::begin(routeFlowCopy), std::end(routeFlowCopy), std::begin(routeFlow));

                routeFlow[routeEdges[i].first.first][routeEdges[i].first.second] -= routeEdges[i].second;

        int now = getMinCost();

        if (minCost - now != routeEdges[i].second)
        {
            routeFlow[routeEdges[i].first.first][routeEdges[i].first.second] += routeEdges[i].second;
        }
        else
        {
            removedSum += routeEdges[i].second;
            toRemove.push_back(i);

            if (removedSum == minCost)
            {
                break;
            }
        }
    }

    std::sort(toRemove.begin(), toRemove.end());

    std::ofstream fout("milk6.out");
    fout << minCost << ' ' << toRemove.size() << '\n';

    for (int i : toRemove)
    {
        fout << (i + 1) << '\n';
    }
}