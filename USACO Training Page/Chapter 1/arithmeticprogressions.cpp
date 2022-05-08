/*
ID: david.y3
LANG: C++
TASK: ariprog
*/
// NAME                 :   David Shen
// GROUP                :   
// LAST MODIFIED        :   11 March 2022
// PROBLEM ID           :   ariprog
// PROBLEM DESCRIPTION  :   Print bisquare sequences given length and upper bound
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :   
// PEOPLE I HELPED      :   

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int distToNext[125001];

int main()
{
    std::ifstream fin("ariprog.in");
    std::ofstream fout("ariprog.out");

    int n, m;
    fin >> n >> m;
    
    std::set<int> collection;

    for (int p = 0; p <= m; ++p)
    {
        for (int q = 0; q <= m; ++q)
        {
            collection.insert(p * p + q * q);
        }
    }

    // calculate differences to put in distToNext
    int last = 0;
    for (int element : collection)
    {
        distToNext[last] = element - last;
        last = element;
    }

    distToNext[0] = 1;
    distToNext[last] = 1;

    // iterate b and a
    int sizeMax = m * m * 2;
    std::vector<std::pair<int, int>> answers;

    // Brute force search
    for (int a : collection)
    {
        int maxB = (sizeMax - a) / (n - 1) + 1;
        
        for (int b = distToNext[a]; b <= maxB; b++)
        {
            int cur = a;
            bool works = true;

            // check all elements
            for (int i = 1; i < n; ++i)
            {
                cur += b;
                if (distToNext[cur] == 0)
                {
                    // Curr is not bisquare!
                    works = false;
                    break;
                }
            }
            if (works)
            {
                answers.push_back({b, a});
            }
        }
    }

    if (answers.size() == 0)
    {
        fout << "NONE\n";
    }
    else
    {
        std::sort(answers.begin(), answers.end());

        for (auto ans : answers)
        {
            fout << ans.second << ' ' << ans.first << '\n';
        }
    }
}