/*
ID: david.y3
LANG: C++
TASK: agrinet
*/
#include <fstream>
#include <queue>

int distance[100][100], n;
bool inMinSpanningTree[100];

int main()
{
    std::ifstream fin("agrinet.in");
    fin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> distance[i][j];
        }
    }

    std::priority_queue<std::pair<int, int>> q;

    q.push({0, 0});

    int minSpanningTreeTotalCost = 0;
    while (!q.empty())
    {
        int cost = -q.top().first, destination = q.top().second;
        q.pop();

        if (inMinSpanningTree[destination])
            continue;

        inMinSpanningTree[destination] = true;
        minSpanningTreeTotalCost += cost;

        for (int i = 0; i < n; i++)
        {
            if (!inMinSpanningTree[i])
            {
                q.push({-distance[destination][i], i});
            }
        }
    }

    std::ofstream fout("agrinet.out");
    fout << minSpanningTreeTotalCost << '\n';
}