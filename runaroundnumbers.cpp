/*
ID: david.y3
LANG: C++
TASK: runround
*/
#include <fstream>
#include <iostream>
#include <string>
unsigned long long n, nextLargest = -1;

bool isRunaround(std::string number)
{
    bool digitUsed[number.size()]{false}, digitNumUsed[10]{false};
    int index = 0, digitsReached = 0, digitVal = number.at(index) - '0';
    while (!digitNumUsed[digitVal] && !digitUsed[index])
    {
        if (digitVal == 0)
            return false;
        digitsReached++;
        digitUsed[index] = true;
        digitNumUsed[digitVal] = true;
        index = (index + (number.at(index) - '0')) % number.size();
        digitVal = number.at(index) - '0';
        // std::cerr << digitVal << ' ' << index << '\n';
        // std::cerr << digitNumUsed[digitVal] << ' ' << digitUsed[index] << '\n';
    }
    return digitsReached == number.size() && index == 0;
}

int main()
{
    std::ifstream fin("runround.in");
    fin >> n;

    for (unsigned long long i = n + 1;; i++)
    {
        if (isRunaround(std::to_string(i)))
        {
            nextLargest = i;
            break;
        }
    }
    std::ofstream fout("runround.out");
    fout << nextLargest << '\n';
}