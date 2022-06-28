/*
ID: david.y3
LANG: C++17
TASK: frameup
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   28 June 2022
// PROBLEM ID           :   frameup
// PROBLEM DESCRIPTION  :   Determine possible orderings of frames that result in given layout
//                          Searching, backtracking
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <fstream>
#include <set>

char picture[31][31];

std::set<char> above['Z' + 1], below['Z' + 1];

int lastX['Z' + 1];
int firstX['Z' + 1];
int lastY['Z' + 1];
int firstY['Z' + 1];

bool isValidAt(std::string s)
{
    int index = s.size() - 1;
    if (s.empty() || below[s[index]].size() > index)
    {
        return false;
    }

    for (int i = 0; i < index; i++)
    {        
        if (above[s[index]].count(s[i]))
        {
            return false;
        }
    }
    return true;
}

void generateValidPermutations(std::string s, std::set<char> remaining, std::ofstream& fout)
{
    if (remaining.empty())
    {
        fout << s << '\n';
        return;
    }
    for (auto it = remaining.begin(); it != remaining.end(); it++)
    {
        char r = *it;

        s.push_back(r);
        remaining.erase(it);
        
        if (isValidAt(s))
        {
            generateValidPermutations(s, remaining, fout);
        }

        it = remaining.insert(r).first;
        s.pop_back();

    }
}

void computeLayering(char frame, char start)
{
    for (char f : above[frame])
    {
        if (!above[start].count(f))
        {
            above[start].insert(f);
            below[f].insert(start);
        }
        computeLayering(f, start);
    }
}

int main()
{
    std::ifstream fin("frameup.in");
    int h, w;

    fin >> h >> w;

    std::set<char> frames;

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            fin >> picture[i][j];

            if (picture[i][j] == '.')
            {
                continue;
            }
            frames.insert(picture[i][j]);

            if (firstX[picture[i][j]] == 0 || firstX[picture[i][j]] > j)
            {
                firstX[picture[i][j]] = j;
            }
            if (firstY[picture[i][j]] == 0)
            {
                firstY[picture[i][j]] = i;
            }

            lastX[picture[i][j]] = std::max(lastX[picture[i][j]], j);
            lastY[picture[i][j]] = i;
        }
    }

    for (char f : frames)
    {
        for (int i = firstX[f]; i <= lastX[f]; i++)
        {
            char c = picture[firstY[f]][i];

            if (c != f)
            {
                above[f].insert(c);
                below[c].insert(f);
            }

            c = picture[lastY[f]][i];

            if (c != f)
            {
                above[f].insert(c);
                below[c].insert(f);
            }
        }

        for (int i = firstY[f]; i <= lastY[f]; i++)
        {
            char c = picture[i][firstX[f]];

            if (c != f)
            {
                above[f].insert(c);
                below[c].insert(f);
            }

            c = picture[i][lastX[f]];

            if (c != f)
            {
                above[f].insert(c);
                below[c].insert(f);
            }
        }
    }
    for (char f : frames)
    {
        computeLayering(f, f);
    }

    std::ofstream fout("frameup.out");
    generateValidPermutations("", frames, fout);
}