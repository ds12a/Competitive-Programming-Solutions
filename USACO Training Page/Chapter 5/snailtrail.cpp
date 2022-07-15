/*
ID: david.y3
LANG: C++17
TASK: snail
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   15 July 2022
// PROBLEM ID           :   snail
// PROBLEM DESCRIPTION  :   Determine longest path in graph
//                          DFS, bruteforce
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cmath>
#include <fstream>

bool barrier[121][121];
bool visited[121][121];
int n, b;

struct Location
{
    int row = 0, col = 0;
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

bool isValid(Location l)
{
    return l.row >= 1 && l.col >= 1 && l.row <= n && l.col <= n && !barrier[l.row][l.col];
}

int getDistance(Location &p, Location &q)
{
    return std::abs(p.row - q.row + p.col - q.col);
}

// DFS, returns longest path
int maxDistance(Location at, Location from, Direction d, int dist = 0)
{
    if (!isValid(at) || visited[at.row][at.col])
        return dist + getDistance(at, from);

    visited[at.row][at.col] = true;
    dist += getDistance(at, from);

    // Can shortcut, no barriers
    if (at.col > 26 && d == Direction::RIGHT)
    {
        int toReturn = std::max(maxDistance({at.row, n}, at, Direction::UP, dist),
                                maxDistance({at.row, n}, at, Direction::DOWN, dist));
        visited[at.row][at.col] = false;
        return toReturn;
    }
    // Can shortcut, no barriers
    if (at.col > 28 && d == Direction::LEFT)
    {
        int toReturn = maxDistance({at.row, 28}, at, d, dist);
        visited[at.row][at.col] = false;
        return toReturn;
    }

    Location next = {at.row + dy[d], at.col + dx[d]};

    if (isValid(next))
    {
        int toReturn = maxDistance(next, at, d, dist);
        visited[at.row][at.col] = false;
        return toReturn;
    }
    else
    {
        if (d == Direction::UP || d == Direction::DOWN)
        {
            int toReturn = std::max(
                maxDistance({at.row + dy[Direction::LEFT], at.col + dx[Direction::LEFT]}, at, Direction::LEFT, dist),
                maxDistance({at.row + dy[Direction::RIGHT], at.col + dx[Direction::RIGHT]}, at, Direction::RIGHT,
                            dist));
            visited[at.row][at.col] = false;
            return toReturn;
        }
        else
        {
            int toReturn = std::max(
                maxDistance({at.row + dy[Direction::UP], at.col + dx[Direction::UP]}, at, Direction::UP, dist),
                maxDistance({at.row + dy[Direction::DOWN], at.col + dx[Direction::DOWN]}, at, Direction::DOWN, dist));
            visited[at.row][at.col] = false;
            return toReturn;
        }
    }
}
int main()
{
    std::ifstream fin("snail.in");

    fin >> n >> b;

    for (int i = 0; i < b; i++)
    {
        char col;
        int row;

        fin >> col >> row;

        barrier[row][col - 'A' + 1] = true;
    }

    // Calculate longest path if snail moves down first
    int downAnswer = maxDistance({1, 1}, {1, 1}, Direction::DOWN);

    // Reset visited
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            visited[i][j] = false;
        }
    }
    std::ofstream fout("snail.out");
    // Output maximum path length (starts down or starts to the right)
    fout << std::max(downAnswer, maxDistance({1, 1}, {1, 1}, Direction::RIGHT)) << '\n';
}