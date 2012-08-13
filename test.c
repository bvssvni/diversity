
/*
Made by Sven Nilsen.
v1.002	Added one buffer overflow check.
v1.001	Added some unit tests.
v1.000	Created basic skeleton.
*/

#include "diversity.h"

#include "diversity-calc-data.c"
#include "diversity-functions.c"
#include "diversity-parsing.c"
#include "diversity-calc.c"

#define TEST(a, b) if (!(a)) { \
	printf("%i: %s\r\n", __LINE__, #a); \
	b; \
	die("failed unit test"); \
	}
void test()
{
	{
		int n = parse_number("3");
		TEST(n == 1, printf("%i\r\n", n));
		n = parse_number(" 3");
		TEST(n == 0, printf("%i\r\n", n));
		n = parse_number("30");
		TEST(n == 2, printf("%i\r\n", n));
		n = parse_number("3 ");
		TEST(n == 1, printf("%i\r\n", n));
	}
	{
		int n = parse_whitespace("");
		TEST(n == 0, printf("%i\r\n", n));
		n = parse_whitespace(" ");
		TEST(n == 1, printf("%i\r\n", n));
		n = parse_whitespace("  ");
		TEST(n == 2, printf("%i\r\n", n));
	}
	{
		int op;
		int n = parse_operator(STANDARD_OPS_SIZE, STANDARD_OPS, "**", &op);
		TEST(n == 2, printf("%i\r\n", n));
		TEST(strcmp(STANDARD_OPS[op].op, "**") == 0, printf("%i\r\n", op));
	}
	{
		double_arr a = {.n = 1, .arr = (double[]){2}};
		double_arr b = {.n = 4, .arr = (double[]){1,2,3,4}};
		double_arr args[] = {a,b};
		double res[4];
		int n;
		int error = calc(" 0 ** 1", 2, args, &n, res);
		TEST(error == 0, printf("Error %i\r\n", error));
		TEST(n == 4, printf("%i\r\n", n));
		TEST(res[0] == 2, printf("%g\r\n", res[0]));
		TEST(res[1] == 4, printf("%g\r\n", res[1]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){2,3}};
		double_arr b = {.n = 2, .arr = (double[]){3,2}};
		double_arr args[] = {a,b};
		double res[2];
		int n;
		calc("0**1", 2, args, &n, res);
		TEST(n == 2, printf("%i\r\n", n));
		TEST(res[0] == 6, printf("%g\r\n", res[0]));
		TEST(res[1] == 6, printf("%g\r\n", res[1]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){2,3}};
		double_arr b = {.n = 2, .arr = (double[]){3,2}};
		double_arr args[] = {a,b};
		double res[2];
		int n;
		calc("0++1", 2, args, &n, res);
		TEST(n == 2, printf("%i\r\n", n));
		TEST(res[0] == 5, printf("%g\r\n", res[0]));
		TEST(res[1] == 5, printf("%g\r\n", res[1]));
	}
	printf("unit test complete\r\n");
}

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
