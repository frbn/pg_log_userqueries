#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>



float  get_io_pressure(void) ;

void main(int argc, char **argv) {

 float ret = get_io_pressure();
 ret = roundf(ret);
 //printf("io pressure: avg10=%.2f\n", ret);
 printf("io pressure: total=%i\n", ret);
 exit(errno);
	
}


// -------------------------------

float  get_io_pressure(void) {

	const char *psi = "/proc/pressure/io";
	const char *field = "avg10=";
	//const char *field = "total=";

   char comm[10];
 	char* ptr = NULL;
	char* delim_equal = "=";

	float ret = 0.00;

	FILE *f = fopen(psi, "r");
	if ( f == NULL) {
		printf("Can't open %s  error: %i\n", psi, errno); 
		exit(errno);
	}

	while(! feof(f)) {
		fscanf(f, "%s",comm);  	
		ptr = strstr(comm,field);

		if (ptr != NULL){
			//field found
			printf("field found: %s\n", ptr); 

			// searching first token <with delim "="
			ptr = strtok(comm,delim_equal);
			if ( ptr != NULL ){
				printf("token found: %s\n", ptr); 

				// now searching for next token delim with = 
				ptr = strtok(NULL,delim_equal);
				if (ptr != NULL ){
					printf("token found: %s\n", ptr); 
				// now searching for next token delim with = 
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


