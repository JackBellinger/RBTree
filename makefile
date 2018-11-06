all: bst timeRBTree clean

bst: RBTreeEngine.o RBTree.o 
	g++ -std=c++11 manualInstantiation.cpp -o rbt -g

timeRBTree: timing.o RBTree.o
	g++ -std=c++11 timeInstantiation.cpp -I/usr/include/python2.7 -lpython2.7 -o timeRBTree -g 

timing.o: timing.cpp
	g++ -std=c++11 -c timing.cpp -g -I/usr/include/python2.7 -lpython2.7 
RBTree.o: RBTree.cpp
	g++ -std=c++11 -c RBTree.cpp -g
RBTreeEngine.o: RBTreeEngine.cpp
	g++ -std=c++11 -c RBTreeEngine.cpp -g
clean:
	rm -rf *o
