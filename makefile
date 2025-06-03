all: programa

programa: main.o bst.o tree_utils.o
	g++ main.o bst.o tree_utils.o -o programa

main.o: main.cpp .\src\bst.h .\src\tree_utils.h
	g++ -c main.cpp -o main.o

bst.o: .\src\bst.cpp .\src\bst.h
	g++ -c .\src\bst.cpp -o bst.o

tree_utils.o: .\src\tree_utils.cpp .\src\tree_utils.h
	g++ -c .\src\tree_utils.cpp -o tree_utils.o

clean:
	rm -f *.o programa