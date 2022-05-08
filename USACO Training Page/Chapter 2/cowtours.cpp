/*
ID: david.y3
LANG: C++
TASK: cowtour
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   cowtour
// PROBLEM DESCRIPTION  :   Determine smallest diameter of graph composed of 2 graphs
//                          Floyd-Warshaw while computing farthest points, then compute
//                          minumum sum of two distances
//                          Simulation
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

const long long INF = 1e15;
const double EPSION = 1e-9;

std::vector<std::pair<int, int>> pastures;
double distance[150][150], ans = INF;
int n, furthestFromPasture[150];

double getDist(std::pair<int, int> a, std::pair<int, int> b)
{
    return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
}

int main()
{
    std::ifstream fin("cowtour.in");
    fin >> n;

    int x, y;
    for (int i = 0; i < n; i++)
    {
        fin >> x >> y;
        pastures.push_back({x, y});
    }

    char connected;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> connected;
            if (connected == '1')
            {
                distance[j][i] = distance[i][j] = getDist(pastures.at(i), pastures.at(j));
            }
            else
                distance[i][j] = INF;
            if (i == j)
                distance[j][i] = distance[i][j] = 0;
        }
    }

    // Floyd-Warshall algo
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                distance[j][i] = distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);

                if ((distance[i][j] > distance[i][furthestFromPasture[i]] &&
                     std::fabs(distance[i][j] - INF) > EPSION) ||
                    std::fabs(distance[i][furthestFromPasture[i]] - INF) < EPSION)
                {
                    furthestFromPasture[i] = j;
                    furthestFromPasture[j] = i;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (std::fabs(distance[i][j] - INF) < EPSION)
            {
                int furthestFromI = furthestFromPasture[i], furthestFromJ = furthestFromPasture[j];
                ans = std::min(ans, distance[i][furthestFromI] + distance[j][furthestFromJ] +
                                        getDist(pastures.at(i), pastures.at(j)));
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (ans < distance[i][furthestFromPasture[i]])
        {
            ans = distance[i][furthestFromPasture[i]];
        }
    }
    std::ofstream fout("cowtour.out");
    fout << std::fixed << std::setprecision(6) << ans << '\n';
}