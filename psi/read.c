#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


float  get_io_pressure(void) ;

void main(int argc, char **argv) {

 float ret = get_io_pressure();
 printf("io pressure: avg10=%f\n", ret);
 exit(errno);
	
}


// -------------------------------

float  get_io_pressure(void) {

	const char *psi = "/proc/pressure/io";
	const char *avg10 = "avg10=";

   char comm[1000];
 	char* ptr = NULL;
	char* delim_equal = "=";
	char* delim_space = " ";

	float ret = 0.00;

	FILE *f = fopen(psi, "r");
	if ( f == NULL) {
		printf("Can't open %s  error: %i\n", psi, errno); 
		exit(errno);
	}

	while(! feof(f)) {
		fscanf(f, "%s",comm);  	

		ptr = strstr(comm,avg10);
		if (ptr != NULL){
			//avg10= found

			// searching first token <with delim "="
			ptr = strtok(comm,delim_equal);
			if ( ptr != NULL ){
				// now searching for next token delim with = 
				ptr = strtok(NULL,delim_equal);
				if (ptr != NULL ){
					ret = atof(ptr);
					return ret;
				}
			}
			fclose(f) ;
			exit(0);
		}
	}
	fclose(f);
}


