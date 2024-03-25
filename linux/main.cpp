
#include <algorithm>
#include <fstream>
#include <iostream>
#include "DBTesting.cpp"

using namespace std;


int main() {
    DBTesting dbTesting;



    std::cout << "\nTesting Memory Leak for std::map...\n";
    dbTesting.test_memory_leak(DBTesting::TestType::MAP);


    std::cout << "\nTesting Memory Leak for std::map...\n";
    dbTesting.test_speed_search(DBTesting::TestType::MAP);



    return 0;
}
