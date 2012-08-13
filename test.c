
#include "diversity.h"

#include "diversity-calc-data.c"
#include "diversity-functions.c"
#include "diversity-parsing.c"
#include "diversity-calc.c"
#include "diversity-unittest.c"

int main(int argc, char* argv[])
{
	test();

	/*
	double_arr a = {.n = 3, .arr = (double[]){1,2,3}};
	double_arr b = {.n = 3, .arr = (double[]){2,3,4}};

	double res[3];
	int n;
	
	double_arr args[] = {a,b};
	
	clock_t start, end;
	start = clock();
	int i;
	int iterations = 1;
	for (i = 0; i < iterations; i++) {
		calc(" 0 ++ 0 ++ 0 ", 2, args, &n, res);
	}
	end = clock();
	double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Sec: %g\r\n", elapsed);
	double cl = log(iterations / elapsed) / log(2);
	printf("CL: %g\r\n", cl);
	
	print_array(n, res);
	*/
	
	return 0;
}
