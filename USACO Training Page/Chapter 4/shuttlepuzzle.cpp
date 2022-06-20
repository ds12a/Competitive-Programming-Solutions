/*
ID: david.y3
LANG: C++17
TASK: shuttle
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   20 June 2022
// PROBLEM ID           :   shuttle
// PROBLEM DESCRIPTION  :   Determine shortest solution to game
//                          Reverse orignal position through valid moves
//                          BFS, observation
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>

int main()
{
    std::ifstream fin("shuttle.in");
    int n;

    fin >> n;

    std::string start = "";

    for (int i = 0; i < n; i++)
    {
        start.push_back('W');
    }
    start.push_back(' ');
    for (int i = 0; i < n; i++)
    {
        start.push_back('B');
    }

    std::string end = start;

    std::reverse(end.begin(), end.end());

    std::vector<int> answer;
    std::queue<std::pair<std::string, std::vector<int>>> toProcess;
    toProcess.push({start, {}});

    while (!toProcess.empty())
    {
        std::string state = toProcess.front().first;
        std::vector<int> locs = toProcess.front().second;

        toProcess.pop();

        if (end == state)
        {
            answer = locs;
            break;
        }

        int empty = state.find(' ');

        if (empty > 1 && state[empty - 1] == 'B' && state[empty - 2] == 'W')
        {
            std::swap(state[empty], state[empty - 2]);
            locs.push_back(empty - 2);

            toProcess.push({state, locs});

            locs.pop_back();
            std::swap(state[empty], state[empty - 2]);
        }
        if (empty > 0 && state[empty - 1] == 'W')
        {
            std::swap(state[empty], state[empty - 1]);
            locs.push_back(empty - 1);

            toProcess.push({state, locs});

            locs.pop_back();
            std::swap(state[empty], state[empty - 1]);
        }

        if (empty < 2 * n && state[empty + 1] == 'B')
        {
            std::swap(state[empty], state[empty + 1]);
            locs.push_back(empty + 1);

            toProcess.push({state, locs});

            locs.pop_back();
            std::swap(state[empty], state[empty + 1]);
        }
        if (empty < 2 * n - 1 && state[empty + 2] == 'B' && state[empty + 1] == 'W')
        {
            std::swap(state[empty], state[empty + 2]);
            locs.push_back(empty + 2);

            toProcess.push({state, locs});

            locs.pop_back();
            std::swap(state[empty], state[empty + 2]);
        }
    }

    std::ofstream fout("shuttle.out");
    for (unsigned int i = 1; i <= answer.size(); i++)
    {
        fout << (answer[i - 1] + 1);

        if (i % 20 > 0 && i < answer.size())
        {
            fout << ' ';
        }
        else
        {
            fout << '\n';
        }
    }
}