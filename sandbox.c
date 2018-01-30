#include "cs.h"
#include "mysparse.h"
#include <string.h>

/*interactive testing of functions*/

void sandbox()
{
	cs *T; int m,n,r,c,triplet; double v,err,test;
	char cont; char * cmd; char * c1 = "add"; char * c2 = "mod"; char * c3 = "del";
	char * c4 = "print"; char * c5 = "help"; char * c6 = "stop"; char *c7 = "array";

	while (1)
	{
		printf ("Choose to create compressed matrix (0) or triplet/uncompressed matrix (1): ");
		if (scanf ("%d", &triplet)) { } 
		printf ("Enter <rows> <columns> of matrix: ");
		if (scanf ("%d %d", &m,&n)) T = create (m,n,triplet);
		while (1) {
			cmd = (char*) malloc (sizeof(char) * 10);				
			printf ("Enter a command (e.g. help): ");
			if (scanf ("%s", cmd)) { }
			if (strcmp (cmd,c1)==0) { if (scanf ("%d %d %lf",&r,&c,&v)) errprint_one (add(T,r,c,v)); }
			else if (strcmp (cmd,c2)==0) { if (scanf ("%d %d %lf",&r,&c,&v)) errprint_one (mod(T,r,c,v)); }
			else if (strcmp (cmd,c3)==0) { if (scanf ("%d %d",&r,&c)) errprint_one (del(T,r,c)); }
			else if (strcmp (cmd,c4)==0) { if (print (T)) printf ("Must be a valid matrix\n"); }
			else if (strcmp (cmd,c7)==0) { if (array (T)) printf ("Must be a valid matrix\n"); }
			else if (strcmp (cmd,c5)==0)
			{
				printf ("\nadd <i> <j> <v>: adds an element\nmod <i> <j> <v>: changes an element\n");
				printf ("del <i> <j>: delete an element\n");
				printf ("print: print the matrix\narray: print matrix arrays\nstop: end program\n\n");
			}
			else if (strcmp (cmd,c6)==0) { break; }
			else {printf ("Invalid command\n");}
			free (cmd);
		}
		free (cmd); print (T); cs_spfree (T);
		printf ("Create another matrix? (y/n): ");
		if (scanf("%s",&cont)) if (cont == 'n' || cont == 'N') break;
	}
}
