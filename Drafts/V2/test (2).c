#include "cs.h"
#include "mysparse.h"
#include <string.h>

/*test functions*/
/*
	To-do List
	//no checks for alter or add against values of 0
	//no safeguards against entering letters
	//create has no error checks
	//can only work with one matrix at a time
*/


/*alter,add,delete test*/
int main()
{
	cs *T;
	int m,n,r,c;
	double v,test;
	char * name = "m_test.txt";

	char * cmd;
	char * c1 = "add"; char * c2 = "alter"; char * c3 = "delete";
	char * c4 = "print"; char * c5 = "help"; char * c6 = "stop"; char *c7 = "csc";


	printf ("Enter <rows> <columns> of matrix: ");
	if (scanf ("%d %d", &m,&n)) 
		T = ccreate_empty (name,m,n,0,0,0,0);
	while (1) {
		cmd = (char*) malloc (sizeof(char) * 10);				
		printf ("Enter a command (e.g. help): ");
		if (scanf ("%s", cmd)) { }
		if (strcmp (cmd,c1)==0) //add
		{
			if (scanf ("%d %d %lf",&r,&c,&v))
			{
				test = access (T,r,c);
				if (!test)
				{
					printf ("%.2f at index (%d,%d) added\n",v,r,c);
					T = add (T,r,c,v);
				}
				else if (test == 999)
				{printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);}
				else 
				{printf ("%.2f already exists at index (%d,%d)\n",test,r,c);}
			}
		}		
		else if (strcmp (cmd,c2)==0) //alter
		{
			if (scanf ("%d %d %lf",&r,&c,&v))
			{
				test = access (T,r,c);
				if (test != 999 && test != 0)
				{
					printf ("Index (%d,%d) changed from %.2f to %.2f\n",r,c,test,v);
					alter (T,r,c,v);
				}
				else if (test == 999)
				{printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);}
				else 
				{printf ("No value exists at index (%d,%d)\n",r,c);}
			}
		}
		else if (strcmp (cmd,c3)==0) //delete
		{
			if (scanf ("%d %d",&r,&c))
			{
				
				test = access (T,r,c);
				if (test != 999 && test != 0)
				{
					printf ("Value %.2f at index (%d,%d) deleted\n",test,r,c);
					delete (T,r,c);
				}
				else if (test == 999)
				{printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);}
				else 
				{printf ("No value exists at index (%d,%d)\n",r,c);}
			}
		}
		else if (strcmp (cmd,c4)==0) { print (T); }
		else if (strcmp (cmd,c5)==0) //help
		{
			printf ("\nadd <i> <j> <v>: adds an element\n");
			printf ("alter <i> <j> <v>: changes an element\n");
			printf ("delete <i> <j>: delete an element\n");
			printf ("print: print the matrix\ncsc: print CSC arrays\nstop: end program\n\n");
		}
		else if (strcmp (cmd,c6)==0) { break; }
		else if (strcmp (cmd,c7)==0) { csc (T); }
		else {printf ("Invalid command\n");}
		free (cmd);
	}
	free (cmd);
	print (T);
	cs_spfree(T);
}
