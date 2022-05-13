/*
ID: david.y3
LANG: C++
TASK: game1
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   13 May 2022
// PROBLEM ID           :   game1
// PROBLEM DESCRIPTION  :   Determine optimal scores in a game
//                          DP and Prefix sums
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <vector>

int maxScore1[200][200];
int prefix[100];

int main()
{
    std::ifstream fin("game1.in");
    int n, x;

    fin >> n;

    std::vector<int> board;

    for (int i = 0; i < n; i++)
    {
        fin >> x;
        board.push_back(x);
        maxScore1[i][i] = x;
    }

    prefix[0] = board[0];
    for (int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + board[i];
    }

    for (int len = 1; len <= n; len++)
    {
        for (int start = 0; start < n; start++)
        {
            int end = start + len - 1;
            if (end >= n)
                break;
            // SumOfRange - player2Score
            maxScore1[start][end] = std::max(
                prefix[end] - ((start > 0) ? prefix[start - 1] : 0) - maxScore1[start + 1][end],
                prefix[end] - ((start > 0) ? prefix[start - 1] : 0) - maxScore1[start][end - 1]);
        }
    }

    std::ofstream fout("game1.out");
    fout << maxScore1[0][n - 1] << ' ' << (prefix[n - 1] - maxScore1[0][n - 1]) << '\n';
}