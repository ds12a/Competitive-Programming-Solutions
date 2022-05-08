/*
ID: david.y3
TASK: calfflac
LANG: C++
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   17 March 2022
// PROBLEM ID           :   calfflac
// PROBLEM DESCRIPTION  :   Identify largest palindrome of alphabetical letters
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<char> original;
std::vector<std::pair<char, int>> onlyUpperLetters;

// Searches OUTWARDS
// Indicies in context of onlyUpperLetters
std::pair<int, std::pair<int, int>> maxPalindrome(int startIndex, int endIndex)
{
    while (startIndex >= 0 && endIndex < onlyUpperLetters.size() && onlyUpperLetters[startIndex].first == onlyUpperLetters[endIndex].first)
    {
        startIndex--;
        endIndex++;
    }

    startIndex++;
    endIndex--;

    return {endIndex - startIndex + 1, {onlyUpperLetters[startIndex].second, onlyUpperLetters[endIndex].second}};
}

char toUpperCase(char c)
{
    return (c > 'Z') ? (c - 32) : c;
}

int main()
{
    std::ifstream fin("calfflac.in");

    // Whitespace matters!
    fin.unsetf(std::ios::skipws);

    char next;

    while (true)
    {
        fin >> next;

        if (fin.eof())
            break;

        // Is letter char
        if (next >= 'A' && next <= 'Z' || next >= 'a' && next <= 'z')
        {
            char upperCase = toUpperCase(next);

            onlyUpperLetters.push_back({upperCase, original.size()});
        }

        original.push_back(next);
    }

    int numLetterChars = onlyUpperLetters.size();
    int longestLength = 0;
    std::pair<int, int> palindromeBounds = {-1, -1};

    for (int i = 0; i < numLetterChars; i++)
    {
        auto palindromeEven = maxPalindrome(i, i + 1);

        if (palindromeEven.first > longestLength)
        {
            longestLength = palindromeEven.first;
            palindromeBounds = palindromeEven.second;
        }

        auto palindromeOdd = maxPalindrome(i, i);

        if (palindromeOdd.first > longestLength)
        {
            longestLength = palindromeOdd.first;
            palindromeBounds = palindromeOdd.second;
        }
    }

    std::ofstream fout("calfflac.out");

    fout << longestLength << '\n';

    for (int i = palindromeBounds.first; i <= palindromeBounds.second; i++)
    {
        fout << original[i];
    }
    fout << '\n';
}