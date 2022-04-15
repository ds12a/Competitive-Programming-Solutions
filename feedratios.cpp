/*
ID: david.y3
LANG: C++
TASK: ratios
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   15 April 2022
// PROBLEM ID           :   ratios
// PROBLEM DESCRIPTION  :   Achieve desired feed ratio with minimum feeds used
//                          Dynamic Programming over multiples
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <array>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

const int MAX = 100;
// mix ratios, feedCount, multiple, feed counts
std::map<std::array<int, 3>, std::pair<std::pair<int, int>, std::array<int, 3>>> multiples;

struct Feed
{
    int a;
    int b;
    int c;
    int aCount;
    int bCount;
    int cCount;
};

int main()
{
    std::ifstream fin("ratios.in");
    int a, b, c;

    fin >> a >> b >> c;

    Feed goal = {a, b, c, 0, 0, 0};

    std::vector<Feed> feeds;

    for (int i = 0; i < 3; i++)
    {
        fin >> a >> b >> c;

        int counts[3] = {0, 0, 0};
        counts[i] = 1;

        Feed other = {a, b, c, counts[0], counts[1], counts[2]};

        feeds.push_back(other);
    }
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            for (int k = 0; k < MAX; k++)
            {
                int m = (i * feeds[0].a + j * feeds[1].a + k * feeds[2].a) / goal.a;
                std::array<int, 3> multiplied = {m * goal.a, m * goal.b, m * goal.c};
                std::array<int, 3> current = {i * feeds[0].a + j * feeds[1].a + k * feeds[2].a, i * feeds[0].b + j * feeds[1].b + k * feeds[2].b, i * feeds[0].c + j * feeds[1].c + k * feeds[2].c};
                
                if (multiplied == current)
                {
                    if (multiples.count(current) && multiples[current].first.first > (i + j + k))
                    {
                        multiples[current].first.first = i + j + k;
                        multiples[current].first.second = m;
                        multiples[current].second = {i, j, k};
                    }
                    else
                    {
                        multiples[current].first.first = i + j + k;
                        multiples[current].first.second = m;
                        multiples[current].second = {i, j, k};
                    }
                }
            }
        }
    }
    std::array<int, 3> x = {0, 0, 0};
    int minFeeds = INT32_MAX;
    std::array<int, 3> minCounts = {0, 0, 0};
    int minMult = 1;

    for (auto counts : multiples)
    {
        if (x != counts.first && counts.second.first.first < minFeeds)
        {
            minFeeds = counts.second.first.first;
            minMult = counts.second.first.second;
            minCounts = counts.second.second;
        }
       // std::cerr << counts.first[0] << ' ' << counts.first[1] << ' ' << counts.first[2] << '\n';
    }

    
    std::ofstream fout("ratios.out");
    if (minCounts == x)
    {
        fout << "NONE\n";
    }
    else
    {
        fout << minCounts[0] << ' ' << minCounts[1] << ' ' << minCounts[2] << ' ' << minMult << '\n';
    }
}
