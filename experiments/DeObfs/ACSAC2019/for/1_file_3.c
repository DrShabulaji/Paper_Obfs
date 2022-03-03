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
	register const char *s;

	for (s = str; *s; ++s) {
		sum += *s;
	}
	
	unsigned int len = (s - str);
	
	for (i = 0; i < len; i++) {
			sum += str[i]; 
	}
	
	printf("Sum is: %d\n", sum);
	
	if ( garb0 == 127 ) {
		puts("Success !");
		//klee_report_error("err",30,"Secret found!","txt");
	}
	return 0;
}
