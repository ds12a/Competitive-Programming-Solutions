/*
ID: david.y3
LANG: C++
TASK: fence
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   23 April 2022
// PROBLEM ID           :   fence
// PROBLEM DESCRIPTION  :   Find Euclidean path (Hierholzer’s algorithm)
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <set>
#include <stack>
#include <vector>

std::multiset<int> fences[501];

int main()
{
    std::ifstream fin("fence.in");
    int f, a, b;
    std::set<int> intersections;

    fin >> f;

    for (int i = 0; i < f; i++)
    {
        fin >> a >> b;

        fences[a].insert(b);
        fences[b].insert(a);
        intersections.insert(a);
        intersections.insert(b);
    }

    int start = 1;

    for (int i : intersections)
    {
        if (fences[i].size() % 2 == 1)
        {
            start = i;
            break;
        }
    }

    std::vector<int> backwardPath;
    std::stack<int> currPath;
    int at = start;

    currPath.push(start);

    while (!currPath.empty())
    {
        if (fences[at].size() > 0)
        {
            currPath.push(at);

            int next = *fences[at].begin();
            fences[at].erase(fences[at].begin());
            fences[next].erase(fences[next].find(at));

            at = next;
        }
        else 
        {
            backwardPath.push_back(at);

            at = currPath.top();
            currPath.pop();
        }
    }

    std::ofstream fout("fence.out");

    for (int i = f; i >= 0; i--)
    {
        fout << backwardPath[i] << '\n';
    }
}