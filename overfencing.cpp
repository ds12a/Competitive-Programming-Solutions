/*
ID: david.y3
LANG: C++
TASK: maze1
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   maze1
// PROBLEM DESCRIPTION  :   Determine longest best path to escape maze 
//                          Floodfill, binary nums
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <set>
#include <stack>

const int NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8;
int maze[101][39], distFromStart[101][39], distFromEnd[101][39];
int h, w;
bool visited[101][39];

void ff(int a, int b, int dists[101][39])
{
    std::stack<std::pair<int, std::pair<int, int>>> vars;
    vars.push({1, {a, b}});

    while (!vars.empty())
    {
        int d = vars.top().first, x = vars.top().second.second, y = vars.top().second.first;

        vars.pop();

        if (visited[y][x])
        {
            if (d < dists[y][x])
            {
                dists[y][x] = d;
            }
            else
                continue;
        }

        visited[y][x] = true;
        dists[y][x] = d;

        int moves = maze[y][x];
        if (moves & NORTH)
        {
            vars.push({d + 1, {y - 1, x}});
        }
        if (moves & EAST)
        {
            vars.push({d + 1, {y, x + 1}});
        }
        if (moves & SOUTH)
        {
            vars.push({d + 1, {y + 1, x}});
        }
        if (moves & WEST)
        {
            vars.push({d + 1, {y, x - 1}});
        }
    }
}

int main()
{
    std::ifstream fin("maze1.in");

    fin >> w >> h;

    char m, junk;
    int y = 0;
    std::pair<int, int> start = {-1, -1}, end;

    fin >> std::noskipws >> junk; // REMOVE THE \n!
    for (int i = 0; i < h * 2 + 1; i++)
    {
        if (i % 2 == 0)
        { // +-+-+\n
            for (int j = 0; j <= w; j++)
            {
                fin >> std::noskipws >> junk >> m;
                if (m == ' ')
                {
                    maze[y][j] |= NORTH;
                    if (y > 0)
                        maze[y - 1][j] |= SOUTH;
                }
            }
        }
        else
        { // | | | |\n
            for (int j = 0; j <= w; j++)
            {
                fin >> std::noskipws >> m >> junk;
                if (m == ' ')
                {
                    if (j > 0)
                        maze[y][j - 1] |= EAST;
                    maze[y][j] |= WEST;
                }
            }
            y++;
        }
    }

    for (int i = 0; i < h; i++)
    {
        if (maze[i][0] & WEST)
        {
            if (start.first != -1)
            {
                end = {i, 0};
            }
            else
                start = {i, 0};
        }
        if (maze[i][w - 1] & EAST)
        {
            if (start.first != -1)
            {
                end = {i, w - 1};
            }
            else
                start = {i, w - 1};
        }
    }
    for (int i = 0; i < w; i++)
    {
        if (maze[0][i] & NORTH)
        {
            if (start.first != -1)
            {
                end = {0, i};
            }
            else
                start = {0, i};
        }
        if (maze[h - 1][i] & SOUTH)
        {
            if (start.first != -1)
            {
                end = {h - 1, i};
            }
            else
                start = {h - 1, i};
        }
    }

    ff(start.first, start.second, distFromStart);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            visited[i][j] = false;
        }
    }

    ff(end.first, end.second, distFromEnd);

    int maxDist = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            maxDist = std::max(maxDist, std::min(distFromStart[i][j], distFromEnd[i][j]));
        }
    }

    std::ofstream fout("maze1.out");
    fout << maxDist << '\n';
}