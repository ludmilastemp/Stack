a.exe:  main.o stack.o error.o hash.o
	g++ main.o stack.o error.o hash.o -o a.exe

main.o: main.cpp   STL_stack.h STL_stack_struct.h STL_stack_const.h error.h
	g++ -c main.cpp  -o main.o

stack.o: stack.cpp STL_stack.h STL_stack_struct.h STL_stack_const.h error.h
	g++ -c stack.cpp -o stack.o

error.o: error.cpp             STL_stack_struct.h STL_stack_const.h error.h hash.h
	g++ -c error.cpp -o error.o

hash.o:  hash.cpp
	g++ -c hash.cpp  -o hash.o


clean:
	rm -rf main.o stack.o error.o hash.o a.exe
