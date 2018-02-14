CC = cc
CF = -O -g -Wall

I = -I../repos/SuiteSparse/CXSparse/Include -I../repos/SuiteSparse/SuiteSparse_config

CS = ../repos/SuiteSparse/CXSparse/Lib/libcxsparse.a
CH = main.o add.o create.o jac.o print.o randmat.c

all:  main

main:  $(CH)
	$(CC) $(CF) $(I) -o main $(CH) $(CS)

main.o: main.c mysparse.h
	$(CC) $(CF) $(I)  -c main.c

add.o: add.c mysparse.h
	$(CC) $(CF) $(I) -c add.c

create.o: create.c mysparse.h
	$(CC) $(CF) $(I) -c create.c

jac.o: $(CS) jac.c mysparse.h
	$(CC) $(CF) $(I) -c jac.c

print.o: $(CS) print.c mysparse.h
	$(CC) $(CF) $(I) -c print.c

randmat.o: $(CS) randmat.c mysparse.h
	$(CC) $(CF) $(I) -c randmat.c

clean:
	- $(RM) *.o main
