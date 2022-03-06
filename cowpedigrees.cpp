/*
ID: david.y3
LANG: C++
TASK: nocows
*/
#include <cmath>
#include <fstream>
#include <iostream>
const int MOD = 9901;
int pedigrees[200][100]; // num cows, height

int main()
{
    std::ifstream fin("nocows.in");
    int n, k;
    fin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (i == 1)
            {
                pedigrees[i][j] = 1;
            }
            else
            {
                for (int l = 1; l <= i - 2; l++)
                {
                    pedigrees[i][j] += pedigrees[l][j - 1] * pedigrees[i - l - 1][j - 1];
                }
                pedigrees[i][j] %= MOD;
            }
        }
    }
    std::ofstream fout("nocows.out");
    fout << ((pedigrees[n][k] - pedigrees[n][k - 1]) % MOD) << '\n';
}