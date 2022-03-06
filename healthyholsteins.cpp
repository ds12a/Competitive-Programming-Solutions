/*
ID: david.y3
LANG: C++
TASK: holstein
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> minVitamins, currentVitamins;
std::vector<std::vector<int>> allFeeds;
std::unordered_map<int, bool> used;
std::vector<int> feedsUsed, solution = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool tested[15];
int v, g, vitaminAmount;

void addFeed(int feedNum)
{

    auto feed = allFeeds.at(feedNum);
    for (int i = 0; i < v; i++)
    {
        currentVitamins.at(i) += feed.at(i);
    }
}
void removeFeed(int feedNum)
{
    auto feed = allFeeds.at(feedNum);
    for (int i = 0; i < v; i++)
    {
        currentVitamins.at(i) -= feed.at(i);
    }
}
bool minVitaminsMet(std::vector<int> currentVitamins)
{
    for (int i = 0; i < v; i++)
    {
        if (currentVitamins.at(i) < minVitamins.at(i))
            return false;
    }
    return true;
}
void tryFeeds(int feed)
{
    // if (tested[feed]) return;
    // std::cerr << feed << '\n';
    // tested[feed] = true;
    feedsUsed.push_back(feed);
    addFeed(feed);
    if (minVitaminsMet(currentVitamins))
    {
        if (solution.size() > feedsUsed.size())
            solution = feedsUsed;
    }
    for (int f = feed + 1; f < g; f++)
    {
        tryFeeds(f);
    }
    feedsUsed.pop_back();
    removeFeed(feed);
}
int main()
{
    std::ifstream fin("holstein.in");
    fin >> v;
    for (int i = 0; i < v; i++)
    {
        fin >> vitaminAmount;
        minVitamins.push_back(vitaminAmount);
        currentVitamins.push_back(0);
    }
    fin >> g;
    for (int i = 0; i < g; i++)
    {
        allFeeds.push_back({});
        for (int j = 0; j < v; j++)
        {
            fin >> vitaminAmount;
            allFeeds.at(i).push_back(vitaminAmount);
        }
    }
    for (int i = 0; i < g; i++)
        tryFeeds(i);
    std::sort(solution.begin(), solution.end());

    std::ofstream fout("holstein.out");
    fout << solution.size() << ' ';
    for (int i = 0; i < solution.size(); i++)
    {
        fout << solution.at(i) + 1;
        if (i < solution.size() - 1)
            fout << ' ';
    }
    fout << '\n';
}