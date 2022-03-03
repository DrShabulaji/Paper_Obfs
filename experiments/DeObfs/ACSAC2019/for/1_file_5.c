#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int garb0 = 0;
	char var0;
	//klee_make_symbolic(&var0,sizeof(var0),"var0");
	for (int it=0; it<var0; it++) {
		garb0++;
	}

	int i,j;
	int sum = 0;
	
	const char *str = argv[1];
	register const char *s, *t;

	for (t = str; *t; ++t) {
		sum += *t;
	}
	
	if (sum > 127)
		sum += *t;
	else
		sum *= *t;
			
	printf("Sum is: %d\n", sum);
	
	if ( garb0 == 127 ) {
		puts("Success !");
		//klee_report_error("err",29,"Secret found!","txt");
	}
	return 0;
}
