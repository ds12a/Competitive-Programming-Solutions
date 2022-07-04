/*
ID: david.y3
LANG: C++17
TASK: starry
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   4 July 2022
// PROBLEM ID           :   starry
// PROBLEM DESCRIPTION  :   Label similar figures in given 2D array
//                          Implementation, flood fill
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

class Cluster
{
  public:
    Cluster(int w, int h, std::vector<std::pair<int, int>> stars) : width(w), height(h), starOffsets(stars)
    {
    }

    // Rotates Cluster by 90 degrees
    Cluster rotate90() const
    {
        auto starOffsetsRotated = starOffsets;

        // Rotates each individual star by 90 degrees
        for (auto &s : starOffsetsRotated)
        {
            s = {-s.second + width - 1, s.first};
            // assert(s.first >= 0);
        }
        std::sort(starOffsetsRotated.begin(), starOffsetsRotated.end());
        return Cluster(height, width, starOffsetsRotated);
    }

    // Flips Cluster with respect to y axis
    Cluster reflect() const
    {
        std::vector<std::pair<int, int>> starsReflected = starOffsets;

        // Reflects each individual star
        for (std::pair<int, int> &s : starsReflected)
        {
            s = {s.first, -s.second + width - 1};
            // assert(s.second >= 0);
        }
        std::sort(starsReflected.begin(), starsReflected.end());
        return Cluster(width, height, starsReflected);
    }

    // Must call after building cluster
    void sortStars()
    {
        std::sort(starOffsets.begin(), starOffsets.end());
    }

    // Tests equality
    // Orientation matters
    bool operator==(const Cluster &other) const
    {
        // std::cerr << getBoundingBox().first << ',' << getBoundingBox().second << ' ' << other.getBoundingBox().first
        //           << ',' << other.getBoundingBox().second << ' ' << getStarOffsets().size() << ' '
        //           << other.getStarOffsets().size() << '\n';
        return getBoundingBox() == other.getBoundingBox() && getStarOffsets() == other.getStarOffsets();
    }

    // Tests if other cluster is of the same type
    // True regardless of orientation
    bool equalsWithoutOrientation(const Cluster &other) const
    {
        // Checks all orientations for equality

        // std::cerr << "Original figure:\n";
        // print();
        if (*this == other)
            return true;
        Cluster rotated = rotate90();
        // std::cerr << "Rotated 90 degrees:\n";
        // rotated.print();
        if (rotated == other)
            return true;
        rotated = rotated.rotate90();
        // std::cerr << "Rotated 180 degrees:\n";
        // rotated.print();
        if (rotated == other)
            return true;
        rotated = rotated.rotate90();
        // std::cerr << "Rotated 270 degrees:\n";
        // rotated.print();
        if (rotated == other)
            return true;

        Cluster rotatedAndFlipped = reflect();
        // std::cerr << "Flipped:\n";
        // rotatedAndFlipped.print();
        if (rotatedAndFlipped == other)
            return true;
        rotatedAndFlipped = rotatedAndFlipped.rotate90();
        // std::cerr << "Flipped and rotated 90 degrees:\n";
        // rotatedAndFlipped.print();
        if (rotatedAndFlipped == other)
            return true;
        rotatedAndFlipped = rotatedAndFlipped.rotate90();
        // std::cerr << "Flipped and rotated 180 degrees:\n";
        // rotatedAndFlipped.print();
        if (rotatedAndFlipped == other)
            return true;
        rotatedAndFlipped = rotatedAndFlipped.rotate90();
        // std::cerr << "Flipped and rotated 270 degrees:\n";
        // rotatedAndFlipped.print();
        if (rotatedAndFlipped == other)
            return true;

        return false;
    }

    // Returns bounding box dimensions
    std::pair<int, int> getBoundingBox() const
    {
        return {width, height};
    }

    // Returns starOffsets
    std::vector<std::pair<int, int>> getStarOffsets() const
    {
        return starOffsets;
    }

    // Adds star to cluster
    void addStar(int x, int y)
    {
        starOffsets.push_back({x, y});
    }
    // Prints cluster info
    // void print() const
    // {
    //     std::cerr << width << ' ' << height << '\n';
    //     std::set<std::pair<int, int>> s;

    //     for (auto x : getStarOffsets())
    //     {
    //         s.insert(x);
    //         std::cerr << '{' << x.first << ", " << x.second << "} ";
    //     }
    //     std::cerr << '\n';

    //     for (int i = 0; i < getBoundingBox().second; i++)
    //     {
    //         for (int j = 0; j < getBoundingBox().first; j++)
    //         {
    //             if (s.count({i, j}))
    //             {
    //                 std::cerr << "\u001b[41m0\u001b[40m";
    //             }
    //             else
    //             {
    //                 std::cerr << "\u001b[44m0\u001b[40m";
    //             }
    //         }
    //         std::cerr << '\n';
    //     }
    //     std::cerr << '\n';
    // }

  private:
    std::vector<std::pair<int, int>> starOffsets; // With respect to where width and height are 0
    int width, height;                            // Bounding box dims
};

int h, w;
char sky[100][100];
bool processed[100][100];
bool processedAgain[100][100];

// Returns bounding box of cluster
// Classic flood fill
std::pair<std::pair<int, int>, std::pair<int, int>> getClusterBox(int x, int y)
{
    if (x >= h || y >= w || x < 0 || y < 0 || processed[x][y] || sky[x][y] == '0')
    {
        return {{INT32_MAX, INT32_MAX}, {0, 0}};
    }
    processed[x][y] = true;

    int minX = x, minY = y, maxX = x, maxY = y;

    for (int dx : {-1, 0, 1})
    {
        for (int dy : {-1, 0, 1})
        {
            auto result = getClusterBox(x + dx, y + dy);

            minX = std::min(result.first.first, minX);
            minY = std::min(result.first.second, minY);
            maxX = std::max(result.second.first, maxX);
            maxY = std::max(result.second.second, maxY);
        }
    }

    return {{minX, minY}, {maxX, maxY}};
}

// Builds cluster
// Can only be used when the bounding box of the cluster is known
// in order to calculate coordinates with respect to the upper left point
// Similar logic as getClusterBox()
void buildCluster(int x, int y, int startX, int startY, Cluster &c)
{
    if (x >= h || y >= w || x < 0 || y < 0 || processedAgain[x][y] || sky[x][y] == '0')
    {
        return;
    }

    processedAgain[x][y] = true;
    c.addStar(x - startX, y - startY);

    for (int dx : {-1, 0, 1})
    {
        for (int dy : {-1, 0, 1})
        {
            if (dx != 0 || (dx == 0 && dx != dy))
            {
                buildCluster(x + dx, y + dy, startX, startY, c);
            }
        }
    }
}

int main()
{
    std::ifstream fin("starry.in");

    fin >> w >> h;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fin >> sky[i][j];
        }
    }
    // Stores upper left points of bounding box of each cluster and Cluster objects
    std::vector<std::vector<std::pair<std::pair<int, int>, Cluster>>> sames;
    // For each point in 'sky'
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (!processed[i][j] && sky[i][j] == '1')
            {
                // std::cerr << "Cluster home: " << i << ' ' << j << '\n';
                // Get bounding box of cluster
                auto o = getClusterBox(i, j);
                // std::cerr << "Bounding box: " << '(' << o.first.first << ", " << o.first.second << "), (" <<
                // o.second.first << ", " << o.second.second << ")\n";

                Cluster c(o.second.second - o.first.second + 1, o.second.first - o.first.first + 1, {});

                // Fill the cluster
                buildCluster(i, j, o.first.first, o.first.second, c);
                c.sortStars();
                // c.print();

                bool found = false;
                // For each cluster type previously seen
                for (auto &same : sames)
                {
                    // If this one matches a previous cluster type
                    if (same.back().second.equalsWithoutOrientation(c))
                    {
                        // Add it to that type
                        same.push_back({o.first, c});
                        found = true;
                        // std::cerr << "<-----------\n";
                        // c.print();
                        // std::cerr << "EQUALS:\n";
                        // same.back().second.print();
                        // std::cerr << "----------->\n";
                        break;
                    }
                }
                // If no matches
                if (!found)
                {
                    // Create a new cluster type
                    sames.push_back({{o.first, c}});
                    // std::cerr << "NEW FIGURE:\n";
                    // c.print();
                }
            }
        }
    }

    char marker = 'a';
    // For each cluster type
    for (auto &same : sames)
    {
        // For each cluster of said type
        for (auto &cluster : same)
        {
            // For each star in said cluster
            for (std::pair<int, int> &offsets : cluster.second.getStarOffsets())
            {
                // Set star in cluster to the identifying character
                sky[cluster.first.first + offsets.first][cluster.first.second + offsets.second] = marker;
            }
        }
        // Next marker (a -> b)
        marker++;
    }
    std::ofstream fout("starry.out");
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fout << sky[i][j];
            // if (sky[i][j] == '0')
            // {
            //     std::cout << "\u001b[40m";
            // }
            // else
            // {
            //     std::cerr << "\u001b[41m";
            // }
            // std::cout << sky[i][j];
            // std::cout << "\u001b[40m";
        }
        fout << '\n';
        // std::cout << '\n';
    }

    // Cluster testA(3, 6,
    //               {{0, 0},
    //                {0, 1},
    //                {0, 2},
    //                {1, 1},
    //                {1, 2},
    //                {2, 0},
    //                {2, 1},
    //                {3, 0},
    //                {3, 1},
    //                {2, 2},
    //                {3, 2},
    //                {4, 1},
    //                {5, 0},
    //                {5, 1},
    //                {5, 2}});
    // testA.sortStars();
    // Cluster testB = testA.rotate90();
    // std::cerr << "EQUAL? " << (testA.equalsWithoutOrientation(testB)) << '\n';
    // testA.print();
    // testB.print();
}