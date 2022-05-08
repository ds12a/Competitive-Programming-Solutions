/*
ID: david.y3
LANG: C++
TASK: contact
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   19 March 2022
// PROBLEM ID           :   contact
// PROBLEM DESCRIPTION  :   Determine patterns in a string, print most frequent
//                          along with frequency
//                          Sliding-window, binary nums
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

void setNthBit(int &bits, bool isOne, int n)
{
    int bit = 1 << n;

    if (bits & bit)
    {
        if (isOne)
            return;
        else
            bits ^= bit;
    }
    else
    {
        if (isOne)
            bits |= bit;
        else
            return;
    }
}

int reverseBinaryDigits(int binary)
{
    int rev = 0;

    while (binary > 0)
    {
        rev <<= 1;
        rev += binary & 1;
        binary >>= 1;
    }
    return rev;
}
int main()
{
    std::ifstream fin("contact.in");

    int a, b, n;
    std::string emission = "", line;

    fin >> a >> b >> n;

    while (std::getline(fin, line))
    {
        emission += line;
    }

    int bitWindow = 0;
    int leadingZeros = 0;

    for (int i = 0; i < a; i++)
    {
        setNthBit(bitWindow, emission[i] - '0', i);
        if (emission[i] - '0' == 0)
        {
            leadingZeros++;
        }
        else
            leadingZeros = 0;
    }

    // Pattern, leadingZeros, digits, frequency
    std::map<std::pair<std::pair<int, int>, int>, int> patternCount;

    for (int start = 0; start < emission.size(); start++)
    {
        int prevLeadingZeros = leadingZeros;

        if (bitWindow == 0)
        {
            leadingZeros--;
        }

        for (int length = a; length <= b; length++)
        {
            if (start + length - 1 >= emission.size())
            {
                break;
            }

            int digit = emission[start + length - 1] - '0';

            setNthBit(bitWindow, digit, length - 1);

            if (digit == 0)
            {
                leadingZeros++;
            }
            else
            {
                leadingZeros = 0;
            }

            patternCount[{{bitWindow, leadingZeros}, length}]++;
        }

        // Look at bit that will enter window
        // Determine how it will change the number of leading zeros
        if (start + a - 1 < emission.size() && emission[start + a - 1] == '0')
        {
            prevLeadingZeros++;
        }
        else if (start + a - 1 < emission.size() && emission[start + a - 1] == '1')
        {
            prevLeadingZeros = 0;
        }

        // Leave only last a bits
        int mask = (1 << a) - 1;

        bitWindow &= mask;

        // If a leading zero is about to exit window
        if (bitWindow == 0)
        {
            prevLeadingZeros--;
        }

        leadingZeros = prevLeadingZeros;
        
        bitWindow >>= 1;
    }

    // Frequency, {{pattern, leadingZeros}, length}
    // Sorted in decreasing order
    std::map<int, std::vector<std::pair<std::pair<int, int>, int>>, std::greater<int>> getPatternsByFreq;

    // move frequencies and patterns into map with frequencies as key
    for (auto pattern : patternCount)
    {
        getPatternsByFreq[pattern.second].push_back(pattern.first);
    }

    // Sort by length and binary
    auto cmp = [](std::pair<std::pair<int, int>, int> a, std::pair<std::pair<int, int>, int> b) {
        if (a.second == b.second)
        {
            return (reverseBinaryDigits(a.first.first) << a.first.second) < (reverseBinaryDigits(b.first.first) << b.first.second);
        }
        if (a.second < b.second) return true;
        
        return false;
    };

    for (auto &pByF : getPatternsByFreq)
    {
        std::sort(pByF.second.begin(), pByF.second.end(), cmp);
    }

    std::ofstream fout("contact.out");

    int freqPrinted = 0;

    for (auto pats : getPatternsByFreq)
    {
        if (freqPrinted == n)
            break;

        // Print frequency
        fout << pats.first << '\n';

        int patsPrinted = 0;

        for (std::pair<std::pair<int, int>, int> p : pats.second)
        {
            // Print binary of p.first.first
            if (p.first.first == 0) fout << 0;
            while (p.first.first > 0)
            {
                if (p.first.first & 1)
                {
                    fout << '1';
                }
                else
                    fout << '0';

                p.first.first >>= 1;
            }

            // Print leadingZeros (now they are trailing zeros)
            for (int i = 0; i < p.first.second; i++)
            {
                fout << '0';
            }
            
            patsPrinted++;

            // Dumb required formatting
            if (patsPrinted % 6 == 0 || patsPrinted == pats.second.size())
                fout << '\n';
            else
                fout << ' ';
        }

        freqPrinted++;
    }
}