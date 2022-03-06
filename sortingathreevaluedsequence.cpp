/*
ID: guangxue1
PROG: sort3
LANG: C++
*/

#include <fstream>
#include <iostream>

int queue[1000];
int queue2[1000];
int a, b;
int ab, ac, ba, bc, ca, cb;
int cnt;

int main()
{
    std::ifstream fin("sort3.in");
    std::ofstream fout("sort3.out");
    int n;
    fin >> n;
    for (int i = 0; i < n; ++i)
    {
        fin >> queue[i];
        switch (queue[i])
        {
        case 1:
            ++a;
            break;
        case 2:
            ++b;
        }
    }
    for (int i = 0; i < a; ++i)
        switch (queue[i])
        {
        case 2:
            ++ab;
            break;
        case 3:
            ++ac;
        }
    for (int i = a; i < a + b; ++i)
        switch (queue[i])
        {
        case 1:
            ++ba;
            break;
        case 3:
            ++bc;
        }
    for (int i = a + b; i < n; ++i)
        switch (queue[i])
        {
        case 1:
            ++ca;
            break;
        case 2:
            ++cb;
        }
    cnt += std::min(ab, ba) + std::min(ac, ca) + std::min(bc, cb);
    cnt += std::abs(ab - ba) + std::abs(ac - ca);
    fout << cnt << '\n';
    return 0;
}
