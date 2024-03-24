// #include "AVLTree.h" // Your AVL tree implementation

#include "DBTesting.cpp"
#include <fstream>
#include <iostream>

using namespace std;

void testInsert() {
    AVL avl;

    EmployeeInfo empl;
    empl.age = 0;
    empl.salary = 0;
    empl.emplNumber = 0;
    empl.sin = 1;
    avl.insert(empl);

    // Assuming you have a method to get the balance factor of the root
    int b = avl.getBalance(avl.GetRoot());
    assert(b == 0); // Check if tree is balanced after insertions

    empl.sin = 2;
    avl.insert(empl);
    node *res = avl.Find(avl.GetRoot(), 2);
    assert(res->empl.sin != 2);
    std::cout << "testInsert passed.\n";
}

const int NUM = 20;
ofstream outfile;
int treeHeight = 0;

int main() {
    // testInsert();
    
    DBTesting dbt;
    // needs to be timed
    dbt.test_load(dbt.TestType::AVLTREE);
    dbt.test_deletion();
    
    std::cout << "All tests passed.\n";
    return 0;
}