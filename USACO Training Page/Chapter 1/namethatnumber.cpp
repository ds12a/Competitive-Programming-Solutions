/*
ID: david.y3
LANG: C++
TASK: namenum
*/

// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   namenum
// PROBLEM DESCRIPTION  :   Find names that match numerical id
//                          Complete Search, then find valid
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::string> allNames, workingNames;
std::vector<std::vector<std::string>> charChoices;
std::unordered_set<std::string> validNames;
std::unordered_map<int, std::vector<std::string>> touchTone = {
    {2, {"A", "B", "C"}}, {3, {"D", "E", "F"}}, {4, {"G", "H", "I"}}, {5, {"J", "K", "L"}},
    {6, {"M", "N", "O"}}, {7, {"P", "R", "S"}}, {8, {"T", "U", "V"}}, {9, {"W", "X", "Y"}},
};

void generateNames(int charNum, std::string accumulated = "")
{
    if (charNum == charChoices.size())
    {
        if (validNames.find(accumulated) != validNames.end())
        {
            workingNames.push_back(accumulated);
        }
        return;
    }
    for (std::string c : charChoices[charNum])
    {
        generateNames(charNum + 1, accumulated + c);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::ifstream fin("namenum.in");
    std::ifstream nameFile("dict.txt");
    std::string id, name;
    while (!nameFile.eof())
    {
        nameFile >> name;
        validNames.insert(name);
    }
    nameFile.close();

    fin >> id;
    for (char c : id)
    {
        charChoices.push_back(touchTone[c - '0']);
    }

    generateNames(0);

    std::ofstream fout("namenum.out");

    std::sort(workingNames.begin(), workingNames.end());

    for (std::string name : workingNames)
        fout << name << '\n';
    if (workingNames.empty())
        fout << "NONE\n";
}