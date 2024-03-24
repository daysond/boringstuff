#include "AVLTree.h"
#include "timer.h"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>

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

#define TEST_CASE_PARAM(fn, param)                                             \
    cout << "================================================================" \
            "================"                                                 \
         << endl;                                                              \
    cout << "    Running " << #fn << "...";                                    \
    fn(param);                                                                 \
    cout << " Complete. " << endl;                                             \
    cout << "================================================================" \
            "================"                                                 \
         << endl;

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


    void test_empty_tree()
    {
        AVL avl;
        assert(avl.GetRoot() == NULL);
    }

    // Test insertion

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

    // Test DELETION

    // Helper function to create a tree with n nodes
    AVL get_tree(int sin[], int n)
    {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < n; i++)
        {
            empl.sin = sin[i];
            avl.insert(empl);
        }
        return avl;
    }

    void test_remove_simple()
    {
        int sin[] = {5};
        AVL avl = get_tree(sin, 1);
        avl.remove(5);
        assert(avl.GetRoot() == NULL);
        avl.remove(1);
        assert(avl.GetRoot() == NULL);
    }

    void test_remove_leaf()
    {
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

    void test_remove_single_child()
    {
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

    void test_remove_two_children()
    {
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

    void test_remove_root()
    {
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

    void test_remove_large_tree()
    {
        int sin[] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35,
                     55, 65, 75, 85, 21, 13, 47, 38, 4, 2, 58};
        int n = sizeof(sin) / sizeof(sin[0]);
        int balance = 99;
        AVL avl = get_tree(sin, n);

        node *root = avl.GetRoot();
        for (int i = 0; i < n; i++)
        {
            avl.remove(sin[i]);
            root = avl.GetRoot();
            assert(avl.Find(root, sin[i]) == NULL);
            balance = avl.getBalance(root);
            assert(balance == 0 || balance == 1 || balance == -1);
        }
    }

    void test_remove_in_sequence()
    {
        int sin[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int n = sizeof(sin) / sizeof(sin[0]);
        int balance = 99;
        AVL avl = get_tree(sin, n);

        node *root = avl.GetRoot();
        char file[50];
        for (int i = 0; i < n; i++)
        {
            avl.remove(sin[i]);
            root = avl.GetRoot();
            assert(avl.Find(root, sin[i]) == NULL);
            balance = avl.getBalance(root);

            sprintf(file, "test_remove_in_sequence_%d.txt", i);
            avl.display(file);
            assert(balance == 0 || balance == 1 || balance == -1);
            if (root)
            {
                assert(avl.findMax(root)->empl.sin == 15);
                assert(avl.findMin(root)->empl.sin == sin[i + 1]);
            }
        }
    }

    // Test MAX SIZE
    void test_max_size_map()
    {
        map<int, EmployeeInfo> m;
        int MAX = 0;

        try
        {
            while (true)
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

    void test_max_size_avl()
    {
        int MAX = 0;
        int stepSize = 1000;
        bool flag = true;

        while (flag)
        {
            try
            {
                AVL avl;
                for (int i = 0; i < MAX; i++)
                {
                    EmployeeInfo empl;
                    empl.age = 0;
                    empl.salary = 0;
                    empl.emplNumber = 0;
                    empl.sin = rand();
                    avl.insert(empl);
                }
                avl.makeEmpty(avl.GetRoot());
                MAX += stepSize;
            }
            catch (const std::bad_alloc &e)
            {
                std::cerr << e.what() << '\n';
                cerr << "Maximum size reached!" << endl;
                flag = false;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                flag = false;
            }

            cout << "@test_max_size: Max size of AVL is: " << MAX - stepSize
                 << endl;
        }
    }

    // Test LOAD
    void test_load_map()
    {
        map<int, EmployeeInfo> m;
        int NUM = 1000000;
        int findStep = 100;
        int removeStep = 500;
        try
        {
            for (int i = 0; i < NUM; i++)
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
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        cout << "@test_load(): Map loaded with " << NUM << " elements" << endl;
    }

    void test_load_avl()
    {
        AVL avl;
        int NUM = 1000000;
        int findStep = 100;
        int removeStep = 500;
        try
        {
            for (int i = 0; i < NUM; i++)
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
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        cout << "@test_load(): AVL loaded with " << NUM << " elements" << endl;
    }

    // MEMORY LEAK
    void memory_leak_iterations(int i)
    {
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

    void memory_leak_avl_bulk(int i)
    {
        AVL avl;
        EmployeeInfo empl;
        empl.age = INT_MAX;
        empl.salary = INT_MAX;
        empl.emplNumber = INT_MAX;
        for (int i = 0; i < i; i++)
        {
            empl.sin = i;
            avl.insert(empl);
        }
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_avl_random()
    {
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

    void memory_leak_avl_duplicate()
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
        }
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_avl_empty()
    {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        avl.insert(empl);
        avl.makeEmpty(avl.GetRoot());
    }

    void memory_leak_map_iterations(int i)
    {
        map<int, EmployeeInfo *> map;
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

    void memory_leak_map_bulk(int i)
    {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = INT_MAX;
        empl.salary = INT_MAX;
        empl.emplNumber = INT_MAX;
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

    void memory_leak_map_random()
    {
        map<int, EmployeeInfo *> map;
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

    void memory_leak_map_duplicate()
    {
        map<int, EmployeeInfo *> map;
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

    void memory_leak_map_empty()
    {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        map[0] = &empl;
        map.erase(0);
    }

    // Test SPEED SEARCH
    map<int, EmployeeInfo *> populateMap(int n)
    {
        map<int, EmployeeInfo *> map;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < n; i++)
        {
            empl.sin = i;
            map[i] = &empl;
        }
        return map;
    }

    AVL populateAVL(int n)
    {
        AVL avl;
        EmployeeInfo empl;
        empl.age = 0;
        empl.salary = 0;
        empl.emplNumber = 0;
        for (int i = 0; i < n; i++)
        {
            empl.sin = i;
            avl.insert(empl);
        }
        return avl;
    }

    void test_speed_map_exist(int i, ofstream &file)
    {
        map<int, EmployeeInfo *> map = populateMap(i);
        Timer timer;
        timer.start();
        auto it = map.find(rand() * (i - 1));
        timer.stop();
        assert(it != map.end());
        file << i << "," << timer.currtime() << endl;
        cout << "Time taken to search for non existent element in map of size "
             << i << " is " << timer.currtime() << endl;
        file.close();
    }

    void test_speed_map_not_exist(int i, ofstream &file)
    {
        map<int, EmployeeInfo *> map = populateMap(i);
        Timer timer;
        timer.start();
        auto it = map.find(-1);
        timer.stop();
        assert(it == map.end());
        file << i << "," << timer.currtime() << endl;
        cout << "Time taken to search for non existent element in map of size "
             << i << " is " << timer.currtime() << endl;
        file.close();
    }

    void test_speed_avl_exist(int i, ofstream &file)
    {
        AVL avl = populateAVL(i);
        Timer timer;
        timer.start();
        node *n = avl.Find(avl.GetRoot(), rand() * (i - 1));
        timer.stop();
        assert(n != NULL);
        cout << "Time taken to search for non existent element in AVL of size "
             << i << " is " << timer.currtime() << endl;
        file << i << "," << timer.currtime() << endl;
    }

    void test_speed_avl_not_exist(int i, ofstream &file)
    {
        AVL avl = populateAVL(i);
        Timer timer;
        timer.start();
        node *n = avl.Find(avl.GetRoot(), -1);
        timer.stop();
        assert(n == NULL);
        cout << "Time taken to search for non existent element in AVL of size "
             << i << " is " << timer.currtime() << endl;
        file << i << "," << timer.currtime() << endl;
    }

public:
    enum TestType
    {
        AVL,
        MAP
    };
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

    void test_deletion()
    {
        TEST_CASE(test_remove_simple);
        TEST_CASE(test_remove_leaf);
        TEST_CASE(test_remove_single_child);
        TEST_CASE(test_remove_two_children);
        TEST_CASE(test_remove_root);
        TEST_CASE(test_remove_large_tree);
        TEST_CASE(test_remove_in_sequence);
    }

    // 3. Test for maximum size.

    void test_max_size_map()
    {
        map<int, EmployeeInfo> m;
        int MAX = 0;

        try
        {
            while (true)
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

    void test_max_size_avl()
    {
        int MAX = 0;
        int stepSize = 1000;
        bool flag = true;

        while (flag)
        {
            try
            {
                AVL avl;
                for (int i = 0; i < MAX; i++)
                {
                    EmployeeInfo empl;
                    empl.age = 0;
                    empl.salary = 0;
                    empl.emplNumber = 0;
                    empl.sin = rand();
                    avl.insert(empl);
                }
                avl.makeEmpty(avl.GetRoot());
                MAX += stepSize;
            }
            catch (const std::bad_alloc &e)
            {
                std::cerr << e.what() << '\n';
                cerr << "Maximum size reached!" << endl;
                flag = false;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                flag = false;
            }

            cout << "@test_max_size: Max size of AVL is: " << MAX - stepSize
                 << endl;
        }
    }

    void test_max_size(enum TestType type)
    {
        if (type == TestType::AVL)
        {
            TEST_CASE(test_max_size_avl);
        }
        else if (type == TestType::MAP)
        {
            TEST_CASE(test_max_size_map);
        }
    }

    // 4. Test for load (have the tree repeatedly accessed).

    void test_load_map()
    {
        map<int, EmployeeInfo> m;
        int NUM = 1000000;
        int findStep = 100;
        int removeStep = 500;
        try
        {
            for (int i = 0; i < NUM; i++)
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
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        cout << "@test_load(): Map loaded with " << NUM << " elements" << endl;
    }

    void test_load_avl()
    {
        AVL avl;
        int NUM = 1000000;
        int findStep = 100;
        int removeStep = 500;
        try
        {
            for (int i = 0; i < NUM; i++)
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
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        cout << "@test_load(): AVL loaded with " << NUM << " elements" << endl;
    }

    void test_load(enum TestType type)
    {
        if (type == TestType::AVL)
        {
            TEST_CASE(test_load_avl);
        }
        else if (type == TestType::MAP)
        {
            TEST_CASE(test_load_map);
        }
    }

    // 5. Test for memory leak.

    // not sure how this is done cuz usually we use valgrind and instruments to
    // check for memory leaks probably do random insertion and deletion here and
    // check for memory leaks

    void test_memory_leak(enum TestType type)
    {
        if (type == TestType::AVL)
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
        else if (type == TestType::MAP)
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
    }

    // 6. Test for speed of search (worst case).
    void test_speed_search_map(enum TestType type)
    {
        if (type == TestType::AVL)
        {
            ofstream file1("test_speed_avl_exist.csv");
            ofstream file2("test_speed_avl_not_exist.csv");
            for (int i = 1000; i <= 1000000; i += 1000)
            {
                TEST_CASE_MULTIPLE_PARAMS(test_speed_avl_exist, i, file1);
                TEST_CASE_MULTIPLE_PARAMS(test_speed_avl_not_exist, i, file2);
            }

        }
        else if (type == TestType::MAP)
        {
            ofstream file1("test_speed_map_exist.csv");
            ofstream file2("test_speed_map_not_exist.csv");
            for (int i = 1000; i <= 1000000; i += 1000)
            {
                TEST_CASE_MULTIPLE_PARAMS(test_speed_map_exist, i, file1);
                TEST_CASE_MULTIPLE_PARAMS(test_speed_map_not_exist, i, file2);
            }
        }
    }
};
