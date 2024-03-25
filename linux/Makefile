CC=g++
CFLAGS=-I
CFLAGS+=-Wall
FILES=AVLTree.cpp
FILES+=timer.cpp
FILES+=main.cpp
# FILES+=Test.cpp

avlTree: $(FILES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o avlTree

all: avlTree

