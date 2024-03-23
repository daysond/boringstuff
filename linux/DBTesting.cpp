#include "AVLTree.h"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

#define TEST_CASE(fn)                                                                                \
    cout << "================================================================================" << endl; \
    cout << "    Running " << #fn << "...";                                                             \
    fn();                                                                                               \
    cout << " Complete. " << endl;                                                                      \
    cout << "================================================================================" << endl;
#define TEST_CASE_PARAM(fn,param)\
    cout << "================================================================================" << endl; \
    cout << "    Running " << #fn << "...";                                                             \
    fn(param);                                                                                               \
    cout << " Complete. " << endl;                                                                      \
    cout << "================================================================================" << endl;

class DBTesting
{

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
public:
    void test_empty_tree()
    {
        AVL avl;
        assert(avl.GetRoot() == NULL);
    }

    void test_single_node()
    {
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
    }

    void test_right_insertion()
    {
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = i;
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == i);
            assert(avl.findMin(root)->empl.sin == 0);
        }
    }

    void test_left_insertion()
    {
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = iterations; i > 0; i--)
        {
            empl.sin = i;
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == 100);
            assert(avl.findMin(root)->empl.sin == i);
        }
    }

    void test_double_roatation()
    {
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
    }

    void test_random_insertion()
    {
        AVL avl;
        srand(42);
        const int iterations = 1000;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = rand();
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
        }
    }

    void test_duplicate_insertion()
    {
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = 1;
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == 1);
            assert(avl.findMin(root)->empl.sin == 1);
        }
    }

    void test_insertion()
    {
        TEST_CASE(test_empty_tree);
        TEST_CASE(test_single_node);
        TEST_CASE(test_right_insertion);
        TEST_CASE(test_left_insertion);
        TEST_CASE(test_double_roatation);
        TEST_CASE(test_random_insertion);
        TEST_CASE(test_duplicate_insertion);
    }

    // test deletion

    void test_deletion_1() {}

    void test_deletion_2() {}

    void test_deletion_3() {}

    void test_deletion_4() {}

    // 3. Test for maximum size.

    void test_max_size_map() {}

    void test_max_size_avl() {}

    // 4. Test for load (have the tree repeatedly accessed).

    void test_load_map() {}

    void test_load_avl() {}

    // 5. Test for memory leak.

    // not sure how this is done cuz usually we use valgrind and instruments to
    // check for memory leaks probably do random insertion and deletion here and
    // check for memory leaks

    void test_memory_leak_map()
    {
        TEST_CASE_PARAM(memory_leak_map_iterations, 100);
        TEST_CASE_PARAM(memory_leak_map_iterations, 1000);
        TEST_CASE_PARAM(memory_leak_map_iterations, 10000);
        TEST_CASE_PARAM(memory_leak_map_iterations, 100000);
        TEST_CASE_PARAM(memory_leak_map_iterations, 10000000);
        TEST_CASE_PARAM(memory_leak_map_bulk, 100);
        TEST_CASE_PARAM(memory_leak_map_bulk, 1000);
        TEST_CASE_PARAM(memory_leak_map_bulk, 10000);
        TEST_CASE_PARAM(memory_leak_map_bulk, 100000);
        TEST_CASE_PARAM(memory_leak_map_bulk, 10000000);
        TEST_CASE(memory_leak_map_random);
        TEST_CASE(memory_leak_map_duplicate);
        TEST_CASE(memory_leak_map_empty);
        
    }

    void test_memory_leak_avl()
    {
        TEST_CASE_PARAM(memory_leak_iterations, 100);
        TEST_CASE_PARAM(memory_leak_iterations, 1000);
        TEST_CASE_PARAM(memory_leak_iterations, 10000);
        TEST_CASE_PARAM(memory_leak_iterations, 100000);
        TEST_CASE_PARAM(memory_leak_iterations, 10000000);
        TEST_CASE_PARAM(memory_leak_avl_bulk, 100);
        TEST_CASE_PARAM(memory_leak_avl_bulk, 1000);
        TEST_CASE_PARAM(memory_leak_avl_bulk, 10000);
        TEST_CASE_PARAM(memory_leak_avl_bulk, 100000);
        TEST_CASE_PARAM(memory_leak_avl_bulk, 10000000);
        TEST_CASE(memory_leak_avl_random);
        TEST_CASE(memory_leak_avl_duplicate);
        TEST_CASE(memory_leak_avl_empty);
    }
    void memory_leak_iterations(int i){
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());

    }
    void memory_leak_avl_bulk(int i){
        AVL avl;
        EmployeeInfo empl;
        empl.age = INT_MAX;
        empl.salary = INT_MAX;
        empl.emplNumber =INT_MAX;
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());

    }
    void memory_leak_avl_random(){
        AVL avl;
        srand(42);
        const int iterations = 10000;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = rand();
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());
    }
    void memory_leak_avl_duplicate(){
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = 1;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());

    }
    void memory_leak_avl_empty(){
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        avl.insert(empl);
        avl.makeEmpty(avl.GetRoot());

    }
    void memory_leak_map_iterations(int i){
        map<int, EmployeeInfo*> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            map[i] = &empl;
        }
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            map.erase(i);
        }

    }
    void memory_leak_map_bulk(int i){
        map<int, EmployeeInfo*> map;
        EmployeeInfo empl;
        empl.age = INT_MAX;
        empl.salary = INT_MAX;
        empl.emplNumber =INT_MAX;
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            map[i] = &empl;
        }
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            map.erase(i);
        }

    }
    void memory_leak_map_random(){
        map<int, EmployeeInfo*> map;
        srand(42);
        const int iterations = 10000;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = rand();
            map[i] = &empl;
        }
        for (int i = 0; i < iterations; i++)
        {
            empl.sin = rand();
            map.erase(i);
        }

    }
    void memory_leak_map_duplicate(){
        map<int, EmployeeInfo*> map;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = 0; i < iterations; i++)
        {
            empl.sin = 1;
            map[i] = &empl;
        }
        for (int i = 0; i < iterations; i++)
        {
            empl.sin = 1;
            map.erase(i);
        }
    }
    void memory_leak_map_empty(){
        map<int, EmployeeInfo*> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        map[0] = &empl;
        map.erase(0);

    }
    // 6. Test for speed of search (worst case).
    void test_speed_search_map() {}

    void test_speed_search_avl() {}
};