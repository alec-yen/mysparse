CC = cc
CF = -O -g -Wall

I = -I../repos/SuiteSparse/CXSparse/Include -I../repos/SuiteSparse/SuiteSparse_config

CS = ../repos/SuiteSparse/CXSparse/Lib/libcxsparse.a
CH = test.o add.o create.o jac.o print.o

all:  main

main:  $(CH)
	$(CC) $(CF) $(I) -o main $(CH) $(CS)

test.o: test.c
	$(CC) $(CF) $(I) -c test.c

add.o: add.c
	$(CC) $(CF) $(I) -c add.c

create.o: create.c
	$(CC) $(CF) $(I) -c create.c

jac.o: $(CS) jac.c
	$(CC) $(CF) $(I) -c jac.c

print.o: $(CS) print.c
	$(CC) $(CF) $(I) -c print.c


clean:
	- $(RM) *.o main
