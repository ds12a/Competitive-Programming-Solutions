/*
ID: david.y3
LANG: C++17
TASK: fence9
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   17 May 2022
// PROBLEM ID           :   fence9
// PROBLEM DESCRIPTION  :   Calculute number of lattice points in triangle given coordinates
//                          Pick's Theorem
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cmath>
#include <fstream>
#include <numeric>

int main()
{
    std::ifstream fin("fence9.in");
    int n, m, p;

    fin >> n >> m >> p;

    int borderLaticePoints = ((n != 0) ? (std::gcd(n, m)) : (m)) + ((n - p != 0) ? (std::gcd(std::abs(n - p), m)) : (m - 1)) + p;
    long long doubleArea = m * p;
    long long internalLatticePoints = (doubleArea - borderLaticePoints) / 2 + 1;

    std::ofstream fout("fence9.out");
    fout << internalLatticePoints << '\n';
}