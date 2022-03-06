/*
ID: david.y3
LANG: C++
TASK: palsquare
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int b;

int pow(int x, int y)
{
    int answer = 1;
    for (int i = 0; i < y; i++)
    {
        answer *= x;
    }
    return answer;
}

std::string toBaseB(std::string n)
{
    int num = std::stoi(n);
    int exponent = 1;
    while (num / pow(b, exponent) > 0)
    {
        exponent++;
    }
    std::string baseB = "";
    for (int e = exponent - 1; e >= 0; e--)
    {
        if ((num / pow(b, e)) / 10 > 0)
        {
            baseB += (char)('A' - 10 + num / pow(b, e));
        }
        else
            baseB += (char)(num / pow(b, e) + '0');
        num %= pow(b, e);
    }
    return baseB;
}

bool isPalindrome(std::string num)
{
    std::string rev = num;
    std::reverse(rev.begin(), rev.end());
    return num == rev;
}

int main()
{
    std::ifstream fin("palsquare.in");
    fin >> b;
    std::ofstream fout("palsquare.out");
    for (int i = 1; i <= 300; i++)
    {
        std::string baseB = toBaseB(std::to_string(i * i));
        if (isPalindrome(baseB))
        {
            fout << toBaseB(std::to_string(i)) << ' ' << baseB << '\n';
            std::cerr << i << ' ' << toBaseB(std::to_string(i)) << ' ' << baseB << '\n';
        }
    }
}