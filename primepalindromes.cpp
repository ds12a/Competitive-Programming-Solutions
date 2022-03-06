/*
ID: david.y3
LANG: C++
TASK: pprime
*/
#include <algorithm>
#include <cmath>
#include <fstream>
#include <set>
#include <string>

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
int getNumDigits(int num)
{
    int digits = 0;
    while (num > 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}
int makePalindrome(int firstHalf, bool hasMid = false)
{
    std::string a = std::to_string(firstHalf);
    std::string b = a;
    if (hasMid)
        b.pop_back();
    std::reverse(b.begin(), b.end());
    return std::stoi(a + b);
}
int main()
{
    std::ifstream fin("pprime.in");
    int a, b;
    std::set<int> primes, primePalindromes;
    fin >> a >> b;
    int maxDigits = getNumDigits(b), minDigits = getNumDigits(a);
    for (int numDigits = minDigits; numDigits <= maxDigits; numDigits++)
    {
        int digitsToChange = numDigits / 2 + (numDigits % 2);
        int number = std::pow(10, digitsToChange - 1);
        while (getNumDigits(number) == digitsToChange)
        {
            int palindrome = makePalindrome(number, numDigits % 2 == 1);
            if (palindrome > b)
                break;
            if (palindrome < a)
            {
                number++;
                continue;
            }
            if (isPrime(palindrome))
            {
                primePalindromes.insert(palindrome);
            }
            number++;
        }
    }
    std::ofstream fout("pprime.out");
    for (int p : primePalindromes)
        fout << p << '\n';
}