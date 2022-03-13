/*
ID: david.y3
PROG: sort3
LANG: C++
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 March 2022
// PROBLEM ID           :   sort3
// PROBLEM DESCRIPTION  :   Determine how many swaps are required to sort array
//                          Greedy?
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>

int queue[1000];
int a, b;

// First letter = 'owner', second letter = 'taker'
int ab, ac, ba, bc, ca, cb;
int cnt;

int main()
{
    std::ifstream fin("sort3.in");
    int n;

    fin >> n;

    // Count ones and twos
    for (int i = 0; i < n; ++i)
    {
        fin >> queue[i];
        switch (queue[i])
        {
        case 1:
            a++;
            break;
        case 2:
            b++;
        }
    }
    // For each place where there should be a one
    // Count how many b's and c's there are
    for (int i = 0; i < a; ++i)
    {
        switch (queue[i])
        {
        case 2:
            ab++;
            break;
        case 3:
            ac++;
        }
    }
    // Similar idea
    for (int i = a; i < a + b; ++i)
    {
        switch (queue[i])
        {
        case 1:
            ba++;
            break;
        case 3:
            bc++;
        }
    }
    // Similar idea
    for (int i = a + b; i < n; ++i)
    {
        switch (queue[i])
        {
        case 1:
            ca++;
            break;
        case 2:
            cb++;
        }
    }

    // Direct swaps, correct 2, require 1 swap each
    cnt += std::min(ab, ba) + std::min(ac, ca) + std::min(bc, cb);
    // Indirect swaps, correct 3, require 2 swaps each
    // 2 * number of nums left uncorrected by first
    cnt += 2 * std::abs(ab - ba);

    std::ofstream fout("sort3.out");
    fout << cnt << '\n';
}
