/*
ID: david.y3
LANG: C++
TASK: heritage
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   15 May 2022
// PROBLEM ID           :   heritage
// PROBLEM DESCRIPTION  :   Produce post-order traversal from pre and in order traversals
//                          Recursion
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cassert>
#include <fstream>

std::string generatePostOrder(std::string inOrder, std::string preOrder)
{
    assert(inOrder.size() == preOrder.size());

    int n = inOrder.size();

    if (n == 0)
        return "";

    char root = preOrder[0];
    int index = inOrder.find(root);
    int onLeft = index, onRight = n - index - 1;

    std::string left = generatePostOrder(inOrder.substr(0, onLeft), preOrder.substr(1, onLeft));      // Left subtree
    std::string right = generatePostOrder(inOrder.substr(n - onRight), preOrder.substr(n - onRight)); // Right Subtree
    return left + right + root;
}

int main()
{
    std::ifstream fin("heritage.in");
    std::string inOrder, preOrder;

    fin >> inOrder >> preOrder;

    std::ofstream fout("heritage.out");
    fout << generatePostOrder(inOrder, preOrder) << '\n';
}