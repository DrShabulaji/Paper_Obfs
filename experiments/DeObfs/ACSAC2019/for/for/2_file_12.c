#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int garb1 = 0;
	char var1;
	//klee_make_symbolic(&var1,sizeof(var1),"var1");
	for (int it=0; it<var1; it++) {
		garb1++;
	}


	int garb0 = 0;
	char var0;
	//klee_make_symbolic(&var0,sizeof(var0),"var0");
	for (int it=0; it<var0; it++) {
		garb0++;
	}

	int i;
	int sum = 0;
	
	for (i = 0; i < argv[1][0]; i++) {
		sum += i; 
	}
	
	for (i = 0; i < argv[1][0]; i++) {
		sum += i; 
	}
	
	printf("Sum is: %d\n", sum);
	
	if (garb1 == 127) {
		puts("Success !");
		//klee_report_error("err",33,"Secret found!","txt");
	}
	return 0;
}
