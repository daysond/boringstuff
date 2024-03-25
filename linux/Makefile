CC=g++
CFLAGS=-I
CFLAGS+=-Wall
FILES=AVLTree.cpp
FILES+=timer.cpp

Test_Unit_Test: $(FILES) Test_Unit_Test.cpp DBTesting.cpp
	$(CC) $(CFLAGS) $^ -o $@

Test_Memory_Leak: $(FILES) Test_Memory_Leak.cpp DBTesting.cpp
	$(CC) $(CFLAGS) $^ -o $@

Test_Max_Size: $(FILES) Test_Max_Size.cpp DBTesting.cpp
	$(CC) $(CFLAGS) $^ -o $@

Test_Load: $(FILES) Test_Load.cpp DBTesting.cpp
	$(CC) $(CFLAGS) $^ -o $@

Test_Search_Speed: $(FILES) Test_Load.cpp DBTesting.cpp
	$(CC) $(CFLAGS) $^ -o $@



clean:
	rm -f *.o Test_Memory_Leak Test_Unit_Test Test_Search_Speed Test_Load Test_Max_Size

all: Test_Memory_Leak Test_Unit_Test Test_Search_Speed Test_Load Test_Max_Size

