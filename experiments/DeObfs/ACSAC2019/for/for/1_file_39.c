#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int garb0 = 0;
	char var0;
	//klee_make_symbolic(&var0,sizeof(var0),"var0");
	for (int it=0; it<var0; it++) {
		garb0++;
	}

	int i;
	int sum = 0;
	
	for (i = 0; i < argc; i++) {
		sum += i; 
	}
	
	printf("Sum is: %d\n", sum);
	
	if ( garb0 == 127 ) {
		puts("Success !");
		//klee_report_error("err",21,"Secret found!","txt");
	}
	return 0;
}
