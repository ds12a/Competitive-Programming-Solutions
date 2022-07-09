/*
ID: david.y3
LANG: C++17
TASK: theme
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   9 July 2022
// PROBLEM ID           :   theme
// PROBLEM DESCRIPTION  :   Find the length of the longest repeating substring
//                          Dynamic programming 2d, optimization (on memory)
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <vector>

int matchingLengthA[5000]; // Previous computed values
int matchingLengthB[5000]; // Currently computing values

int main()
{
    std::ifstream fin("theme.in");
    int n;

    fin >> n;

    std::vector<int> changes; // Stores differences between notes
    int prevNote = 0, maxLen = 0;

    for (int i = 0; i < n; i++)
    {
        int note;
        fin >> note;

        if (i > 0)
        {
            changes.push_back(note - prevNote);

            // For each previously computed difference between consecutive notes
            for (int j = 0; j < i - 1; j++)
            {
                // If the differences match, the answer is at least 1
                // otherwise it's at least 0
                matchingLengthB[j] = changes[j] == changes[i - 1];

                // If there are computed changes before the current one and
                // the changes match and the matching intervals do not overlap
                if (j > 0 && changes[j] == changes[i - 1] &&
                    i - 1 - j > std::max(matchingLengthA[j - 1] + 1, matchingLengthB[j]))
                {
                    // We have a possible solution
                    matchingLengthB[j] = std::max(matchingLengthA[j - 1] + 1, matchingLengthB[j]);
                }

                // Compute max solution
                maxLen = std::max(maxLen, matchingLengthB[j] + 1);
            }
        }

        // Shift matchingLengthB into matchingLengthA
        std::copy(matchingLengthB, matchingLengthB + n, matchingLengthA);
        prevNote = note;
    }

    std::ofstream fout("theme.out");
    fout << ((maxLen >= 5) * maxLen) << '\n';
}