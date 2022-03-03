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

	if (argc < 2) {
		printf("Usage: program-name argument\n");
	
		return 1;
	}
	
	unsigned char c = argv[1][0];
	if (c == 127)
		printf("win\n");
	else
		printf("lose\n");

	if (garb1 == 127) {
		puts("Success !");
		//klee_report_error("err",22,"Secret found!","txt");
	}

	return 0;
}
