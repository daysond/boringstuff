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
    cout << "********** Testing Insertion **********" << endl;
    dbt.test_insertion();

    std::cout << "Insertion tests passed.\n";

    std::cout << "Press enter to continue...";
    std::cin.get();

    cout << "\n\n********** Testing Deletion **********" << endl;
    dbt.test_deletion();
    std::cout << "Deletion tests passed.\n";
    
    std::cout << "Press enter to continue...";
    std::cin.get();

    return 0;
}