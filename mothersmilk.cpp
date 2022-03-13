/*
ID: david.y3
LANG: C++
TASK: milk3
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   milk3
// PROBLEM DESCRIPTION  :   Print possible amount of milk of bucket C when A is empty
//                          DFS Algo
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int maxA, maxB, maxC;
bool tested[21][21][21]; // tested[a][b][c] = true when values (a, b, c) have been tested
std::vector<int> possibleCVals;

void pourBuckets(int inA = 0, int inB = 0, int inC = maxC)
{
    if (tested[inA][inB][inC])
        return;
    // std::cerr << inA << ' ' << inB << ' ' << inC << '\n';
    tested[inA][inB][inC] = true;
    if (inA == 0)
    {
        possibleCVals.push_back(inC);
    }
    pourBuckets(std::min(maxA, inC + inA), inB, std::max(0, inC + inA - maxA));
    pourBuckets(inA, std::min(maxB, inC + inB), std::max(0, inC + inB - maxB));
    pourBuckets(inA, std::max(0, inB + inC - maxC), std::min(maxC, inC + inB));
    pourBuckets(std::min(maxA, inB + inA), std::max(0, inB + inA - maxA), inC);
    pourBuckets(std::max(0, inA + inB - maxB), std::min(maxB, inA + inB), inC);
    pourBuckets(std::max(0, inA + inC - maxC), inB, std::min(maxC, inA + inC));
}

int main()
{
    std::ifstream fin("milk3.in");
    fin >> maxA >> maxB >> maxC;
    // std::cerr << maxA << ' ' << maxB << ' ' << maxC << '\n';
    pourBuckets();

    std::sort(possibleCVals.begin(), possibleCVals.end());

    std::ofstream fout("milk3.out");
    for (int i = 0; i < possibleCVals.size(); i++)
    {
        fout << possibleCVals[i];
        if (i < possibleCVals.size() - 1)
            fout << ' ';
    }
    fout << '\n';
}