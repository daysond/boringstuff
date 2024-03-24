#include "AVLTree.h"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

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
    }

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
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == 100);
            assert(avl.findMin(root)->empl.sin == i);
        }
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
            // assert balance maintained
            node *root = avl.GetRoot();
            assert(avl.getBalance(root) == 0 || avl.getBalance(root) == 1 ||
                   avl.getBalance(root) == -1);
            assert(avl.findMax(root)->empl.sin == 1);
            assert(avl.findMin(root)->empl.sin == 1);
        }
    }

  public:
    void test_insertion() {
        TEST_CASE(test_empty_tree);
        TEST_CASE(test_single_node);
        TEST_CASE(test_right_insertion);
        TEST_CASE(test_left_insertion);
        TEST_CASE(test_double_roatation);
        TEST_CASE(test_random_insertion);
        TEST_CASE(test_duplicate_insertion);
    }

    // test deletion
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
        int sin[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,12, 13, 14, 15};
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
            // if(root) {
            //     assert(avl.findMax(root)->empl.sin == 15 );
            //     assert(avl.findMin(root)->empl.sin == sin[i + 1]);
            // }
        }
    }

    void test_deletion() {
        TEST_CASE(test_remove_simple);
        TEST_CASE(test_remove_leaf);
        TEST_CASE(test_remove_single_child);
        TEST_CASE(test_remove_two_children);
        TEST_CASE(test_remove_root);
        TEST_CASE(test_remove_large_tree);
        TEST_CASE(test_remove_in_sequence);
    }


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
    void test_memory_leak_map() {}

    void test_memory_leak_avl() {}

    // 6. Test for speed of search (worst case).
    void test_speed_search_map() {}

    void test_speed_search_avl() {}
};
