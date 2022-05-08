/*
ID: david.y3
LANG: C++
TASK: stamps
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   20 March 2022
// PROBLEM ID           :   stamps
// PROBLEM DESCRIPTION  :   Find largest m where all ints 1...m can be 
//                          represented as sum of <= k of given ints
//                          Classic DP Problem
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <vector>
#include <algorithm>

// Minimum stamps required to reach index cents
int minStamps[2000001];

int main()
{
    std::ifstream fin("stamps.in");
    int n, k, c;
    std::vector<int> values;

    fin >> k >> n;

    for (int i = 0; i < n; i++)
    {
        fin >> c;

        minStamps[c] = 1;
        values.push_back(c);
    }

    std::sort(values.begin(), values.end());

    int valuesCanForm = 0;
    int maxValue = k * 10000;
    
    for (int i = 1; i <= maxValue; i++)
    {
        for (int val : values)
        {
            if (i - val < 0) 
            {
                break;
            }
            if (minStamps[i - val] + 1 <= k)
            {
                if (minStamps[i] == 0)
                {
                    minStamps[i] = minStamps[i - val] + 1;
                }
                else
                {
                    minStamps[i] = std::min(minStamps[i], minStamps[i - val] + 1);
                }
            }
        }

        if (!minStamps[i]) break;
        valuesCanForm = i;
    }

    std::ofstream fout("stamps.out");
    fout << valuesCanForm << '\n';
}