#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int garb3 = 0;
	for (int it=0; it<argv[1][3]; it++) {
		garb3++;
	}


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
	register const char *s, *t;

	for (t = str; *t; ++t) {
		sum += *t;
	}
			
	printf("Sum is: %d\n", sum);
	
	if ( garb3 == 127 ) {
		puts("Success !");
		//klee_report_error("err",40,"Secret found!","txt");
	}
	return 0;
}
