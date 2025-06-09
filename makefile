all: avl

avl: main_avl.o avl.o tree_utils.o data.o
	g++ main_avl.o avl.o tree_utils.o data.o -o avl

main_avl.o: .\src\main_avl.cpp .\src\avl.h .\src\tree_utils.h .\src\data.h
	g++ -c .\src\main_avl.cpp -o main_avl.o

avl.o: .\src\avl.cpp .\src\avl.h
	g++ -c .\src\avl.cpp -o avl.o

tree_utils.o: .\src\tree_utils.cpp .\src\tree_utils.h
	g++ -c .\src\tree_utils.cpp -o tree_utils.o

data.o: .\src\data.cpp .\src\data.h
	g++ -c .\src\data.cpp -o data.o

clean:
	del /Q *.o avl.exe