/*
ID: david.y3
LANG: C++
TASK: rockers
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   21 May 2022
// PROBLEM ID           :   Rockers
// PROBLEM DESCRIPTION  :   Find maximum number of songs on m disks with time limit t on each disk
//                          3D Dynamic Programming
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <vector>

// Num Disks, Time Remaining On Disk, Num Songs
int maxSongs[21][21][21];

int main()
{
    std::ifstream fin("rockers.in");
    int n, t, m;
    std::vector<int> lengths{0};
    fin >> n >> t >> m;

    for (int i = 0; i < n; i++)
    {
        int len;
        fin >> len;
        lengths.push_back(len);
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j <= t; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                maxSongs[i][j][k] = std::max(maxSongs[i][j][k - 1], maxSongs[i - 1][t][k]);
                maxSongs[i][j][k] = std::max(maxSongs[i][j][k], maxSongs[i][std::max(j - 1, 0)][k]);

                if (j >= lengths[k])
                {
                    maxSongs[i][j][k] = std::max(maxSongs[i][j][k], maxSongs[i][j - lengths[k]][k - 1] + 1);
                }
            }
        }
    }

    std::ofstream fout("rockers.out");
    fout << maxSongs[m][t][n] << '\n';
}