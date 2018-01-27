#include "cs.h"
#include "mysparse.h"
#include <string.h>

/*test functions*/

void sandbox()
{
	cs *T;
	int m,n,r,c,triplet;
	double v,err,test;

	char * cmd;
	char * c1 = "add"; char * c2 = "mod"; char * c3 = "del";
	char * c4 = "print"; char * c5 = "help"; char * c6 = "stop"; char *c7 = "array";

	printf ("Choose to create compressed matrix (0) or triplet/uncompressed matrix (1): ");
	if (scanf ("%d", &triplet)) { } 
	printf ("Enter <rows> <columns> of matrix: ");
	if (scanf ("%d %d", &m,&n)){
		T = create (m,n,triplet);
	}
	while (1) {
		cmd = (char*) malloc (sizeof(char) * 10);				
		printf ("Enter a command (e.g. help): ");
		if (scanf ("%s", cmd)) { }
		if (strcmp (cmd,c1)==0) //add
		{
			if (scanf ("%d %d %lf",&r,&c,&v))
			{
				err = add(T,r,c,v);
				if (!err) printf ("Value %.2f added at index (%d,%d)\n",v,r,c);
				else if (err==3) printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);
				else if (err==2) printf ("%.2f already exists at index (%d,%d)\n",acc(T,r,c),r,c);
				else if (err==1) printf ("Cannot add value of zero\n");
			}
		}		
		else if (strcmp (cmd,c2)==0) //mod
		{
			if (scanf ("%d %d %lf",&r,&c,&v))
			{
				test = acc(T,r,c);
				err = mod(T,r,c,v);
				if (!err) printf ("Index (%d,%d) changed from %.2f to %.2f\n",r,c,test,v);
				else if (err==3) printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);
				else if (err==2) printf ("No value exists at index (%d,%d)\n",r,c);
			}
		}
		else if (strcmp (cmd,c3)==0) //delete
		{
			if (scanf ("%d %d",&r,&c))
			{
				test = acc(T,r,c);
				err = del(T,r,c);
				if (!err) printf ("Value %.2f at index (%d,%d) deleted\n",test,r,c);
				else if (err==3) printf ("Index (%d,%d) outside %d by %d matrix\n",r,c,m,n);
				else if (err==2) printf ("No value exists at index (%d,%d)\n",r,c);
			}
		}
		else if (strcmp (cmd,c4)==0) { if (print (T)) printf ("Must be a valid matrix\n"); }
		else if (strcmp (cmd,c5)==0) //help
		{
			printf ("\nadd <i> <j> <v>: adds an element\n");
			printf ("mod <i> <j> <v>: changes an element\n");
			printf ("del <i> <j>: delete an element\n");
			printf ("print: print the matrix\narray: print matrix arrays\nstop: end program\n\n");
		}
		else if (strcmp (cmd,c6)==0) { break; }
		else if (strcmp (cmd,c7)==0) { if (array (T)) printf ("Must be valid, non-empty matrix\n"); }
		else {printf ("Invalid command\n");}
		free (cmd);
	}
	free (cmd);
	print (T);
	cs_spfree(T);
}
