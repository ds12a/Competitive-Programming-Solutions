/*
ID: david.y3
LANG: C++
TASK: money
*/
#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("money.in");
    int v, n, c;
    long long waysToConstructValue[10001]{0};

    fin >> v >> n;

    std::vector<int> coinValues;

    for (int i = 0; i < v; i++)
    {
        fin >> c;
        coinValues.push_back(c);
    }

    waysToConstructValue[0] = 1;

    for (int val : coinValues)
    {
        for (int i = 1; i <= n; i++)
        {
            if (val <= i)
            {
                waysToConstructValue[i] += waysToConstructValue[i - val];
            }
        }
    }

    std::ofstream fout("money.out");
    fout << waysToConstructValue[n] << '\n';
}