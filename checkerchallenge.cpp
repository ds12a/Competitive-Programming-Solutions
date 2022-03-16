/*
ID: david.y3
TASK: checker
LANG: C++
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   16 March 2022
// PROBLEM ID           :   checker
// PROBLEM DESCRIPTION  :   Essentially a n x n queens problem
//                          DFS, binary nums, LOTS OF OPTIMIZATION
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <stack>
#include <vector>

int main()
{
    std::ifstream fin("checker.in");
    int n;

    fin >> n;

    // {{Row #, filled positions in row}, {attack statuses, {binary set of cols occupied, firstIsCenter}}}
    std::stack<std::pair<std::pair<int, std::vector<int>>, std::pair<std::pair<int, int>, std::pair<int, bool>>>> nextRows;

    nextRows.push({{1, {}}, {{0, 0}, {0, false}}});

    int halfSolutions = 0;
    int centerSolutions = 0;
    std::vector<std::vector<int>> solutionList;
    bool recordingSolutions = true;

    // Here we go with DFS...
    while (!nextRows.empty())
    {
        auto next = nextRows.top();

        int rowNumber = next.first.first;
        std::vector<int> &filled = next.first.second;
        int leftStat = next.second.first.first;
        int rightStat = next.second.first.second;
        int bitSet = next.second.second.first;
        bool firstIsCenter = next.second.second.second;

        nextRows.pop();

        if (!recordingSolutions) filled = {};

        // Precompute attacked squares on next row without adding checkers
        int nextRowStatusLeft = leftStat >> 1;
        int nextRowStatusRight = rightStat << 1;

        // Record previous state of squares that will be changed
        // so this state can be recovered afterwards
        int statusPrevLeft = nextRowStatusLeft;
        int statusPrevRight = nextRowStatusRight;

        // Upper bound for col
        // If first row, test only half
        int upper = (rowNumber == 1) ? (n / 2 - 1 + n % 2) : (n - 1);

        for (int index = upper; index >= 0; index--)
        {
            // For bit checking
            int bitShifted = 1 << index;
            // If it is not attacked and col not occupied
            if (!(bitSet & bitShifted) && !(leftStat & bitShifted || rightStat & bitShifted))
            {
                if (rowNumber == n)
                {
                    if (!firstIsCenter)
                    {
                        halfSolutions++;
                    }
                    else
                    {
                        centerSolutions++;
                    }

                    if (recordingSolutions)
                    {
                        filled.push_back(index + 1);

                        solutionList.push_back(filled);

                        filled.pop_back();
                    }

                    if (solutionList.size() == 3)
                    {
                        recordingSolutions = false;
                    }
                    continue;
                }

                // Place checker
                // Set left
                if (index > 0)
                {
                    nextRowStatusLeft |= bitShifted >> 1;
                }
                // Set right
                if (index + 1 < n)
                {
                    nextRowStatusRight |= bitShifted << 1;
                }

                if (recordingSolutions) filled.push_back(index + 1);

                int colsTaken = bitSet | (1 << index);

                bool prevBool = firstIsCenter;

                if (rowNumber == 1 && n % 2 == 1 && index == n / 2)
                {
                    firstIsCenter = true;
                }

                nextRows.push(
                    {{rowNumber + 1, filled}, {{nextRowStatusLeft, nextRowStatusRight}, {colsTaken, firstIsCenter}}});

                // Undo changes
                if (recordingSolutions)
                    filled.pop_back();

                nextRowStatusLeft = statusPrevLeft;
                nextRowStatusRight = statusPrevRight;

                firstIsCenter = prevBool;
            }
        }
    }

    int numSols = solutionList.size();

    // Not enough to print
    // Reverse first sol for next
    if (numSols < 3)
    {
        for (int i = 0; i < 2; i++)
        {
            auto thirdToPrint = solutionList[i];

            std::reverse(thirdToPrint.begin(), thirdToPrint.end());

            solutionList.push_back(thirdToPrint);
        }
    
        std::sort(solutionList.begin(), solutionList.end());
    }

    std::ofstream fout("checker.out");
    int printed = 0;

    for (std::vector<int> &sol : solutionList)
    {
        if (printed == 3)
            break;

        for (int col = 0; col < n; col++)
        {
            fout << sol[col];

            if (col + 1 < n)
            {
                fout << ' ';
            }
            else
                fout << '\n';
        }
        printed++;
    }
    fout << 2 * halfSolutions + centerSolutions << '\n';
}