/*
ID: david.y3
LANG: C++
TASK: concom
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   concom
// PROBLEM DESCRIPTION  :   Determine which companies control which companies given rules
//                          Simulation
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <vector>

int owns[101][101];
bool ctrl[101][101];

void controls(int i, int j)
{
    if (ctrl[i][j])
        return;

    ctrl[i][j] = true;
    
    // i gets j's percentages of company k
    for (int k = 0; k <= 100; k++)
        owns[i][k] += owns[j][k];
    // companies that control i control j
    for (int k = 0; k <= 100; k++)
        if (ctrl[k][i])
            controls(k, j);
    for (int k = 0; k <= 100; k++)
        if (owns[i][k] > 50)
            controls(i, k);
}

// Company i, company j, percentage p
void own(int i, int j, int p)
{
    // Companies that control i also own p% more of j
    for (int k = 0; k <= 100; k++)
        if (ctrl[k][i])
            owns[k][j] += p;

    for (int k = 0; k <= 100; k++)
        if (owns[k][j] > 50)
            controls(k, j);
}

int main()
{
    int t;
    std::ifstream fin("concom.in");
    std::ofstream fout("concom.out");

    fin >> t;

    for (int i = 0; i <= 100; i++)
        ctrl[i][i] = 1;

    for (int i = 0; i < t; i++)
    {
        int j, k, p;
        fin >> j >> k >> p;
        own(j, k, p);
    }

    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            if (i != j && ctrl[i][j])
                fout << i << " " << j << '\n';
}