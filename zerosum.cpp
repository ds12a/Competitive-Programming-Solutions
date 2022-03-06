/*
ID: david.y3
LANG: C++
TASK: zerosum
*/
#include <cmath>
#include <fstream>

const int SPACE = 0, PLUS = 1, MINUS = 2;

int main()
{
    std::ifstream fin("zerosum.in");
    int n;

    fin >> n;

    std::ofstream fout("zerosum.out");

    for (int i = 0; i < std::pow(3, n - 1); i++)
    {
        std::string sum = "";
        int sumVal = 0, currVal = 0, digit;
        bool add = true;

        for (int j = 1; j < n; j++)
        {
            int place = std::pow(3, n - j - 1);
            digit = i / place % 3;
            sum += '0' + j;
            currVal += j;
            if (digit == SPACE)
            { // maintain
                sum += ' ';
                currVal *= 10;
            }
            else
            { // dump
                if (add)
                {
                    sumVal += currVal;
                }
                else
                {
                    sumVal -= currVal;
                }
                if (digit == PLUS)
                {
                    sum += '+';
                }
                else
                {
                    sum += '-';
                }
                add = digit == PLUS;
                currVal = 0;
            }
        }

        currVal += n;
        if (add)
        {
            sumVal += currVal;
        }
        else
        {
            sumVal -= currVal;
        }

        sum += '0' + n;
        if (sumVal == 0)
        {
            fout << sum << '\n';
        }
    }
}