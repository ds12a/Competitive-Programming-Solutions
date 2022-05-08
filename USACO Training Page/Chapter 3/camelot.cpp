/*
ID: david.y3
LANG: C++
TASK: camelot
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   8 May 2022
// PROBLEM ID           :   camelot
// PROBLEM DESCRIPTION  :   Determine minimum knight and king moves on a chessboard with modified rules 
//                          to move pieces to same square
//                          BFS and Brute Force
//                          Note to self: When you fix an error, MAKE SURE THE ERROR ISN'T REPEATED IN OTHER PLACES!!!
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cmath>
#include <fstream>
#include <queue>
#include <vector>

int r, c;
std::pair<int, int> king;
std::vector<std::pair<int, int>> knights;
int distance[31][27][31][27];
const int THRESHOLD = 2;
const int MAX = 1 << 20;

int main()
{
    std::ifstream fin("camelot.in");

    fin >> r >> c;

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            for (int k = 1; k <= r; k++)
            {
                for (int l = 1; l <= c; l++)
                {
                    distance[i][j][k][l] = MAX;
                }
            }
        }
    }

    char a;
    int b;

    fin >> a >> b;

    king = {b, a - 'A' + 1};

    while (true)
    {
        fin >> a >> b;
        if (fin.fail())
        {
            break;
        }

        knights.push_back({b, a - 'A' + 1});
    }

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            std::queue<std::pair<std::pair<int, int>, int>> next;
            next.push({{i, j}, 0});

            while (!next.empty())
            {
                int x = next.front().first.first;
                int y = next.front().first.second;
                int dist = next.front().second;

                next.pop();

                if(x > r || y > c || y < 1 || x < 1) continue;
                if (distance[i][j][x][y] <= dist)
                    continue;

                distance[i][j][x][y] = dist;

                next.push({{x + 1, y + 2}, dist + 1});
                next.push({{x + 2, y + 1}, dist + 1});
                next.push({{x - 1, y + 2}, dist + 1});
                next.push({{x - 2, y + 1}, dist + 1});
                next.push({{x + 1, y - 2}, dist + 1});
                next.push({{x + 2, y - 1}, dist + 1});
                next.push({{x - 1, y - 2}, dist + 1});
                next.push({{x - 2, y - 1}, dist + 1});
            }
        }
    }

    int cost = MAX;

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            int rawDist = 0;

            for (auto knight : knights)
            {
                rawDist += distance[i][j][knight.first][knight.second];
            }

            for (int k = std::max(1, king.first - THRESHOLD); k <= std::min(king.first + THRESHOLD, r); k++)
            {
                for (int l = std::max(1, king.second - THRESHOLD); l <= std::min(king.second + THRESHOLD, c); l++)
                {
                    int kCost = std::max(std::abs(k - king.first), std::abs(l - king.second));

                    for (auto knight : knights)
                    {
                        int add = distance[i][j][k][l] + distance[k][l][knight.first][knight.second] + kCost -
                                  distance[i][j][knight.first][knight.second];
                        cost = std::min(cost, rawDist + add);
                    }
                }
            }
        }
    }

    std::ofstream fout("camelot.out");
    fout << ((cost == MAX) ? 0 : cost) << '\n';
}