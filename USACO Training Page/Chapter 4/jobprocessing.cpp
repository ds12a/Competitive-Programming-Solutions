/*
ID: david.y3
LANG: C++17
TASK: job
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   9 June 2022
// PROBLEM ID           :   job
// PROBLEM DESCRIPTION  :   Find min time it takes for 2 groups of machines to finish n tasks
//                          Greedy!
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <vector>

int waitTimesA[31];
int waitTimesB[31];

int main()
{
    std::ifstream fin("job.in");
    int n, m1, m2, t;
    std::vector<int> timeA, timeB;

    fin >> n >> m1 >> m2;

    for (int i = 0; i < m1; i++)
    {
        fin >> t;

        timeA.push_back(t);
    }

    for (int i = 0; i < m2; i++)
    {
        fin >> t;

        timeB.push_back(t);
    }

    std::vector<int> doneA;
    int lastATime = 0, lastBTime = 0;

    for (int i = 0; i < n; i++)
    {
        int soonestIndex = 0;

        for (int j = 0; j < m1; j++)
        {
            if (timeA[j] + waitTimesA[j] < timeA[soonestIndex] + waitTimesA[soonestIndex])
            {
                soonestIndex = j;
            }
        }

        waitTimesA[soonestIndex] += timeA[soonestIndex];
        doneA.push_back(waitTimesA[soonestIndex]);
        lastATime = waitTimesA[soonestIndex];
    }

    std::reverse(doneA.rbegin(), doneA.rend());

    for (int job : doneA)
    {
        int soonestIndex = 0;
        for (int j = 0; j < m2; j++)
        {
            if (timeB[j] + waitTimesB[j] < timeB[soonestIndex] + waitTimesB[soonestIndex])
            {
                soonestIndex = j;
            }
        }

        waitTimesB[soonestIndex] += timeB[soonestIndex];
        lastBTime = std::max(waitTimesB[soonestIndex] + job, lastBTime);
    }

    std::ofstream fout("job.out");
    fout << lastATime << ' ' << lastBTime << '\n';
}