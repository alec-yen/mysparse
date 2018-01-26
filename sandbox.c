#include "cs.h"
#include "mysparse.h"
#include <string.h>

/*test functions*/
/*
	To-do List
	//no checks for mod or add against values of 0
	//no safeguards against entering letters
	//create has no error checks
	//can only work with one matrix at a time
*/

void sandbox()
{
	cs *A; 
	cs *T;
	int m,n,r,c,t;
	double v,err,test;

	char * cmd;
	char * c1 = "set"; char * c2 = "mod"; char * c3 = "del";
	char * c4 = "print"; char * c5 = "help"; char * c6 = "stop"; char *c7 = "csc";

	printf ("Choose to create compressed matrix (0) or triplet/uncompressed matrix (1): ");
	if (scanf ("%d", &t)) { } 
	printf ("Enter <rows> <columns> of matrix: ");
	if (scanf ("%d %d", &m,&n)){
		if (t) T = cs_spalloc (m,n,m*n,1,1);
		if (!t) { A = cs_spalloc (m,n,m*n,1,1); T = cs_compress(A); cs_spfree (A); }
	}
	while (1) {
		cmd = (char*) malloc (sizeof(char) * 10);				
		printf ("Enter a command (e.g. help): ");
		if (scanf ("%s", cmd)) { }
		if (strcmp (cmd,c1)==0) //set
		{
			if (scanf ("%d %d %lf",&r,&c,&v))
			{
				err = set(T,r,c,v);
				if (!err) printf ("%.2f at index (%d,%d) added\n",v,r,c);
				else if (err==2) printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);
				else if (err==1) printf ("%.2f already exists at index (%d,%d)\n",acc(T,r,c),r,c);
			}
		}		
		else if (strcmp (cmd,c2)==0) //mod
		{
			if (scanf ("%d %d %lf",&r,&c,&v))
			{
				test = acc(T,r,c);
				err = mod(T,r,c,v);
				if (!err) printf ("Index (%d,%d) changed from %.2f to %.2f\n",r,c,test,v);
				else if (err==2) printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);
				else if (err==1) printf ("No value exists at index (%d,%d)\n",r,c);
			}
		}
		else if (strcmp (cmd,c3)==0) //delete
		{
			if (scanf ("%d %d",&r,&c))
			{
				test = acc(T,r,c);
				err = del(T,r,c);
				if (!err) printf ("Value %.2f at index (%d,%d) deleted\n",test,r,c);
				else if (err==2) printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);
				else if (err==1) printf ("No value exists at index (%d,%d)\n",r,c);
			}
		}
		else if (strcmp (cmd,c4)==0) { if (print (T)) printf ("Must be a valid matrix\n"); }
		else if (strcmp (cmd,c5)==0) //help
		{
			printf ("\nset <i> <j> <v>: sets an element\n");
			printf ("mod <i> <j> <v>: changes an element\n");
			printf ("del <i> <j>: delete an element\n");
			printf ("print: print the matrix\ncsc: print CSC arrays\nstop: end program\n\n");
		}
		else if (strcmp (cmd,c6)==0) { break; }
		else if (strcmp (cmd,c7)==0) { if (csc (T)) printf ("Must be a non-empty compressed matrix\n"); }
		else {printf ("Invalid command\n");}
		free (cmd);
	}
	free (cmd);
	print (T);
	cs_spfree(T);
}
