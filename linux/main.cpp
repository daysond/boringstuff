
#include "AVLTree.h"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

const int NUM = 20;
ofstream outfile;
int treeHeight = 0;

int main() {
    DBTesting dbTesting;

    // Testing memory leaks for AVL Tree and std::map
    std::cout << "\nTesting Memory Leak for AVL Tree...\n";
    dbTesting.test_memory_leak(DBTesting::TestType::AVLTREE);

    std::cout << "\nTesting Memory Leak for std::map...\n";
    dbTesting.test_memory_leak(DBTesting::TestType::MAP);

    return 0;
}
