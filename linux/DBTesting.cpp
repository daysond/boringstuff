// DBTesting.cpp
//
// Created - March, 2024
// Author - Dennis Audi, Yiyuan Dong, Kannav Sethi

#include "AVLTree.h"
#include "timer.h"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;
#define INT_MAX 200
#define TEST_CASE(fn)                                                          \
    cout << "================================================================" \
            "================"                                                 \
         << endl;                                                              \
    cout << "    Running " << #fn << "...";                                    \
    fn();                                                                      \
    cout << " Complete. " << endl;                                             \
    cout << "================================================================" \
            "================"                                                 \
         << endl;

#define TEST_CASE_PARAM(fn, param)                                                                      \
    cout << "================================================================================" << endl; \
    cout << "    Running " << #fn << "...";                                                             \
    fn(param);                                                                                          \
    cout << " Complete. " << endl;                                                                      \
    cout << "================================================================================" << endl;

#define TEST_CASE_MULTIPLE_PARAMS(fn, param1, file)                            \
    cout << "================================================================" \
            "================"                                                 \
         << endl;                                                              \
    cout << "    Running " << #fn << "...";                                    \
    fn(param1, file);                                                          \
    cout << " Complete. " << endl;                                             \
    cout << "================================================================" \
            "================"                                                 \
         << endl;

enum TestType { AVLTREE, MAP };

class DBTesting {

    /*
    Avl Only
    1. Test for correctness of insertion.
    2. Test for correctness of deletion.

    Map & Avl
    3. Test for maximum size.
    4. Test for load (have the tree repeatedly accessed).
    5. Test for memory leak.
    6. Test for speed of search (worst case).
    */

//================================================================================================
//                                      Helper functions
//================================================================================================

// ==================== Visualization ====================

/*
These functions vide generate a png file of the visualize tree.

generateDotFile: Generates a dot file of the tree.

generateDotFileRec: Recursively writes to the dot file.

displayTree: Displays the tree in a txt file and generates a png file.

*/
    void generateDotFile(const std::string &filename, node *root) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing.\n";
            return;
        }

        file << "digraph AVLTree {\n";
        if (root) {
            file << "    " << root->empl.sin << ";\n";
            generateDotFileRec(root, file);
        }
        file << "}\n";

        file.close();

        std::string command =
            "dot -Tpng " + filename + " -o " + filename + ".png";
        system(command.c_str());

        command = "rm " + filename;
        system(command.c_str());

        std::cout << "Generated png" << std::endl;
    }

    void generateDotFileRec(node *node, std::ofstream &file) {
        if (!node)
            return;

        if (node->left) {
            file << "    " << node->empl.sin << " -> " << node->left->empl.sin
                 << ";\n";
            generateDotFileRec(node->left, file);
        }
        if (node->right) {
            file << "    " << node->empl.sin << " -> " << node->right->empl.sin
                 << ";\n";
            generateDotFileRec(node->right, file);
        }
    }

    void displayTree(char file[], const std::string &dotfile, AVL &avl) {
        avl.display(file);
        generateDotFile(dotfile, avl.GetRoot());
    }

// ================= Tree Generation ========================

    AVL get_tree(int sin[], int n) {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < n; i++) {
            empl.sin = sin[i];
            avl.insert(empl);
        }
        return avl;
    }

    AVL populateAVL(int n) {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < n; i++) {
            empl.sin = i;
            avl.insert(empl);
        }
        return avl;
    }

//================================================================================================
//                                           Test Cases
//================================================================================================

