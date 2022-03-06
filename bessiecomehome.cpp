/*
ID: david.y3
LANG: C++
TASK: comehome
*/
#include <fstream>
#include <queue>
#include <unordered_set>

const int INFINITY = INT32_MAX;
int p, distance['z' - 'A' + 1]['z' - 'A' + 1]{INFINITY};

int main()
{
    for (int i = 0; i < 'z' - 'A' + 1; i++)
    {
        for (int j = 0; j < 'z' - 'A' + 1; j++)
        {
            distance[i][j] = INFINITY;
        }
    }
    std::ifstream fin("comehome.in");
    fin >> p;

    std::unordered_set<int> pasturesToConsider;
    char a, b;
    int c;
    for (int i = 0; i < p; i++)
    {
        fin >> a >> b >> c;

        pasturesToConsider.insert(a - 'A');
        pasturesToConsider.insert(b - 'A');

        distance[b - 'A'][a - 'A'] = distance[a - 'A'][b - 'A'] = std::min(distance[a - 'A'][b - 'A'], c);
    }

    std::queue<std::pair<int, int>> toCalculate;
    toCalculate.push({'Z' - 'A', 0});

    bool visited['z' - 'A' + 1]{false};

    while (!toCalculate.empty())
    {
        auto x = toCalculate.front();
        int pasture = x.first, dist = x.second;

        toCalculate.pop();

        if (!visited[pasture] || dist < distance['Z' - 'A'][pasture])
        {
            visited[pasture] = true;
            distance['Z' - 'A'][pasture] = distance[pasture]['Z' - 'A'] = dist;

            for (int i : pasturesToConsider)
            {
                if (distance[pasture][i] != INFINITY)
                {
                    toCalculate.push({i, dist + distance[pasture][i]});
                }
            }
        }
    }

    int minDist = INFINITY;
    char closestPasture = '?';
    for (int x : pasturesToConsider)
    {
        if (minDist > distance['Z' - 'A'][x] && x < 'Z' - 'A')
        {
            minDist = distance['Z' - 'A'][x];
            closestPasture = x + 'A';
        }
    }

    std::ofstream fout("comehome.out");
    fout << closestPasture << ' ' << minDist << '\n';
}