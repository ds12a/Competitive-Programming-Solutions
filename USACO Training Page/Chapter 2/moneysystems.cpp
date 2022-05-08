/*
ID: david.y3
LANG: C++
TASK: money
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   money
// PROBLEM DESCRIPTION  :   Classic money system DP problem
//                          Dynamic Programming
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <vector>

long long waysToConstructValue[10001];

int main()
{
    std::ifstream fin("money.in");
    int v, n, c;
    

    fin >> v >> n;

    std::vector<int> coinValues;

    for (int i = 0; i < v; i++)
    {
        fin >> c;
        coinValues.push_back(c);
    }

    waysToConstructValue[0] = 1;

    for (int val : coinValues)
    {
        for (int i = 1; i <= n; i++)
        {
            if (val <= i)
            {
                waysToConstructValue[i] += waysToConstructValue[i - val];
            }
        }
    }

    std::ofstream fout("money.out");
    fout << waysToConstructValue[n] << '\n';
}