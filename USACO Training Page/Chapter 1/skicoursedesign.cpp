/*
ID: david.y3
LANG: C++
TASK: skidesign
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   12 March 2022
// PROBLEM ID           :   skidesign
// PROBLEM DESCRIPTION  :   Mininmize changes to hills while ensuring range <= 17
//                          Complete search over lower bound
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<int> hills;

int main()
{
    std::ifstream fin("skidesign.in");
    int n, h;

    fin >> n;
    
    for (int i = 0; i < n; i++)
    {
        fin >> h;
        hills.push_back(h);
    }

    int answer = INT32_MAX;

    // Let i be lower bound to heights
    for (int i = 0; i <= 83; i++)
    {
        int cost = 0;
        for (int height : hills)
        {
            if (height < i)
                cost += (height - i) * (height - i);
            else if (height > i + 17)
                cost += (height - i - 17) * (height - i - 17);
        }
        answer = std::min(answer, cost);
    }

    std::ofstream fout("skidesign.out");
    fout << answer << '\n';
}