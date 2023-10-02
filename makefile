a.exe:  main.o stack.o error.o
	g++ main.o stack.o error.o -o a.exe

main.o: main.cpp   STL_stack.h STL_stack_struct.h STL_stack_const.h error.h
	g++ -c main.cpp  -DCANARY_PROTECTION -DHASH_PROTECTION -o main.o

stack.o: stack.cpp STL_stack.h STL_stack_struct.h STL_stack_const.h error.h
	g++ -c stack.cpp -DCANARY_PROTECTION -DHASH_PROTECTION -o stack.o

error.o: error.cpp             STL_stack_struct.h STL_stack_const.h error.h
	g++ -c error.cpp -DCANARY_PROTECTION -DHASH_PROTECTION -o error.o

# target
#clean:
#	g++ clean main.o stack.o error.o a.exe
