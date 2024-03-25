// #include "AVLTree.h" // Your AVL tree implementation

#include "DBTesting.cpp"
#include <fstream>
#include <iostream>

using namespace std;

ofstream outfile;

int main() {
    // testInsert();

    DBTesting dbt;
    // needs to be timed
    cout << "********** Testing Load **********" << endl;
    dbt.test_insertion();

    std::cout << "All tests passed.\n";
    return 0;
}