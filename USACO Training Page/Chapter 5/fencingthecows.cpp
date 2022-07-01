/*
ID: david.y3
LANG: C++17
TASK: fc
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   1 July 2022
// PROBLEM ID           :   fc
// PROBLEM DESCRIPTION  :   Convex Hull
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>

// Returns cos of angle between vectors a and b
double getCos(const std::pair<double, double> &a, const std::pair<double, double> &b)
{
    return (a.first * b.first + a.second * b.second) / (std::hypot(a.first, a.second) * std::hypot(b.first, b.second));
}

std::pair<double, double> makeVector(const std::pair<double, double> &p1, const std::pair<double, double> &p2)
{
    return {p2.first - p1.first, p2.second - p1.second};
}

std::pair<double, double> perpendicular(const std::pair<double, double> &v)
{
    return {-v.second, v.first};
}

int main()
{
    std::ifstream fin("fc.in");
    int n;

    fin >> n;

    std::vector<std::pair<double, double>> locations;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        fin >> x >> y;

        locations.push_back({x, y});
    }

    std::sort(locations.begin(), locations.end());

    double length = 0;
    std::vector<std::pair<double, double>> convexHull;

    // Upper hull
    for (std::pair<double, double> l : locations)
    {
        // If there are at least 2 points in the convex hull, check the angle
        // While the angle (or cos of angle) is that of an left-turning angle
        // remove it
        while (convexHull.size() > 1 &&
               getCos(perpendicular(makeVector(convexHull[convexHull.size() - 2], convexHull.back())),
                      makeVector(convexHull.back(), l)) > 0)
        {
            length -= std::hypot(convexHull[convexHull.size() - 2].first - convexHull.back().first,
                                 convexHull[convexHull.size() - 2].second - convexHull.back().second);
            convexHull.pop_back();
        }

        // Add to perimeter if a line can be formed
        if (!convexHull.empty())
        {
            length += std::hypot(l.first - convexHull.back().first, l.second - convexHull.back().second);
        }
        convexHull.push_back(l);
    }

    std::reverse(locations.begin(), locations.end());

    // Lower hull
    for (std::pair<double, double> l : locations)
    {
        // If there are at least 2 points in the convex hull, check the angle
        // While the angle (or cos of angle) is that of an left-turning angle
        // remove it
        while (convexHull.size() > 1 &&
               getCos(perpendicular(makeVector(convexHull[convexHull.size() - 2], convexHull.back())),
                      makeVector(convexHull.back(), l)) > 0)
        {
            length -= std::hypot(convexHull[convexHull.size() - 2].first - convexHull.back().first,
                                 convexHull[convexHull.size() - 2].second - convexHull.back().second);
            convexHull.pop_back();
        }

        // Add to perimeter if a line can be formed
        if (!convexHull.empty())
        {
            length += std::hypot(l.first - convexHull.back().first, l.second - convexHull.back().second);
        }
        convexHull.push_back(l);
    }

    std::ofstream fout("fc.out");

    fout << std::fixed << std::setprecision(2) << length << '\n';
}