/*
ID: david.y3
LANG: C++
TASK: agrinet
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   arginet
// PROBLEM DESCRIPTION  :   Given dists, find way to connect all with minimum dist covered
//                          Prim's algo
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

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

    // Prim's algo
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
