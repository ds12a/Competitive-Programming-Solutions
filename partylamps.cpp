/*
ID: david.y3
LANG: C++
TASK: lamps
*/
#include <fstream>
#include <set>
#include <vector>

const int TERMINATOR = -1;
int n, c;
std::vector<int> on, off;

void pressButton1(std::vector<bool> &lamps)
{
    for (int i = 0; i < lamps.size(); i++)
    {
        lamps.at(i) = !lamps.at(i);
    }
}
void pressButton2(std::vector<bool> &lamps)
{
    for (int i = 1; i < lamps.size(); i += 2)
    {
        lamps.at(i) = !lamps.at(i);
    }
}
void pressButton3(std::vector<bool> &lamps)
{
    for (int i = 0; i < lamps.size(); i += 2)
    {
        lamps.at(i) = !lamps.at(i);
    }
}
void pressButton4(std::vector<bool> &lamps)
{
    for (int i = 0; i < lamps.size(); i += 3)
    {
        lamps.at(i) = !lamps.at(i);
    }
}
std::set<std::vector<bool>> getPotentialStates()
{
    std::set<std::vector<bool>> states;
    for (int i = 0; i < 16; i++)
    { // 16 = 1 << 4
        int lampsOn = __builtin_popcount(i);
        if (lampsOn > c || ((c - lampsOn) % 2 != 0 && (c - lampsOn) % 3 != 0))
            continue;
        std::vector<bool> state(n, true);
        for (int j = 0; j < 4; j++)
        {
            if ((1 << j) & i)
            {
                switch (j)
                {
                case 0:
                    pressButton1(state);
                    break;
                case 1:
                    pressButton2(state);
                    break;
                case 2:
                    pressButton3(state);
                    break;
                case 3:
                    pressButton4(state);
                    break;
                }
            }
        }
        bool bad = false;
        for (int l : on)
        {
            if (!state.at(l - 1))
                bad = true;
            ;
        }
        if (bad)
            continue;
        for (int l : off)
        {
            if (state.at(l - 1))
                bad = true;
        }
        if (bad)
            continue;
        states.insert(state);
    }
    return states;
}
int main()
{
    std::ifstream fin("lamps.in");

    fin >> n >> c;

    int lampStatus = 0;
    while (lampStatus != TERMINATOR)
    {
        fin >> lampStatus;
        if (lampStatus != TERMINATOR)
            on.push_back(lampStatus);
    }

    lampStatus = 0;
    while (lampStatus != TERMINATOR)
    {
        fin >> lampStatus;
        if (lampStatus != TERMINATOR)
            off.push_back(lampStatus);
    }

    auto possible = getPotentialStates();
    // std::sort(possible.begin(), possible.end());

    std::ofstream fout("lamps.out");
    for (auto state : possible)
    {
        for (bool b : state)
        {
            fout << b;
        }
        fout << '\n';
    }
    if (possible.size() == 0)
    {
        fout << "IMPOSSIBLE\n";
    }
}