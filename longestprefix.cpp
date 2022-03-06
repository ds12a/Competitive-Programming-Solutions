/*
ID: david.y3
LANG: C++
TASK: prefix
*/
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_set>

std::set<std::string> primitives;
std::unordered_set<int> checked;
std::string sequence;
int longestPrefix = 0;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::ifstream fin("prefix.in");
    std::string in = "";
    fin >> in;
    while (in != ".")
    {
        primitives.insert(in);
        fin >> in;
    }
    fin >> in;
    while (fin)
    {
        // std::cerr << in << '\n';
        sequence += in;
        fin >> in;
    }
    std::stack<int> indexDfs; // index
    indexDfs.push(0);
    while (!indexDfs.empty())
    {
        int index = indexDfs.top();
        checked.insert(index);
        indexDfs.pop();
        if (index == sequence.size())
        {
            longestPrefix = index;
            continue;
        }
        // std::cerr << index << '\n';
        longestPrefix = std::max(longestPrefix, index);
        char currentChar = sequence.at(index);
        std::string currentCharStr(1, currentChar);
        std::set<std::string>::iterator toTry = primitives.lower_bound(currentCharStr);
        while (toTry != primitives.end() && toTry->at(0) == currentChar)
        {
            bool validPrimitive = true;
            for (int i = 0; i < toTry->size(); i++)
            {
                if (toTry->size() > (sequence.size() - index))
                {
                    validPrimitive = false;
                    break;
                }
                if (toTry->at(i) != sequence.at(index + i))
                {
                    validPrimitive = false;
                    break;
                }
            }

            if (validPrimitive && checked.find(index + toTry->size()) == checked.end())
            {
                indexDfs.push(index + toTry->size());
                // break;
            }
            toTry++;
        }
    }
    std::ofstream fout("prefix.out");
    fout << longestPrefix << '\n';
}