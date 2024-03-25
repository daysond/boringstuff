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
    cout << "********** Testing Search Speed AVL **********" << endl;
    dbt.test_speed_search(TestType::AVLTREE);

    std::cout << "Press enter to continue...";
    std::cin.get();

    cout << "********** Testing Search Speed for Map **********" << endl;
    dbt.test_speed_search(TestType::MAP);

    std::cout << "Press enter to continue...";
    std::cin.get();

    std::cout << "All Search Speed tests done.\n";
    return 0;
}