#include "DBTesting.h"
#include <iostream>

int main()
{
    DBTesting dbTesting;

    std::cout << "Starting search speed tests for AVL and MAP..." << std::endl;

    // Testing AVL search speed
    std::cout << "\nTesting AVL Tree Search Speed:" << std::endl;
    dbTesting.test_speed_search_map(DBTesting::TestType::AVL);

    // Testing MAP search speed
    std::cout << "\nTesting std::map Search Speed:" << std::endl;
    dbTesting.test_speed_search_map(DBTesting::TestType::MAP);

    std::cout << "Search speed tests completed." << std::endl;

    return 0;
}