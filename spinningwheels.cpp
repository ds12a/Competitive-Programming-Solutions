/*
ID: david.y3
LANG: C++17
TASK: spin
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   10 April 2022
// PROBLEM ID           :   spin
// PROBLEM DESCRIPTION  :   Determine shortest time until 'wedges' on wheels 'align'
//                          Simulation!?
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <iostream>
#include <vector>

int prefixDiffs[720];
int overlaps[360];

bool stateAligns()
{
    int preOverlap = 0;
    for (int deg = 0; deg < 720; deg++)
    {
        preOverlap += prefixDiffs[deg];
        if (preOverlap >= 5)
        {
            return true;
        }
        if (deg < 360)
        {
            overlaps[deg] = preOverlap;
        }
        else 
        {
            overlaps[deg - 360] += preOverlap;
            if (overlaps[deg - 360] >= 5)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::ifstream fin("spin.in");
    // {Speed, {{wedge start, wedge extent}...}}
    std::vector<std::pair<int, std::vector<std::pair<int, int>>>> currentState;
    

    for (int i = 0; i < 5; i++)
    {
        int s, w, start, deg;
        fin >> s >> w;

        currentState.push_back({s, {}});

        for (int j = 0; j < w; j++)
        {
            fin >> start >> deg;
            currentState[i].second.push_back({start, deg});

            prefixDiffs[start]++;
            prefixDiffs[start + deg + 1]--;
        }
    }

    // std::cerr << stateAligns() << '\n';
    int time = 0;

    while (!stateAligns())
    {
        for (auto &wheel : currentState)
        {
            for (auto &wedge : wheel.second)
            {
                prefixDiffs[wedge.first]--;
                prefixDiffs[wedge.first + wedge.second + 1]++;

                wedge.first = (wedge.first + wheel.first) % 360;

                prefixDiffs[wedge.first]++;
                prefixDiffs[wedge.first + wedge.second + 1]--;
                //if (time == 356) std::cerr << wedge.first << ' ' << wedge.first + wedge.second << '\n';
            }
        }
        time++;

        //std::cerr << time << '\n';
        if (time == 360)
            break;
    }
    // std::cerr << time << '\n';
    std::ofstream fout("spin.out");
    if (time != 0 && time % 360 == 0)
    {
        fout << "none\n";
    }
    else
    {
        fout << time << '\n';
    }
}