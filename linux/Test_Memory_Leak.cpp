#include "DBTesting.cpp"
#include <fstream>
#include <iostream>

using namespace std;

ofstream outfile;

int main() {
    // testInsert();

    DBTesting dbt;
    // needs to be timed
    dbt.test_memory_leak_avl();

    std::cout << "Test finished.\n";
    return 0;
}