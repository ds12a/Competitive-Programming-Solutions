/*
ID: david.y3
LANG: C++
TASK: butter
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   18 April 2022
// PROBLEM ID           :   butter
// PROBLEM DESCRIPTION  :   Find point closest to all other points, points are weighted
//                          Dijkstra's algorithm over all pastures
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <vector>
#include <queue>

bool processed[801][801];
int cowsAt[801];
int dist[801][801];
std::vector<std::pair<int, int>> connected[801];

int main()
{
    std::ifstream fin("butter.in");
    int n, p, c, l;

    fin >> n >> p >> c;

    for (int i = 1; i <= p; i++)
    {
        for (int j = 1; j <= p; j++)
        {
            dist[i][j] = 1e5;
        }
    }

    for (int i = 0; i < n; i++)
    {
        fin >> l;
        cowsAt[l]++;
    }

    int a, b, d;
    for (int i = 0; i < c; i++)
    {
        fin >> a >> b >> d;

        connected[a].push_back({b, d});
        connected[b].push_back({a, d});
    }

    for (int i = 1; i <= p; i++)
    {
        // Let i be the meeting point
        std::priority_queue<std::pair<int, int>> next;
        next.push({0, i});

        dist[i][i] = 0;

        while (!next.empty())
        {
            int pasture = next.top().second;

            next.pop();

            if (processed[i][pasture])
            {
                continue;
            }

            processed[i][pasture] = true;

            for (std::pair<int, int> nextP : connected[pasture])
            {
                if (nextP.second + dist[i][pasture] < dist[i][nextP.first])
                {
                    dist[i][nextP.first] = nextP.second + dist[i][pasture];
                    next.push({-dist[i][nextP.first], nextP.first});
                }
            }
        }
    }

    int minDistSum = INT32_MAX;

    for (int i = 1; i <= p; i++)
    {
        int sum = 0;
        for (int j = 1; j <= p; j++)
        {
            sum += cowsAt[j] * dist[i][j];
        }
        minDistSum = std::min(minDistSum, sum);
    }

    std::ofstream fout("butter.out");
    fout << minDistSum << '\n';
}