// =================== Insertion Test Cases ===================

    void test_empty_tree() {
        AVL avl;
        assert(avl.GetRoot() == NULL);
    }

    void test_single_node() {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        empl.sin = 1;
        avl.insert(empl);
        node *root = avl.GetRoot();
        assert(root->empl.sin == 1);
        assert(avl.getBalance(root) == 0);
        assert(avl.findMax(root)->empl.sin == 1);
        assert(avl.findMin(root)->empl.sin == 1);
        assert(avl.Find(root, 1)->empl.sin == 1);
        char file[] = "single_node.txt";
        displayTree(file, "single_node.dot", avl);
    }

    void test_right_insertion() {
        AVL avl;
        const int iterations = 31;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = i;
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == i);
            assert(avl.findMin(root)->empl.sin == 0);
        }
        char file[] = "right_insertion.txt";
        displayTree(file, "right_insertion.dot", avl);
    }

    void test_left_insertion() {
        AVL avl;
        const int iterations = 31;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = iterations; i > 0; i--) {
            empl.sin = i;
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == iterations);
            assert(avl.findMin(root)->empl.sin == i);
        }
        char file[] = "left_insertion.txt";
        displayTree(file, "left_insertion.dot", avl);
    }

    void test_double_roatation() {
        // Left-Right
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        empl.sin = 30;
        avl.insert(empl);
        empl.sin = 20;
        avl.insert(empl);
        empl.sin = 25;
        avl.insert(empl);
        node *root = avl.GetRoot();
        assert(root->empl.sin == 25);
        assert(avl.getBalance(root) == 0);

        char file[] = "double_rotation_left_right.txt";
        displayTree(file, "double_rotation_left_right.dot", avl);

        // Right-Left
        AVL avl2;
        empl.sin = 30;
        avl2.insert(empl);
        empl.sin = 40;
        avl2.insert(empl);
        empl.sin = 35;
        avl2.insert(empl);
        root = avl2.GetRoot();
        assert(root->empl.sin == 35);
        assert(avl2.getBalance(root) == 0);

        char file2[] = "double_rotation_right_left.txt";
        displayTree(file2, "double_rotation_right_left.dot", avl2);
    }

    void test_random_insertion() {
        AVL avl;
        srand(42);
        const int iterations = 1000;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = rand();
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
        }

        char file[] = "random_insertion.txt";
        displayTree(file, "random_insertion.dot", avl);
    }

    void test_duplicate_insertion() {
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = 1;
            avl.insert(empl);
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == 1);
            assert(avl.findMin(root)->empl.sin == 1);
        }

        char file[] = "duplicate_insertion.txt";
        displayTree(file, "duplicate_insertion.dot", avl);
    }

