/*
ID: david.y3
LANG: C++
TASK: humble
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   ttwo
// PROBLEM DESCRIPTION  :   Find first n numbers made by multiplying given primes
//                          Calculated humbles one-by-one, iterate over primes, not humbles
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> humbles, primes;
// see name, helps avoid repeats, saves time
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
    // Need to subtract 1 to compensate for having 1 as humble num
    while (humbles.size() - 1 < n)
    {
        // next humble, prime used to multiply with other humble
        int next = INT32_MAX, primeMultiplied;
        for (int prime : primes)
        {
            // This is humble
            int potentialNext = prime * humbles.at(indexOfNextHumbleToMultiply[prime]);
            // Is it smallest next humble?
            if (potentialNext < next)
            {
                next = potentialNext;
                primeMultiplied = prime;
            }
        }
        // Prime used, update to muliply with next humble
        indexOfNextHumbleToMultiply[primeMultiplied]++;
        // Is this humble larger than last humble?
        if (humbles[humbles.size() - 1] < next)
            humbles.push_back(next);
        // std::cout << next << '\n';
    }

    std::ofstream fout("humble.out");
    fout << humbles[humbles.size() - 1] << '\n';
}