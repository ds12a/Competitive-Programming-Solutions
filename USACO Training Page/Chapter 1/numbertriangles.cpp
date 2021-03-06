/*
ID: david.y3
LANG: C++
TASK: numtri
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   numtri
// PROBLEM DESCRIPTION  :   Find max sum when traversing number triangle
//                          Little bit of dynamic programming!
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>

int maxSum[1000][1000];
int n;

int main()
{
    std::ifstream fin("numtri.in");
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            fin >> maxSum[i][j];
        }
    }
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            maxSum[i][j] += std::max(maxSum[i + 1][j], maxSum[i + 1][std::min(j + 1, n - 1)]);
        }
    }
    std::ofstream fout("numtri.out");
    fout << maxSum[0][0] << '\n';
}