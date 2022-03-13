/*
ID: david.y3
LANG: C++
TASK: sprime
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   sprime
// PROBLEM DESCRIPTION  :   Prints all "superprime ribs" of length n
//                          Complete Search
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>

bool isPrime(int num)
{
    if (num == 1)
        return false;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0 && i != num)
            return false;
    }
    return true;
}

// Complete search
void printSuperprimeRibs(int n, std::ofstream &fout, int accumulated = 0)
{
    if (!isPrime(accumulated))
        return;
    if (n == 0)
    {
        fout << accumulated << '\n';
        return;
    }
    for (int i = 1; i <= 9; i++)
    {
        printSuperprimeRibs(n - 1, fout, accumulated * 10 + i);
    }
}

int main()
{
    std::ifstream fin("sprime.in");
    std::ofstream fout("sprime.out");
    int n;
    fin >> n;

    printSuperprimeRibs(n, fout);
}