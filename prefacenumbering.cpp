/*
ID: david.y3
LANG: C++
TASK: preface
*/
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>

std::unordered_map<char, int> toDec = {{'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}};

std::unordered_map<char, int> count;

std::string int_to_roman(int a)
{
    std::string ans;
    std::string M[] = {"", "M", "MM", "MMM"};
    std::string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    std::string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    std::string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    ans = M[a / 1000] + C[(a % 1000) / 100] + X[(a % 100) / 10] + I[(a % 10)];
    return ans;
}

int main()
{
    std::ifstream fin("preface.in");
    int n;
    fin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::string r = int_to_roman(i);
        for (char j : r)
        {
            count[j]++;
        }
    }
    std::ofstream fout("preface.out");
    for (char c : {'I', 'V', 'X', 'L', 'C', 'D', 'M'})
    {
        if (count[c] > 0)
            fout << c << ' ' << count[c] << '\n';
    }
}