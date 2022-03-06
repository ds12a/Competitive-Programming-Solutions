/*
ID: david.y3
LANG: C++
TASK: concom
*/
#include <algorithm>
#include <fstream>
#include <vector>

std::ifstream fin("concom.in");
std::ofstream fout("concom.out");

int owns[101][101];
bool ctrl[101][101];

void controls(int i, int j)
{
    if (ctrl[i][j])
        return;
    ctrl[i][j] = true;
    for (int k = 0; k <= 100; k++)
        owns[i][k] += owns[j][k];
    for (int k = 0; k <= 100; k++)
        if (ctrl[k][i])
            controls(k, j);
    for (int k = 0; k <= 100; k++)
        if (owns[i][k] > 50)
            controls(i, k);
}

void own(int i, int j, int p)
{
    for (int k = 0; k <= 100; k++)
        if (ctrl[k][i])
            owns[k][j] += p;
    for (int k = 0; k <= 100; k++)
        if (owns[k][j] > 50)
            controls(k, j);
}

int main()
{
    int T;
    fin >> T;
    for (int i = 0; i <= 100; i++)
        ctrl[i][i] = 1;
    for (int t = 0; t < T; t++)
    {
        int i, j, p;
        fin >> i >> j >> p;
        own(i, j, p);
    }
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            if (i != j && ctrl[i][j])
                fout << i << " " << j << '\n';
}