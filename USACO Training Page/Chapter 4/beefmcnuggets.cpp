/*
ID: david.y3
LANG: C++17
TASK: nuggets
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   25 May 2022
// PROBLEM ID           :   nuggets
// PROBLEM DESCRIPTION  :   Find maximum number that cannot be represented as a weighted sum of <=10 integers (1...256)
//                          DP, Chicken McNugget Theorem, NT
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <numeric>
#include <vector>

bool reachable[65025];

int main()
{
    std::ifstream fin("nuggets.in");
    std::vector<int> packages;
    int n, x, g = -1;

    fin >> n;

    for (int i = 0; i < n; i++)
    {
        fin >> x;

        packages.push_back(x);

        if (g == -1)
            g = x;
        else
            g = std::gcd(g, x);
    }

    std::ofstream fout("nuggets.out");

    if (g != 1)
    {
        fout << "0\n";
        return 0;
    }

    int maxCannotReach = 0;
    reachable[0] = true;

    for (int i = 0; i <= 65024; i++)
    {
        if (reachable[i])
        {
            for (int p : packages)
            {
                reachable[i + p] = true;
            }
        }
        else
        {
            maxCannotReach = i;
        }
    }

    fout << maxCannotReach << '\n';
}
