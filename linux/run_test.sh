#!/bin/bash

# Build the project
make clean all

# Check if build succeeded
if [ $? -ne 0 ]; then
    echo "Build failed, aborting test runs."
    exit 1
fi

# Define test programs
declare -a tests=("Test_Memory_Leak"
                  "Test_Unit_Test"
                  "Test_Search_Speed"
                  "Test_Load"
                  "Test_Max_Size")

# Run each test
for test in "${tests[@]}"; do
    echo "Running $test..."
    if [[ $test == "Test_Memory_Leak" ]]; then
        # Run Test_Memory_Leak with valgrind
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$test
    else
        # Run other tests normally
        ./$test
    fi
    echo "$test completed."
    echo "-----------------------------"
done

echo "All tests have been run."
