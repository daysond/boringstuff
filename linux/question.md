# Test Report:

## Insertion:

### On Test Case - Duplicate Insertion: 

The tree was only populated with one node.  (See generated graphs)

#### Note: 

[*graphviz*](https://graphviz.org) is needed to generate graph

For linux, run the following command:
``` linux
sudo apt-get update
sudo apt-get install graphviz
```
Windows
```
choco install graphviz
```
MacOS
```
brew install graphviz
```

## Deletion:

The below test cases cause segmetation fault.

```
        // TEST_CASE(test_remove_large_tree);
        // TEST_CASE(test_remove_in_sequence);
        // TEST_CASE(test_remove_in_reverse_sequence);
```

### test_remove_large_tree

Inserts random number into the tree and deletes them in the same order that they are inserted.

### test_remove_in_sequence

Inserts number 1 - 15 and then deletes them in the same order.

### test_remove_in_reverse_sequence

Inserts number 1 - 15 in reversed order then deletes them in the same reserved order.


## Memory Leak

### Linux:

- AVL: no memory leak found

- MAP: no memory leak found

```
All memory leak tests done.
In case memory leak, test AVL and map separately.
==343089== 
==343089== HEAP SUMMARY:
==343089==     in use at exit: 0 bytes in 0 blocks
==343089==   total heap usage: 20,110 allocs, 20,110 frees, 959,856 bytes allocated
==343089== 
==343089== All heap blocks were freed -- no leaks are possible
==343089== 
==343089== For lists of detected and suppressed errors, rerun with: -s
==343089== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Test_Memory_Leak completed.
```

### Windows:

Output suggests no memory leak for AVL and std::map.

```
'MemLeakTest.exe' (Win32): Loaded 'C:\Users\dayson\source\repos\memoryleak\x64\Debug\MemLeakTest.exe'. Symbols loaded.
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\ntdll.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\kernel32.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\KernelBase.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\msvcp140d.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\vcruntime140d.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\vcruntime140_1d.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\ucrtbased.dll'. 
The thread 0x730 has exited with code 0 (0x0).
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\kernel.appcore.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\msvcrt.dll'. 
'MemLeakTest.exe' (Win32): Loaded 'C:\Windows\System32\rpcrt4.dll'. 
The thread 0x1704 has exited with code 0 (0x0).
The thread 0x1a08 has exited with code 0 (0x0).
The program '[15304] MemLeakTest.exe' has exited with code 0 (0x0).
```


## Speed test 

For graphs, see [Speed_Graphs.pdf](./Speed_Graphs.pdf)

- Conclusion: 

The provided graphs demonstrate the performance of AVL trees and Maps when searching for existing and non-existing elements. 
The AVL tree shows greater time taken for existing elements, while its performance for non-existing elements is more stable. 
The Map demonstrates consistently low times for existing elements with some spikes but higher differences in time taken when searching for non-existing elements.
To conclude, Maps may offer faster searches for existing elements and AVL trees may be more predictable for non-existing elements 

## Load Test


## Max Size Test






# Questions

## 1. Are there any other test that you feel are required? Describe them briefly.

Given the requirement of the system, we can:

- Test for concurrency: in such system, data read and write shall not block and is usally implemented in differenct threads, which implies there might be concurrency issues when one thread is trying to read and another is trying to write.

- Test for initial load time for AVL and std::map: the data will eventually be stored on the local storage, testing the initial load time can provide a better insight into the performce

- Test for recovery: upon system crash, are all the latest data saved?

- Test for reliability: how often does the system crash

In terms of the AVL tree itself, we could:

- Test for internal functions: balance, findMin, findMax, rotation functions

- Test for traversal path correctness: ensure in-order, pre-order, and level-order traversal of the tree produce the corrent sequence of elements



## 2. Compare and contrast std::map vs AVL tree for all six test cases above.

### a. Were there unexpected results?

### b. Which would you recommend, std::map or AVL Tree?  

### c. Based on memory tests, what maximum memory would you recommend be reserved for the database?

## 3. Is this AVL Tree reusable for other projects?

The AVL tree is not really reusable without modification given the nodes has dependency on EmployeeInfo. However, a better way would be using a template for AVL, so EmployeeInfo would be a generic type T. And the Node object will handle the underlying logic of data initialization:

```cpp
node *AVL::insert(EmployeeInfo empl, node *t) {
    if (t == NULL) {
        t = new node;
        t->empl.salary = empl.salary;
        t->empl.age = empl.age;
        t->empl.emplNumber = empl.emplNumber;
        t->empl.sin = empl.sin;
        t->height = 0;
        t->left = t->right = NULL;
    }
    ... 
}
```

These code could be in the node class to make the AVL tree class more reusable.


## 4. Is your test software reusable?

It is not really reusable given that the dependency EmployeeInfo. However, we could easily make this generic and make virtual parent class that contains functions suchs as test_insertion(), and also the underlying database type will have to use the same interface for inserting, deleting etc.

For std::map, a wrapper would be required.

For similar AVL tree, the code can be modified to so data can be injected into the test class.

