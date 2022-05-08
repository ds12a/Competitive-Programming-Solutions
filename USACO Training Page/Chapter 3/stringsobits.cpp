/*
ID: david.y3
LANG: C++
TASK: kimbits
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   7 April 2022
// PROBLEM ID           :   kimbits
// PROBLEM DESCRIPTION  :   Print ith smallest binary num with maximum of l set bits with length n
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <stack>

int choose[32][32];

int main()
{

    std::ifstream fin("kimbits.in");
    long long n, l, i;

    fin >> n >> l >> i;

    for (int j = 0; j <= n; j++)
    {
        choose[j][0] = 1;
    }

    for (int j = 1; j <= n; j++)
    {
        for (int k = 1; k <= j; k++)
        {
            // Pascal's identity
            // Calculate j choose k
            choose[j][k] = choose[j - 1][k - 1] + choose[j - 1][k];
        }
    }

    long long prevGenerated;
    long long generated = 0;
    int digits;
    int toSet = l;
    std::ofstream fout("kimbits.out");

    for (int j = n; j >= 1; j--)
    {
        prevGenerated = generated;

        for (int k = 0; k <= std::min(j - 1, toSet); k++)
        {
            generated += choose[j - 1][k];
            //std::cout << j - 1<< ' ' << k << " = " << choose[j - 1][k] << '\n';
        }
        //std::cout << generated << '\n';

        if (generated >= i)
        {
            // This is over what is wanted if this bit was 1
            generated = prevGenerated;

            fout << 0;
        }
        else {
            fout << 1;
            toSet--;
        }
    }
    fout << '\n';
}