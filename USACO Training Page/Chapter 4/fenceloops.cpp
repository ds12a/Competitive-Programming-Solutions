/*
ID: david.y3
LANG: C++17
TASK: fence6
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   28 May 2022
// PROBLEM ID           :   fence6
// PROBLEM DESCRIPTION  :   Find shortest cycle in graph
//                          Dijkstra's algorithm over each segment
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>

std::pair<std::unordered_set<int>, std::unordered_set<int>> connectedTo[101];
int length[101];

int distance[101];
bool processed[101];

int main()
{
    std::ifstream fin("fence6.in");
    int n;

    fin >> n;

    for (int i = 0; i < n; i++)
    {
        int s, l, n1, n2, segment;

        fin >> s >> l >> n1 >> n2;

        length[s] = l;

        for (int j = 0; j < n1; j++)
        {
            fin >> segment;

            connectedTo[s].first.insert(segment);
        }

        for (int j = 0; j < n2; j++)
        {
            fin >> segment;

            connectedTo[s].second.insert(segment);
        }
    }

    int minPerimeter = INT32_MAX;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            distance[j] = INT32_MAX / 4;
            processed[j] = false;
        }

        std::priority_queue<std::pair<std::pair<int, int>, std::pair<int, int>>>
            toProcess; // {-Dist, segment id}, {prev, first}
        toProcess.push({{0, i}, {-1, -1}});

        while (!toProcess.empty())
        {
            int dist = -toProcess.top().first.first;
            int segmentID = toProcess.top().first.second;
            int prev = toProcess.top().second.first;
            int first = toProcess.top().second.second;

            toProcess.pop();

            if (processed[segmentID])
            {
                continue;
            }

            processed[segmentID] = true;

            if (first != -1)
            {
                std::unordered_set<int> &segmentsBeforeReturning =
                    connectedTo[i].first.find(first) == connectedTo[i].first.end() ? connectedTo[i].first
                                                                                   : connectedTo[i].second;

                if (segmentsBeforeReturning.find(segmentID) != segmentsBeforeReturning.end())
                {
                    minPerimeter = std::min(minPerimeter, dist + length[segmentID]);
                    continue;
                }
            }

            std::unordered_set<int> &next =
                connectedTo[segmentID].first.find(prev) == connectedTo[segmentID].first.end()
                    ? connectedTo[segmentID].first
                    : connectedTo[segmentID].second;

            for (int connectedSeg : next)
            {
                if (distance[connectedSeg] > dist + length[segmentID])
                {
                    distance[connectedSeg] = dist + length[segmentID];
                    toProcess.push(
                        {{-distance[connectedSeg], connectedSeg}, {segmentID, (first == -1) ? connectedSeg : first}});
                }
            }
        }
    }

    std::ofstream fout("fence6.out");
    fout << minPerimeter << '\n';
}