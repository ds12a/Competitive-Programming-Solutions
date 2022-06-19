/*
ID: david.y3
LANG: C++17
TASK: lgame
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   19 June 2022
// PROBLEM ID           :   lgame
// PROBLEM DESCRIPTION  :   Find words that maximize score
//                          Brute force (seriously???)
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main()
{
    std::unordered_map<char, int> value = {{'q', 7}, {'w', 6}, {'e', 1}, {'r', 2}, {'t', 2}, {'y', 5}, {'u', 4},
                                           {'i', 1}, {'o', 3}, {'p', 5}, {'a', 2}, {'s', 1}, {'d', 4}, {'f', 6},
                                           {'g', 5}, {'h', 5}, {'j', 7}, {'k', 6}, {'l', 3}, {'z', 7}, {'x', 7},
                                           {'c', 4}, {'v', 6}, {'b', 5}, {'n', 2}, {'m', 5}};
    std::ifstream fin("lgame.in");
    std::unordered_multiset<char> letters;
    char c;
    int fullScore = 0;

    fin >> c;
    while (!fin.eof())
    {
        letters.insert(c);
        fullScore += value[c];
        fin >> c;
    }
    fin.close();

    std::ifstream dict("lgame.dict");
    std::ofstream fout("lgame.out");
    std::string line;
    std::vector<std::pair<std::string, int>> valid;

    int maxScore = 0;
    std::vector<std::string> answers;

    dict >> line;

    while (line != ".")
    {
        std::unordered_multiset<char> remaining = letters;
        bool cannotMake = false;
        int score = 0;

        for (char &x : line)
        {
            auto it = remaining.find(x);
            if (it != remaining.end())
            {
                score += value[x];
                remaining.erase(it);
            }
            else
            {
                cannotMake = true;
                break;
            }
        }
        if (!cannotMake)
        {
            valid.push_back({line, score});
            maxScore = std::max(maxScore, score);
        }
        dict >> line;
    }

    for (unsigned int i = 0; i < valid.size(); i++)
    {
        if (valid[i].second == maxScore)
        {
            answers.push_back(valid[i].first);
            continue;
        }
        for (unsigned int j = i + 1; j < valid.size(); j++)
        {
            std::unordered_multiset<char> remaining = letters;
            bool bad = false;

            for (char &x : valid[i].first)
            {
                auto it = remaining.find(x);
                if (it != remaining.end())
                {
                    remaining.erase(it);
                }
                else
                {
                    bad = true;
                    break;
                }
            }
            if (bad)
            {
                continue;
            }
            for (char &x : valid[j].first)
            {
                auto it = remaining.find(x);
                if (it != remaining.end())
                {
                    remaining.erase(it);
                }
                else
                {
                    bad = true;
                    break;
                }
            }
            if (bad)
            {
                continue;
                ;
            }

            int score = valid[i].second + valid[j].second;
            if (maxScore < score)
            {
                maxScore = score;
                answers.clear();
            }
            if (score == maxScore)
            {
                answers.push_back(valid[i].first + " " + valid[j].first);
            }
        }
    }

    fout << maxScore << '\n';

    for (auto a : answers)
    {
        fout << a << '\n';
    }
}