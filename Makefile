CC = cc
CF = -O -g -Wall

I = -I../repos/SuiteSparse/CXSparse/Include -I../repos/SuiteSparse/SuiteSparse_config
CS = ../repos/SuiteSparse/CXSparse/Lib/libcxsparse.a
CH = main.o add.o jac.o print.o randmat.o set.o test.o
S = source/

all:  main

main:  $(CH)
	$(CC) $(CF) $(I) -o main $(CH) $(CS)

main.o: $(S)main.c $(S)mysparse.h
	$(CC) $(CF) $(I)  -c $(S)main.c

add.o: $(S)add.c
	$(CC) $(CF) $(I) -c $(S)add.c

jac.o: $(CS) $(S)jac.c $(S)mysparse.h
	$(CC) $(CF) $(I) -c $(S)jac.c

print.o: $(CS) $(S)print.c
	$(CC) $(CF) $(I) -c $(S)print.c

randmat.o: $(CS) $(S)randmat.c
	$(CC) $(CF) $(I) -c $(S)randmat.c

set.o: $(CS) $(S)set.c
	$(CC) $(CF) $(I) -c $(S)set.c

test.o: $(CS) $(S)test.c $(S)mysparse.h
	$(CC) $(CF) $(I) -c $(S)test.c

clean:
	- $(RM) *.o main
