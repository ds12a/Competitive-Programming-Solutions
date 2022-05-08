/*
ID: david.y3
LANG: C++
TASK: castle
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   castle
// PROBLEM DESCRIPTION  :   Determine largest room that can be created by removing
//                          a wall in the castle, print wall and max room size
//                          Floodfill, binary nums
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

const int WEST = 1, NORTH = 2, EAST = 4, SOUTH = 8;
int encodedWalls[50][50], roomSize[50][50], comps[50][50];
bool visited[50][50];

int m, n;
void debug(int i, int j)
{
    std::cerr << (encodedWalls[i][j] & NORTH) << '\n';
    std::cerr << (encodedWalls[i][j] & EAST) << '\n';
    std::cerr << (encodedWalls[i][j] & SOUTH) << '\n';
    std::cerr << (encodedWalls[i][j] & WEST) << '\n';
}
// For debugging
void printLayout()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cerr << comps[i][j] << ' ';
            if (comps[i][j] < 10)
                std::cerr << ' ';
        }
        std::cerr << '\n';
    }
    std::cerr << '\n';

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cerr << roomSize[i][j] << ' ';
            if (roomSize[i][j] < 10)
                std::cerr << ' ';
        }
        std::cerr << '\n';
    }
}
bool hasHigherPriority(char a, char b)
{ // returns true if a has higher priority than b
    return (a == 'N') > (b == 'N');
}
// Floodfill, gets sizes of rooms
void fillIn(int x, int y, int val)
{
    if (x < 0 || y < 0 || x > n || y > m || roomSize[x][y] == val)
        return;
    roomSize[x][y] = val;

    if (!(encodedWalls[x][y] & NORTH))
        fillIn(x - 1, y, val);
    if (!(encodedWalls[x][y] & EAST))
        fillIn(x, y + 1, val);
    if (!(encodedWalls[x][y] & SOUTH))
        fillIn(x + 1, y, val);
    if (!(encodedWalls[x][y] & WEST))
        fillIn(x, y - 1, val);
}
// Floodfill, 
int getRoomSize(int x, int y, int comp, int reached = 0)
{
    if (x < 0 || y < 0 || x > n || y > m || visited[x][y])
        return reached;
    // std::cerr << "Visited: " << x << ' ' << y << " Reached: " << reached << " Component: " << comp << '\n';
    visited[x][y] = true;
    comps[x][y] = comp;

    reached++;

    if (!(encodedWalls[x][y] & NORTH))
        reached = getRoomSize(x - 1, y, comp, reached);
    if (!(encodedWalls[x][y] & EAST))
        reached = getRoomSize(x, y + 1, comp, reached);
    if (!(encodedWalls[x][y] & SOUTH))
        reached = getRoomSize(x + 1, y, comp, reached);
    if (!(encodedWalls[x][y] & WEST))
        reached = getRoomSize(x, y - 1, comp, reached);

    fillIn(x, y, reached);
    return reached;
}

int main()
{
    std::ifstream fin("castle.in");
    fin >> m >> n;
    int encoded;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fin >> encodedWalls[i][j];
        }
    }

    int numRooms = 0, maxRoom = 0;
    // Fill components, find largest
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!visited[i][j])
            {
                // std::cerr << "Component Starting at " << i << ' ' << j << '\n';
                maxRoom = std::max(maxRoom, getRoomSize(i, j, numRooms));
                numRooms++;
            }
        }
    }
    std::pair<std::pair<int, int>, char> wallToRemove = {{m, 0}, 'N'};
    int maxRoomWithoutAWall = -1;
    // Test breaking down each wall and compute room size, store maximum along with
    // which wall
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool doesNotHaveLocationPriority =
                j > wallToRemove.first.second || (j == wallToRemove.first.second && i < wallToRemove.first.first);
            // std::cerr << wallToRemove.first.first << ' ' << wallToRemove.first.second << ' ' << i << ' ' << j << ' '
            // << doesNotHaveLocationPriority << ' ' << hasHigherPriority(wallToRemove.second, 'E') << '\n';
            if (j < m - 1 && encodedWalls[i][j] & EAST)
            {
                if (maxRoomWithoutAWall <= roomSize[i][j] + roomSize[i][j + 1] && comps[i][j] != comps[i][j + 1])
                {
                    if (!(maxRoomWithoutAWall == roomSize[i][j] + roomSize[i][j + 1] &&
                          (doesNotHaveLocationPriority || hasHigherPriority(wallToRemove.second, 'E'))))
                    {
                        maxRoomWithoutAWall = roomSize[i][j] + roomSize[i][j + 1];
                        wallToRemove = {{i, j}, 'E'};
                    }
                }
            }
            if (i > 0 && encodedWalls[i][j] & NORTH)
            {
                if (maxRoomWithoutAWall <= roomSize[i][j] + roomSize[i - 1][j] && comps[i][j] != comps[i - 1][j])
                {
                    if (!(maxRoomWithoutAWall == roomSize[i][j] + roomSize[i - 1][j] &&
                          (doesNotHaveLocationPriority || hasHigherPriority(wallToRemove.second, 'N'))))
                    {
                        maxRoomWithoutAWall = roomSize[i][j] + roomSize[i - 1][j];
                        wallToRemove = {{i, j}, 'N'};
                    }
                }
            }
        }
    }
    std::ofstream fout("castle.out");
    fout << numRooms << '\n';
    fout << maxRoom << '\n';
    fout << maxRoomWithoutAWall << '\n';
    fout << wallToRemove.first.first + 1 << ' ' << wallToRemove.first.second + 1 << ' ' << wallToRemove.second << '\n';
    // printLayout();
}