// =================== Deletion Test Cases ===================

    void test_remove_simple() {
        int sin[] = {5};
        AVL avl = get_tree(sin, 1);
        avl.remove(5);
        assert(avl.GetRoot() == NULL);
        avl.remove(1);
        assert(avl.GetRoot() == NULL);
    }

    void test_remove_leaf() {
        /*          20                          20
                10      30          =>      10      30
            5
        */
        int sin[] = {20, 10, 30, 5};
        AVL avl = get_tree(sin, 4);
        avl.remove(5);
        node *root = avl.GetRoot();
        assert(root->empl.sin == 20);
        assert(avl.Find(root, 5) == NULL);
        assert(avl.getBalance(root) == 0);

        char file[] = "remove_leaf.txt";
        displayTree(file, "remove_leaf.dot", avl);
    }

    void test_remove_single_child() {
        /*          20                          20
                10      30          =>      10      30
                    25     40                    25
        */
        int sin[] = {20, 10, 30, 25, 40};
        AVL avl = get_tree(sin, 5);
        avl.remove(40);
        node *root = avl.GetRoot();
        assert(root->empl.sin == 20);
        assert(avl.Find(root, 40) == NULL);
        assert(avl.getBalance(root) == -1);

        char file[] = "remove_single_child.txt";
        displayTree(file, "remove_single_child.dot", avl);
    }

    void test_remove_two_children() {
        /*          20                           20
                10      30          =>       10      35
               5  15  25   35               5  15  25   40
                    40
        */
        int sin[] = {20, 10, 30, 5, 15, 25, 35, 40};
        AVL avl = get_tree(sin, 8);
        avl.remove(30);
        node *root = avl.GetRoot();
        assert(avl.Find(root, 30) == NULL);
        assert(root->empl.sin == 20);
        assert(avl.getBalance(root) == 0);

        char file[] = "remove_two_children.txt";
        displayTree(file, "remove_two_children.dot", avl);
    }

    void test_remove_root() {
        /*          20                           25
                10      30          =>       10      30
               5  15  25   35               5  15  27   35
                    27
        */
        int sin[] = {20, 10, 30, 5, 15, 25, 35, 27};
        AVL avl = get_tree(sin, 8);
        avl.remove(20);
        node *root = avl.GetRoot();
        assert(avl.Find(root, 20) == NULL);
        assert(root->empl.sin == 25);
        assert(avl.getBalance(root) == 0);
        char file[] = "remove_root.txt";
        displayTree(file, "remove_root.dot", avl);
    }

    void test_remove_large_tree() {
        int sin[] = {50, 20, 70, 10, 30, 60, 80, 5,  15, 25, 35,
                     55, 65, 75, 85, 21, 13, 47, 38, 4,  2,  58};
        int n = sizeof(sin) / sizeof(sin[0]);
        int balance = 99;
        AVL avl = get_tree(sin, n);

        node *root = avl.GetRoot();
        for (int i = 0; i < n; i++) {
            avl.remove(sin[i]);
            root = avl.GetRoot();
            assert(avl.Find(root, sin[i]) == NULL);
            balance = avl.getBalance(root);
            assert(balance == 0 || balance == 1 || balance == -1);
        }
    }

    void test_remove_in_sequence() {
        int sin[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int n = sizeof(sin) / sizeof(sin[0]);
        int balance = 99;
        AVL avl = get_tree(sin, n);

        node *root = avl.GetRoot();
        char file[50];
        for (int i = 0; i < n; i++) {
            avl.remove(sin[i]);
            root = avl.GetRoot();
            assert(avl.Find(root, sin[i]) == NULL);
            balance = avl.getBalance(root);
            assert(balance == 0 || balance == 1 || balance == -1);
            if (root) {
                assert(avl.findMax(root)->empl.sin == 15);
                assert(avl.findMin(root)->empl.sin == sin[i + 1]);
            }
        }
    }

   void test_remove_duplicate() {
        int sin[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        int n = sizeof(sin) / sizeof(sin[0]);
        int balance = 99;
        AVL avl = get_tree(sin, n);

        node *root = avl.GetRoot();
        char file[50];
        for (int i = 0; i < n; i++) {
            avl.remove(sin[i]);
            root = avl.GetRoot();
            assert(avl.Find(root, sin[i]) == NULL);
            balance = avl.getBalance(root);
            assert(balance == 0 || balance == 1 || balance == -1);
            if (root) {
                assert(avl.findMax(root)->empl.sin == 1);
                assert(avl.findMin(root)->empl.sin == 1);
            }
        }
    }


// =================== Maximum Size Test Cases ===================

    // MAX SIZE
    void test_max_size_map(long (*func)())
    {
        map<int, EmployeeInfo> m;
        int MAX = 0;

        try
        {
            long maxStorageCapacity = 4096; // 4 GB memory
            while (func() < maxStorageCapacity)
            {
                EmployeeInfo empl;
                empl.age = 0;
                empl.salary = 0;
                empl.emplNumber = 0;
                empl.sin = rand();
                m.insert(pair<int, EmployeeInfo>(empl.sin, empl));
                MAX++;
            }
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
            cerr << "Maximum size reached!" << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        m.clear(); // delete all elements
        cout << "@test_max_size: Max size of map is: " << MAX << endl;
    }


    void test_max_size_avl(long(*func)())
    {
        int stepSize = 1000;
        int offset = 0;
        long maxStorageCapacity = 4096; // 4 GB memory

        while (func() < maxStorageCapacity)
        {
            try
            {
                AVL avl;
                for (int i = 0; i < offset + stepSize; i++)
                {
                    EmployeeInfo empl;
                    empl.age = 0;
                    empl.salary = 0;
                    empl.emplNumber = 0;
                    empl.sin = rand();
                    avl.insert(empl);
                    offset = i;
                }
                avl.makeEmpty(avl.GetRoot());
                offset += stepSize;
            }
            catch (const std::bad_alloc &e)
            {
                std::cerr << e.what() << '\n';
                cerr << "Maximum size reached!" << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

        }
        cout << "@test_max_size: Max size of AVL is: " << offset << endl;
    }

// =================== Load Test Cases ===================

    void test_load_map(int numIterations)
    {
        map<int, EmployeeInfo> m;
        int findStep = 10;
        int removeStep = 50;
        try
        {     
            for (int i = 0; i < numIterations; i++)
            {
                EmployeeInfo empl;
                empl.age = 0;
                empl.salary = 0;
                empl.emplNumber = 0;
                empl.sin = i;
                m.insert(pair<int, EmployeeInfo>(empl.sin, empl));

                // D: Find a random element in the map after every findStep
                // insertions
                if (i % findStep == 0)
                    m.find(rand() % i + 1);

                // D: Remove a random element in the map after every removeStep
                // insertions
                if (i % removeStep == 0)
                    m.erase(rand() % i + 1);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }

        // cout << "@test_load(): Map loaded with " << numIterations << " elements" << endl;
    }

    void test_load_avl(int numIterations)
    {
        AVL avl;
        int findStep = 10;
        int removeStep = 50;
        try
        {
            for (int i = 0; i < numIterations; i++)
            {
                EmployeeInfo empl;
                empl.age = 0;
                empl.salary = 0;
                empl.emplNumber = 0;
                empl.sin = i;
                avl.insert(empl);

                // D: Find a random element in the tree after every findStep
                // insertions
                if (i % findStep == 0)
                    avl.Find(avl.GetRoot(), rand() % i + 1);

                // D: Remove a random element in the tree after every removeStep
                // insertions
                if (i % removeStep == 0)
                    avl.remove(rand() % i + 1);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }

        // cout << "@test_load(): AVL loaded with " << numIterations << " elements" << endl;
    }

// =================== Memory Leak Test Cases ===================

    void memory_leak_iterations(int i) {
        cout << "running avl memory leak tests\n" << endl;
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int j = 0; j < i; j++) {
            empl.sin = i;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_avl_bulk(int i) {
        AVL avl;
        EmployeeInfo empl;
        empl.age = INT_MAX;
        empl.salary = INT_MAX;
        empl.emplNumber = INT_MAX;
        for (int j = 0; j < i; j++) {
            empl.sin = i;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_avl_random() {
        AVL avl;
        srand(42);
        const int iterations = 10000;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = rand();
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_avl_duplicate() {
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = 1;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_avl_empty() {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        avl.insert(empl);
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_map_iterations(int i) {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int j = 0; j < i; j++) {
            empl.sin = i;
            map[i] = &empl;
        }
        for (int j = 0; j < i; j++) {
            empl.sin = i;
            map.erase(i);
        }
    }

    void memory_leak_map_bulk(int i) {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = INT_MAX;
        empl.salary = INT_MAX;
        empl.emplNumber = INT_MAX;
        for (int j = 0; j < i; j++) {
            empl.sin = i;
            map[i] = &empl;
        }
        for (int j = 0; j < i; j++) {
            empl.sin = i;
            map.erase(i);
        }
    }

    void memory_leak_map_random() {
        map<int, EmployeeInfo *> map;
        srand(42);
        const int iterations = 10000;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = rand();
            map[i] = &empl;
        }
        for (int i = 0; i < iterations; i++) {
            empl.sin = rand();
            map.erase(i);
        }
    }

    void memory_leak_map_duplicate() {
        map<int, EmployeeInfo *> map;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++) {
            empl.sin = 1;
            map[i] = &empl;
        }
        for (int i = 0; i < iterations; i++) {
            empl.sin = 1;
            map.erase(i);
        }
    }

    void memory_leak_map_empty() {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        map[0] = &empl;
        map.erase(0);
    }

// =================== Speed Test Cases ===================

    map<int, EmployeeInfo *> populateMap(int n) {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < n; i++) {
            empl.sin = i;
            map[i] = &empl;
        }
        return map;
    }

    void test_speed_map_exist(int i, ofstream &file) {
        map<int, EmployeeInfo *> map = populateMap(i);
        Timer timer;
        timer.start();
        auto it = map.find(rand() * (i - 1));
        timer.stop();
        file << i << "," << timer.currtime() << endl;
        cout << "Time taken to search for non existent element in map of size "
             << i << " is " << timer.currtime() << endl;
    }

    void test_speed_map_not_exist(int i, ofstream &file) {
        map<int, EmployeeInfo *> map = populateMap(i);
        Timer timer;
        timer.start();
        auto it = map.find(-1);
        timer.stop();
        file << i << "," << timer.currtime() << endl;
        cout << "Time taken to search for non existent element in map of size "
             << i << " is " << timer.currtime() << endl;
    }

    void test_speed_avl_exist(int i, ofstream &file) {
        AVL avl = populateAVL(i);
        Timer timer;
        timer.start();
        node *n = avl.Find(avl.GetRoot(), rand() * (i - 1));
        timer.stop();
        cout << "Time taken to search for non existent element in AVL of size "
             << i << " is " << timer.currtime() << endl;
        file << i << "," << timer.currtime() << endl;
    }

    void test_speed_avl_not_exist(int i, ofstream &file) {
        AVL avl = populateAVL(i);
        Timer timer;
        timer.start();
        node *n = avl.Find(avl.GetRoot(), -1);
        timer.stop();
        cout << "Time taken to search for non existent element in AVL of size "
             << i << " is " << timer.currtime() << endl;
        file << i << "," << timer.currtime() << endl;
    }

public:

//================================================================================================
//                                           Tests
//================================================================================================

    // 1. Test for correctness of insertion.
    void test_insertion() {
        TEST_CASE(test_empty_tree);
        TEST_CASE(test_single_node);
        TEST_CASE(test_right_insertion);
        TEST_CASE(test_left_insertion);
        TEST_CASE(test_double_roatation);
        TEST_CASE(test_random_insertion);
        TEST_CASE(test_duplicate_insertion);
    }

    // 2. Test for correctness of deletion.
    void test_deletion() {
        TEST_CASE(test_remove_simple);
        TEST_CASE(test_remove_leaf);
        TEST_CASE(test_remove_single_child);
        TEST_CASE(test_remove_two_children);
        TEST_CASE(test_remove_root);
        TEST_CASE(test_remove_duplicate);

        // TEST CASES THAT CAUSE SEGMENTATION FAULT
        // TEST_CASE(test_remove_large_tree);
        // TEST_CASE(test_remove_in_sequence);
        // TEST_CASE(test_remove_in_reverse_sequence);
    }

    // 3. Test for maximum size.
    void test_max_size(TestType type, long(*func)())
    {
        if (type == TestType::AVLTREE)
        {
            test_max_size_avl(func);
        }
        else if (type == TestType::MAP)
        {
            test_max_size_map(func);
        }
    }

    // 4. Test for load (have the tree repeatedly accessed).
    void test_load(TestType type, int numIterations)
    {
        if (type == TestType::AVLTREE)
        {
            test_load_avl(numIterations);
        }
        else if (type == TestType::MAP)
        {
            test_load_map(numIterations);
        }
    }


    // 5. Test for memory leak.
    void test_memory_leak(TestType type) {
        if (type == TestType::AVLTREE) {
            TEST_CASE_PARAM(memory_leak_iterations, 1000);
            TEST_CASE_PARAM(memory_leak_avl_bulk, 1000);
            TEST_CASE(memory_leak_avl_random);
            TEST_CASE(memory_leak_avl_duplicate);
            TEST_CASE(memory_leak_avl_empty);
        } else if (type == TestType::MAP) {
            TEST_CASE_PARAM(memory_leak_map_iterations, 1000);
            TEST_CASE_PARAM(memory_leak_map_bulk, 1000);
            TEST_CASE(memory_leak_map_random);
            TEST_CASE(memory_leak_map_duplicate);
            TEST_CASE(memory_leak_map_empty);
        }
    }

    // 6. Test for speed of search (worst case).
    void test_speed_search(TestType type) {
        if (type == TestType::AVLTREE) {
            ofstream file1("test_speed_avl_exist.csv");
            ofstream file2("test_speed_avl_not_exist.csv");
            file1 << "Iterations"
                  << ","
                  << "Time Taken" << endl;
            file2 << "Iterations"
                  << ","
                  << "Time Taken" << endl;
            for (int i = 1000; i <= 1000000; i += 10000) {
                TEST_CASE_MULTIPLE_PARAMS(test_speed_avl_exist, i, file1);
                TEST_CASE_MULTIPLE_PARAMS(test_speed_avl_not_exist, i, file2);
            }
        } else if (type == TestType::MAP) {
            ofstream file1("test_speed_map_exist.csv");
            ofstream file2("test_speed_map_not_exist.csv");
            file1 << "Iterations"
                  << ","
                  << "Time Taken" << endl;
            file2 << "Iterations"
                  << ","
                  << "Time Taken" << endl;
            for (int i = 1000; i <= 1000000; i += 10000) {
                TEST_CASE_MULTIPLE_PARAMS(test_speed_map_exist, i, file1);
                TEST_CASE_MULTIPLE_PARAMS(test_speed_map_not_exist, i, file2);
            }
        }
    }

};
