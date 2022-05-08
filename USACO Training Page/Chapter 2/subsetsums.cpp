/*
ID: david.y3
LANG: C++
TASK: subset
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   subset
// PROBLEM DESCRIPTION  :   Number of partitions that sum up to n
//                          Dynamic programming over current sum
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <iostream>

long long sumUpTo[800];

int main()
{
    std::ifstream fin("subset.in");
    std::ofstream fout("subset.out");
    long long n;

    fin >> n;

    long long totalSum = n * (n + 1) / 2;

    if (totalSum % 2 == 1)
    {
        fout << "0\n";
        return 0;
    }

    sumUpTo[0] = 1;

    for (long long i = 1; i <= n; i++)
    {
        for (long long j = totalSum - i; j >= 0; --j)
        {
            // std::cerr << "Calculating " << j + i << " using " << j << '\n';
            // std::cerr << sumUpTo[j + i] << " + " << sumUpTo[j] << '\n';
            sumUpTo[j + i] += sumUpTo[j];
        }
    }

    fout << sumUpTo[totalSum / 2] / 2 << '\n';
}