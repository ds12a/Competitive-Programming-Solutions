/*
ID: david.y3
LANG: C++
TASK: shopping
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   1 May 2022
// PROBLEM ID           :   shopping
// PROBLEM DESCRIPTION  :   Dynamic programming, compress IDs
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

int code2ID[1000];
int cost[6][6][6][6][6];

int main()
{
    std::ifstream fin("shopping.in");
    int s, b, n, c, k, p;
    int nextID = 1;
    std::vector<std::pair<std::array<int, 6>, int>> buy;

    fin >> s;

    for (int i = 0; i < s; i++)
    {
        fin >> n;

        std::array<int, 6> counts = {0, 0, 0, 0, 0, 0};

        for (int j = 0; j < n; j++)
        {
            fin >> c >> k;

            if (code2ID[c] == 0)
            {
                code2ID[c] = nextID;
                nextID++;
            }

            counts[code2ID[c]] += k;
        }

        fin >> p;

        cost[counts[1]][counts[2]][counts[3]][counts[4]][counts[5]] = p;
        buy.push_back({counts, p});
    }

    fin >> b;

    std::array<int, 6> countsDesired = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < b; i++)
    {
        fin >> c >> k >> p;

        std::array<int, 6> counts = {0, 0, 0, 0, 0, 0};

        if (code2ID[c] == 0)
        {
            code2ID[c] = nextID;
            nextID++;
        }
        counts[code2ID[c]] = 1;
        countsDesired[code2ID[c]] = k;
        cost[counts[1]][counts[2]][counts[3]][counts[4]][counts[5]] = p;
        buy.push_back({counts, p});
    }

    for (int i = 0; i <= countsDesired[1]; i++)
    {
        for (int j = 0; j <= countsDesired[2]; j++)
        {
            for (int l = 0; l <= countsDesired[3]; l++)
            {
                for (int m = 0; m <= countsDesired[4]; m++)
                {
                    for (int o = 0; o <= countsDesired[5]; o++)
                    {
                        if (cost[i][j][l][m][o] == 0) cost[i][j][l][m][o] = INT32_MAX / 2;
                    }
                }
            }
        }
    }

    cost[0][0][0][0][0] = 0;
    
    for (int i = 0; i <= countsDesired[1]; i++)
    {
        for (int j = 0; j <= countsDesired[2]; j++)
        {
            for (int l = 0; l <= countsDesired[3]; l++)
            {
                for (int m = 0; m <= countsDesired[4]; m++)
                {
                    for (int o = 0; o <= countsDesired[5]; o++)
                    {
                        for (std::pair<std::array<int, 6>, int> canBuy : buy)
                        {
                            if (i - canBuy.first[1] < 0 || j - canBuy.first[2] < 0 || l - canBuy.first[3] < 0 ||
                                m - canBuy.first[4] < 0 || o - canBuy.first[5] < 0)
                            {
                                continue;
                            }
                            cost[i][j][l][m][o] = std::min(
                                cost[i][j][l][m][o], cost[i - canBuy.first[1]][j - canBuy.first[2]][l - canBuy.first[3]]
                                                         [m - canBuy.first[4]][o - canBuy.first[5]] +
                                                         canBuy.second);
                        }
                    }
            }
        }
    }
    }
    std::ofstream fout("shopping.out");
    fout << cost[countsDesired[1]][countsDesired[2]][countsDesired[3]][countsDesired[4]][countsDesired[5]] << '\n';
}