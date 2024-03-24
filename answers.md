# Answers to the Questions

1. I think the amount of tests we've performed for both AVL and MAP in this should clear out any ambiguities we have regarding theproblem given in this assignment, that is to find a data
   structure that is to correspond to events and requests as fast as possible,but if we were to include any more tests ,then that would be testing out the concurrency of
   the data structure, that is how well the data structure perfroms whiel running in a multi threaded enviornment , we would test on cases like race conditions, memory corruption and speed of accessing the data in a multi threaded enviornment.

2. 

3. The AVL tree that we have over here, we wouldn't say it is reusable just because you can see that while inserting the nodes into the tree, removing nodes , the parameter asks for a variable that is of the type EmployeeInfo and in the case of removing the node it asks for sin, so in that case we can't just take this data structure implemented and use it in different situatuations where the nodes can be of different types. Most of the important operations of the AVLTree is however reusable , like all of the rotations and makeEmpty , they can be reused.

4. The approach that we used in the testing part is to create a class which contains various tests for different types of data structure, the approach that we have used is to create modular functions for each test and have parameterized test function cases. The only thing here is that we're skeptical about is to have templatized data structures and call their functions based on a standardized functions, if we had to test out databses that are almost similar to what we have , like redBlack trees, 2-3 trees, this code is deifntely reusable

