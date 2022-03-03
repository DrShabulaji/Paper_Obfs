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

	int i;
	int sum = 0;
	
	for (i = 0; i < argv[1][0]; i++)
		sum += i;
	
	if (sum > 8128)
		printf("Sum is: %d\n", sum);
	else
		printf("Sum is: %d\n", sum);
	
	if ( garb3 == 127 ) {
		puts("Success !");
		//klee_report_error("err",39,"Secret found!","txt");
	}
	return 0;
}
