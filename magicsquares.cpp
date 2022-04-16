/*
ID: david.y3
LANG: C++
TASK: msquare
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   16 April 2022
// PROBLEM ID           :   msquare
// PROBLEM DESCRIPTION  :   Determine optimal sequence of operations to reach the desired state
//                          BFS
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <fstream>
#include <unordered_set>
#include <queue>

const int pows[8] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
std::unordered_set<int> found;

int getDigit(int num, int i)
{
    return (num / pows[8 - i]) % 10;
}
int A(int num)
{
    return getDigit(num, 8) * pows[7] + getDigit(num, 7) * pows[6] + getDigit(num, 6) * pows[5] +
           getDigit(num, 5) * pows[4] + getDigit(num, 4) * pows[3] + getDigit(num, 3) * pows[2] +
           getDigit(num, 2) * pows[1] + getDigit(num, 1) * pows[0];
}
int B(int num)
{
    return (getDigit(num, 4) * pows[3] + num / pows[5]) * pows[4] + ((num % pows[3]) * 10 + getDigit(num, 5));
}
int C(int num)
{
    return getDigit(num, 1) * pows[7] + getDigit(num, 7) * pows[6] + getDigit(num, 2) * pows[5] +
           getDigit(num, 4) * pows[4] + getDigit(num, 5) * pows[3] + getDigit(num, 3) * pows[2] +
           getDigit(num, 6) * pows[1] + getDigit(num, 8) * pows[0];
}

int main()
{
    std::ifstream fin("msquare.in");
    int n, goal = 0;

    for (int i = 0; i < 8; i++)
    {
        fin >> n;
        goal *= 10;
        goal += n;
    }

    std::vector<char> steps;
    std::queue<std::pair<std::vector<char>, int>> toSearch;
    toSearch.push({{}, 12345678});

    // BFS
    while (!toSearch.empty())
    {
        std::vector<char> operations = toSearch.front().first;
        int state = toSearch.front().second;

        toSearch.pop();

        if (found.find(state) != found.end())
        {
            continue;
        }

        found.insert(state);

        if (state == goal)
        {
            steps = operations;
            break;
        }

        operations.push_back('A');
        toSearch.push({operations, A(state)});
        operations.pop_back();

        operations.push_back('B');
        toSearch.push({operations, B(state)});
        operations.pop_back();
        
        operations.push_back('C');
        toSearch.push({operations, C(state)});
        operations.pop_back();
    }

    std::ofstream fout("msquare.out");
    int printed = 0;

    fout << steps.size() << '\n';

    for (char step : steps)
    {
        fout << step;

        if (printed % 60 == 59)
        {
            fout << '\n';
        }
        printed++;
    }
    fout << '\n';
}