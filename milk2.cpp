/*
ID: david.y3
LANG: C++
TASK: milk2
*/
#include <fstream>
#include <iostream>

int milkingPrefix[1000001], n, firstTime = INT32_MAX, lastTime, a, b;

int main()
{
    std::ifstream fin("milk2.in");
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> a >> b;
        milkingPrefix[a]++;
        milkingPrefix[b]--;
        lastTime = std::max(lastTime, b);
        firstTime = std::min(firstTime, a);
    }
    int currentlyMilking = 0, longestIdle = 0, longestContinueous = 0, currentIdle = 0, currentContinueous = 0;
    bool isIdle = true;
    for (int time = firstTime; time < lastTime; time++)
    {
        currentlyMilking += milkingPrefix[time];
        if (currentlyMilking > 0)
        {
            currentContinueous++;
            currentIdle = 0;
        }
        else
        {
            currentContinueous = 0;
            currentIdle++;
        }
        longestContinueous = std::max(longestContinueous, currentContinueous);
        longestIdle = std::max(longestIdle, currentIdle);
    }
    std::ofstream fout("milk2.out");
    fout << longestContinueous << ' ' << longestIdle << '\n';
}