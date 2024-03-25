#include "DBTesting.cpp"
#include <fstream>
#include <iostream>

using namespace std;

ofstream outfile;

int main() {

    DBTesting dbt;

    cout << "********** Testing Memory Leak for AVL Tree **********" << endl;
    dbt.test_memory_leak(TestType::AVLTREE);

    std::cout << "Press enter to continue...";
    std::cin.get();

    cout << "********** Testing Memory Leak for Map **********" << endl;
    dbt.test_memory_leak(TestType::MAP);

    std::cout << "Press enter to continue...";
    std::cin.get();

    std::cout << "All memory leak tests done.\n";
    return 0;
}