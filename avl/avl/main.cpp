//
//  main.cpp
//  avl
//
//  Created by Dayson Dong on 2024-03-23.
//

#include "DBTesting.cpp"
#include <fstream>
#include <iostream>


const int NUM = 20;
ofstream outfile;
int treeHeight = 0;

int main() {
    // testInsert();
    
    DBTesting dbt;
    dbt.test_deletion();
    std::cout << "All tests passed.\n";
    return 0;
}
