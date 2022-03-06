/*
ID: david.y3
LANG: C++
TASK: crypt1
*/
#include <fstream>
#include <iostream>
#include <unordered_set>

std::unordered_set<int> allowedDigits;
int n, x;

bool hasOnlyAllowedDigits(int num)
{
    while (num > 0)
    {
        if (allowedDigits.find(num % 10) == allowedDigits.end())
        {
            return false;
        }
        num /= 10;
    }
    return true;
}

bool onlyAllowed(int top, int bottom)
{ // abc, xy
    return hasOnlyAllowedDigits(top * bottom) && hasOnlyAllowedDigits(top * (bottom / 10)) &&
           hasOnlyAllowedDigits(top * (bottom % 10));
}

int main()
{
    std::ifstream fin("crypt1.in");
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> x;
        allowedDigits.insert(x);
    }
    long long solutions = 0;
    for (int a : allowedDigits)
    {
        for (int b : allowedDigits)
        {
            for (int c : allowedDigits)
            { // number abc
                for (int x : allowedDigits)
                {
                    for (int y : allowedDigits)
                    { // number xy
                        int top = 100 * a + 10 * b + c;
                        int bottom = 10 * x + y;
                        // std::cerr << top << ' ' << bottom << '\n';
                        if ((top * (bottom / 10)) / 100 > 10 || (top * (bottom % 10)) / 100 > 10)
                        {
                            // Too big!
                            continue;
                        }
                        if ((top * (bottom / 10)) / 100 < 1 || (top * (bottom % 10)) / 100 < 1)
                        {
                            // Too small!

                            continue;
                        }

                        solutions += onlyAllowed(top, bottom);
                    }
                }
            }
        }
    }
    std::ofstream fout("crypt1.out");
    fout << solutions << '\n';
}