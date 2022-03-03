#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int garb2 = 0;
	for (int it=0; it<argv[1][2]; it++) {
		garb2++;
	}


	int garb1 = 0;
	for (int it=0; it<argv[1][1]; it++) {
		garb1++;
	}


	int garb0 = 0;
	for (int it=0; it<argv[1][0]; it++) {
		garb0++;
	}

	int i,j;
	int sum = 0;
	
	const char *str = argv[1];
	register const char *s;

	for (s = str; *s; ++s) {
		sum += *s;
	}
	
	unsigned int len = (s - str);
	
	for (i = 0; i < len; i++) {
			sum += str[i]; 
	}
	
	printf("Sum is: %d\n", sum);
	
	if ( garb2 == 127 ) {
		puts("Success !");
		//klee_report_error("err",22,"Secret found!","txt");
	}
	return 0;
}
