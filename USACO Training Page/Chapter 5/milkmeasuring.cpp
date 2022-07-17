/*
ID: david.y3
LANG: C++17
TASK: milk4
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   17 July 2022
// PROBLEM ID           :   milk4
// PROBLEM DESCRIPTION  :   Determine optimal set of pails that can fill given quarts
//                          DFS with iterative deepening
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <vector>

int q, p;
std::vector<int> pailSizes;

int answer[100], currentAnswer[100];

// DFS with iterative deepening
void search(int remainingQuarts, int nextPailIndex, int maxLength, int length = 0)
{
    // If goal is achieved
    if (remainingQuarts == 0)
    {
        // Check this solution is better than the existing solution (if exists)
        for (int i = 0; i < length; i++)
        {
            if (answer[i] > 0 && answer[i] < currentAnswer[i])
            {
                return;
            }
            else if (answer[i] > currentAnswer[i])
                break;
        }

        // This solution is better, set it as the answer
        for (int i = 0; i < length; i++)
        {
            answer[i] = currentAnswer[i];
        }
        return;
    }

    // If max depth reached, too many quarts are filled, we run out of pail sizes, or all remaining pail sizes are too
    // big, stop
    if (length == maxLength || remainingQuarts < 0 || nextPailIndex >= p || pailSizes[nextPailIndex] > remainingQuarts)
    {
        return;
    }

    // Search states where this pail is not used
    search(remainingQuarts, nextPailIndex + 1, maxLength, length);

    // Set current pail size that we are adding to the next empty index in current answer
    currentAnswer[length] = pailSizes[nextPailIndex];

    // Search states where this pail is used i > 0 times
    for (int i = 1; i <= remainingQuarts / pailSizes[nextPailIndex]; i++)
    {
        search(remainingQuarts - i * pailSizes[nextPailIndex], nextPailIndex + 1, maxLength, length + 1);
    }
}

int main()
{
    std::ifstream fin("milk4.in");
    fin >> q >> p;

    for (int i = 0; i < p; i++)
    {
        int s;
        fin >> s;
        pailSizes.push_back(s);
    }

    std::sort(pailSizes.begin(), pailSizes.end());

    int length = 0;

    // For each maximum depth (or number of pails used)
    for (int i = 1; i <= p; i++)
    {
        // Search for answer with i number of pails
        search(q, 0, i);
        length = i;

        // If answer found, break
        if (answer[0] > 0)
        {
            break;
        }
    }

    std::ofstream fout("milk4.out");

    fout << length;

    for (int i = 0; i < length; i++)
    {
        fout << ' ' << answer[i];
    }

    fout << '\n';
}