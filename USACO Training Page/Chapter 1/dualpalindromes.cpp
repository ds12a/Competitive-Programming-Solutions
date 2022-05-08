/*
ID: david.y3
LANG: C++
TASK: dualpal
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   dualpal
// PROBLEM DESCRIPTION  :   Print bases num is palindrome
//                          Brute force once again!
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int n, s;

int pow(int x, int y)
{
    int answer = 1;
    for (int i = 0; i < y; i++)
    {
        answer *= x;
    }
    return answer;
}

std::string toBaseB(std::string n, int b)
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
    std::ifstream fin("dualpal.in");
    fin >> n >> s;

    std::ofstream fout("dualpal.out");

    int numPrinted = 0;
    for (int i = s + 1; numPrinted < n; i++)
    {
        int numBasesAsPalindrome = 0;
        for (int j = 2; j <= 10; j++)
        {
            numBasesAsPalindrome += isPalindrome(toBaseB(std::to_string(i), j));
            if (numBasesAsPalindrome == 2)
            {
                fout << i << '\n';
                numPrinted++;
                break;
            }
        }
    }
}