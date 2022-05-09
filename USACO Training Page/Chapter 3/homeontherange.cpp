/*
ID: david.y3
LANG: C++
TASK: range
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   9 May 2022
// PROBLEM ID           :   range
// PROBLEM DESCRIPTION  :   Find squares in grid of varing sizes, count them
//                          2D Prefix sum
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <map>
#include <iostream>

int prefixSum[251][251];

int main()
{
    std::ifstream fin("range.in");
    int n;
    char c;

    fin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fin >> c; 

            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + (c - '0');
        }
    }

    std::map<int, int> answers;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 2; std::max(i, j) + k - 1 <= n; k++)
            {
                int readyToEatCount = prefixSum[i + k - 1][j + k - 1] - prefixSum[i - 1][j + k - 1] - prefixSum[i + k - 1][j - 1] + prefixSum[i - 1][j - 1];
                if (readyToEatCount == k * k)
                {
                    answers[k]++;
                }
            }
        }
    }

    std::ofstream fout("range.out");

    for (std::pair<int, int> p : answers)
    {
        fout << p.first << ' ' << p.second << '\n';
    }
}