CC = cc
CF = -O -g

I = -I../repos/SuiteSparse/CXSparse/Include -I../repos/SuiteSparse/SuiteSparse_config

CS = ../repos/SuiteSparse/CXSparse/Lib/libcxsparse.a
CH = add.c create.c acc.c print.c err.c #jac.c

all: $(CS) test1

test1: $(CS) test1.c Makefile $(CS)
	$(CC) $(CF) $(I) -o test1 test1.c $(CH) $(CS) -lm


.PHONY: test1

clean:
	- $(RM) *.o main
