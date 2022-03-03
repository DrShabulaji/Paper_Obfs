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

	unsigned char c = argv[1][0];
	
	if (argc > 1) {
		if (c == 127)
			printf("win\n");
		else
			printf("lose\n");
	} else {
		printf("Usage: program-name character\n");
	}
	if ( garb3 == 127 ) {
		puts("Success !");
		//klee_report_error("err",38,"Secret found!","txt");
	}
	return 0;
}
