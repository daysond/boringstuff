// Test_Max_Size.cpp - Main program for testing max size of AVL tree and map
//
// Created - March, 2024
// Author - Dennis Audi

#include <iostream>
#include "DBTesting.cpp"
#include <fstream>
#include <iostream>

using namespace std;

#define POSIX 1
#define WINDOWS 2
#define PLATFORM POSIX

#if PLATFORM == POSIX
#include <sys/resource.h>
#include <unistd.h>

long memUsed() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss / 1024;  // Memory used in MB
}

#elif PLATFORM == WINDOWS
#include <windows.h>
#include <psapi.h>

size_t memUsed() {
    PROCESS_MEMORY_COUNTERS pmc;
    size_t currentUsage = 0;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        currentUsage = pmc.WorkingSetSize / (1024 * 1024);  // Convert from bytes to MB
    }
    return currentUsage;
}
#endif


ofstream outfile;

int main(){
    DBTesting dbt;

    dbt.test_max_size(TestType::AVLTREE, &memUsed);
   

    return 0;
}
