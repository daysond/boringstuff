#include "AVLTree.h"
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

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
  public:
    void test_right_insertion() {
        AVL avl;
        const int iterations = 100;
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
    }

    void test_left_insertion() {
        AVL avl;
        const int iterations = 100;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;

        for (int i = iterations; i > 0; i--) {
            empl.sin = i;
            avl.insert(empl);
            // assert balance maintained
            node *root = avl.GetRoot();
            cout << avl.getBalance(root) << endl;
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == 100);
            assert(avl.findMin(root)->empl.sin == i);
        }
    }

    void test_random_insertion() {}

    void test_other_insertion() {}

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

    // not sure how this is done cuz usually we use valgrind and instruments to check for memory leaks
    // probably do random insertion and deletion here and check for memory leaks
    void test_memory_leak_map() {}

    void test_memory_leak_avl() {}

    // 6. Test for speed of search (worst case).
    void test_speed_search_map() {}

    void test_speed_search_avl() {}
};