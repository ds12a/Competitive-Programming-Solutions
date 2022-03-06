/*
ID: david.y3
LANG: C++
TASK: contact
*/

#include <fstream>
#include <map>

std::map<std::string, int> repeats; // pattern, count

int main()
{
    std::ifstream fin("contact.in");

    int a, b, n;
    std::string pastChars = "";
    char toAppend;

    fin >> a >> b >> n;

    while (fin >> toAppend)
    {
        if (toAppend == '\n')
            continue;

        pastChars += toAppend;

        if (pastChars.size() > b)
            pastChars.erase(0, 1);
        else if (pastChars.size() < a)
            continue;

        std::string past = pastChars;
        for (int i = b; i >= a; i--)
        {

            repeats[past]++;
            pastChars.erase(pastChars.front());
        }
    }

    std::ofstream fout("contact.out");
    fout << repeats.rbegin()->first << '\n';
}