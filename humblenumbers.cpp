/*
ID: david.y3
LANG: C++
TASK: humble
*/

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> humbles, primes;
std::unordered_map<int, int> indexOfNextHumbleToMultiply;

int main()
{
    std::ifstream fin("humble.in");
    int k, n;

    fin >> k >> n;

    int p;

    for (int i = 0; i < k; i++)
    {
        fin >> p;
        primes.push_back(p);
        indexOfNextHumbleToMultiply[p] = 0;
    }

    humbles = {1};
    while (humbles.size() - 1 < n)
    {
        int next = INT32_MAX, primeMultiplied;
        for (int prime : primes)
        {
            int potentialNext = prime * humbles.at(indexOfNextHumbleToMultiply[prime]);
            if (potentialNext < next)
            {
                next = potentialNext;
                primeMultiplied = prime;
            }
        }
        indexOfNextHumbleToMultiply[primeMultiplied]++;
        if (humbles[humbles.size() - 1] < next)
            humbles.push_back(next);
        // std::cout << next << '\n';
    }

    std::ofstream fout("humble.out");
    fout << humbles[humbles.size() - 1] << '\n';
}