// Test_Memory_Leak.cpp - Main program for testing memory leak
//
// Created - March, 2024
// Author - Yiyuan Dong

#include "DBTesting.cpp"
#include <fstream>
#include <iostream>

#if PLATFORM == WINDOWS
// windows memory leak detection with VS
#include <crtdbg.h>
#endif
using namespace std;

ofstream outfile;

int main() {

    #if PLATFORM == WINDOWS
    // Enable debug heap allocations & leak check at program exit
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

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
    std::cout << "In case memory leak, test AVL and map separately.\n";
    return 0;
}