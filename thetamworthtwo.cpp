/*
ID: david.y3
LANG: C++
TASK: ttwo
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   ttwo
// PROBLEM DESCRIPTION  :   Determine how long it will take for farmer and cow to meet
//                          or print zero if they do not meet
//                          Simulation until original state is reached or they meet
//                          Note: classes were probably overkill but I couldn't resist
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <set>

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};
const int MAX = 9;
const char OBSTACLE = '*';

char grid[10][10];

class GridWalker
{
  public:
    GridWalker(int a, int b, Direction c = NORTH)
    {
        x = a;
        y = b;
        dir = c;
    }
    bool move()
    { // returns true iff GridWalker changes position
        if (obstacleAhead())
        {
            turn();
            return false;
        }
        if (dir == NORTH)
        {
            y--;
        }
        else if (dir == SOUTH)
        {
            y++;
        }
        else if (dir == EAST)
        {
            x++;
        }
        else if (dir == WEST)
        {
            x--;
        }
        return true;
    }
    void turn()
    {
        dir = static_cast<Direction>((dir + 1) % 4);
    }
    bool obstacleAhead()
    {
        if (dir == NORTH)
        {
            if (y == 0 || grid[y - 1][x] == OBSTACLE)
                return true;
        }
        else if (dir == EAST)
        {
            if (x == MAX || grid[y][x + 1] == OBSTACLE)
                return true;
        }
        else if (dir == SOUTH)
        {
            if (y == MAX || grid[y + 1][x] == OBSTACLE)
                return true;
        }
        else if (dir == WEST)
        {
            if (x == 0 || grid[y][x - 1] == OBSTACLE)
                return true;
        }
        return false;
    }
    bool meetWith(GridWalker gw)
    {
        return x == gw.x && y == gw.y;
    }
    int x, y;
    Direction dir;
};

bool farmerVisited[10][10], cowsVisited[10][10];

std::set<std::pair<std::pair<std::pair<int, int>, Direction>, std::pair<std::pair<int, int>, Direction>>> states;

// Get state of current configuration
std::pair<std::pair<std::pair<int, int>, Direction>, std::pair<std::pair<int, int>, Direction>> getState (GridWalker f, GridWalker c)
{
    return {{{f.x, f.y}, f.dir}, {{c.x, c.y}, c.dir}};
}

int main()
{
    std::ifstream fin("ttwo.in");
    int farmerX, farmerY, cowsX, cowsY;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fin >> grid[i][j];
            if (grid[i][j] == 'F')
            {
                farmerX = j;
                farmerY = i;
            }
            else if (grid[i][j] == 'C')
            {
                cowsX = j;
                cowsY = i;
            }
        }
    }

    GridWalker farmer(farmerX, farmerY), cows(cowsX, cowsY);
    int timeUsed = 0;
    bool meet = false;
    std::pair<std::pair<std::pair<int, int>, Direction>, std::pair<std::pair<int, int>, Direction>> current = getState(farmer, cows);

    // Simulate untill they meet
    do
    {
        states.insert(current);
        cows.move();
        farmer.move();
        timeUsed++;
        current = getState(farmer, cows);
        if (cows.meetWith(farmer))
        {
            meet = true;
            break;
        }
    } while (states.find(current) == states.end());

    std::ofstream fout("ttwo.out");
    if (meet)
        fout << timeUsed << '\n';
    else
        fout << "0\n";
}
