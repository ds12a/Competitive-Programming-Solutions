/*
ID: david.y3
LANG: C++17
TASK: race3
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   17 June 2022
// PROBLEM ID           :   race3
// PROBLEM DESCRIPTION  :   Determine which nodes of a directed graph are unavoidable when traversed and which cleanly
//                          split the graph
//                          DFS, bits
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <vector>

std::vector<int> next[51];
std::vector<int> undirected[51];
long long n = 0;

void countConnected(int node, int removed, std::vector<int> graph[], long long &visited)
{
    long long shifted = 1LL << node;
    if (visited & shifted || node == removed)
    {
        return;
    }
    visited |= shifted;
    if (node == n)
    {
        return;
    }

    for (int connected : graph[node])
    {
        countConnected(connected, removed, graph, visited);
    }
}

int main()
{
    std::ifstream fin("race3.in");

    while (true)
    {
        int x;

        fin >> x;

        if (x == -1)
        {
            break;
        }
        while (x != -2)
        {
            next[n].push_back(x);
            undirected[x].push_back(n);
            undirected[n].push_back(x);

            fin >> x;
        }
        n++;
    }

    n--;
    std::vector<int> unavoidable;

    for (int i = 1; i < n; i++)
    {
        long long visited = 0;
        countConnected(0, i, next, visited);

        if (!(visited & (1LL << (n))))
        {
            unavoidable.push_back(i);
        }
    }
    std::vector<int> splitting;

    for (int i : unavoidable)
    {
        long long visited = 0;
        countConnected(0, i, undirected, visited);

        if (!(visited & (1LL << n)))
        {
            bool falsePositive = false;
            for (int node : next[i])
            {
                if (visited & (1LL << node))
                {
                    falsePositive = true;
                    break;
                }
            }
            if (!falsePositive)
            {
                splitting.push_back(i);
            }
        }
    }
    std::sort(splitting.begin(), splitting.end());
    std::sort(unavoidable.begin(), unavoidable.end());

    std::ofstream fout("race3.out");
    fout << unavoidable.size();

    if (!unavoidable.empty())
    {
        fout << ' ';
    }
    else
    {
        fout << '\n';
    }

    for (int u : unavoidable)
    {
        fout << u;

        if (u != *unavoidable.rbegin())
        {
            fout << ' ';
        }
        else
        {
            fout << '\n';
        }
    }

    fout << splitting.size();

    if (!splitting.empty())
    {
        fout << ' ';
    }
    else
    {
        fout << '\n';
    }
    for (int s : splitting)
    {
        fout << s;

        if (s != *splitting.rbegin())
        {
            fout << ' ';
        }
        else
        {
            fout << '\n';
        }
    }
}