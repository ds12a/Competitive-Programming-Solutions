/*
ID: david.y3
LANG: C++
TASK: transform
*/
#include <fstream>
#include <iostream>

int n;
std::string original, changed;
std::string reflect(std::string pattern)
{
    std::string transformed = pattern;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            transformed[i * n + j] = pattern[i * n + n - j - 1];
            transformed[i * n + n - j - 1] = pattern[i * n + j];
        }
    }
    return transformed;
}
std::string rotate90(std::string pattern)
{
    std::string transformed = pattern;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            transformed[i * n + j] = pattern[j * n + i]; // Issue
            transformed[j * n + i] = pattern[i * n + j];
        }
    }
    return reflect(transformed);
}
std::string rotate180(std::string pattern)
{
    return rotate90(rotate90(pattern));
}
std::string rotate270(std::string pattern)
{
    return rotate90(rotate180(pattern));
}

int main()
{
    std::ifstream fin("transform.in");
    std::string line;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> line;
        original += line;
    }
    for (int i = 0; i < n; i++)
    {
        fin >> line;
        changed += line;
    }
    std::ofstream fout("transform.out");
    if (changed == rotate90(original))
        fout << "1\n";
    else if (changed == rotate180(original))
        fout << "2\n";
    else if (changed == rotate270(original))
        fout << "3\n";
    else if (changed == reflect(original))
        fout << "4\n";
    else if ((changed == reflect(rotate90(original)) ||
              (changed == reflect(rotate180(original)) || (changed == reflect(rotate270(original))))))
        fout << "5\n";
    else if (changed == original)
        fout << "6\n";
    else
        fout << "7\n";
}