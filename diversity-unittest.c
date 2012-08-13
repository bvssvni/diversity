

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
	{
		double_arr a = {.n = 2, .arr = (double[]){1,2}};
		double_arr b = {.n = 1, .arr = (double[]){3}};
		double_arr args[] = {a,b};
		double res[1];
		int n;
		calc("0*1", 2, args, &n, res);
		TEST(n == 1, printf("%i\r\n", n));
		TEST(res[0] == 9, printf("%g\r\n", res[0]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){3,2}};
		double_arr b = {.n = 1, .arr = (double[]){1}};
		double_arr args[] = {a,b};
		double res[1];
		int n;
		calc("0+1", 2, args, &n, res);
		TEST(n == 1, printf("%i\r\n", n));
		TEST(res[0] == 6, printf("%g\r\n", res[0]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){0,0}};
		double_arr b = {.n = 2, .arr = (double[]){1,2}};
		double_arr args[] = {a,b};
		double res[2];
		int n;
		calc("0++-1", 2, args, &n, res);
		TEST(n == 2, printf("%i\r\n", n));
		TEST(res[0] == -1, printf("%g\r\n", res[0]));
		TEST(res[1] == -2, printf("%g\r\n", res[1]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){1,2}};
		double_arr b = {.n = 1, .arr = (double[]){3}};
		double_arr args[] = {a,b};
		double res[1];
		int n;
		calc("0-1", 2, args, &n, res);
		TEST(n == 1, printf("%i\r\n", n));
		TEST(res[0] == 0, printf("%g\r\n", res[0]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){2,4}};
		double_arr b = {.n = 2, .arr = (double[]){2,2}};
		double_arr args[] = {a,b};
		double res[1];
		int n;
		calc("0//1", 2, args, &n, res);
		TEST(n == 2, printf("%i\r\n", n));
		TEST(res[0] == 1, printf("%g\r\n", res[0]));
		TEST(res[1] == 2, printf("%g\r\n", res[1]));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){2,4}};
		double_arr b = {.n = 2, .arr = (double[]){1,0}};
		double_arr args[] = {a,b};
		double res[2];
		int n;
		int error = calc("0//1", 2, args, &n, res);
		TEST(error == ERROR_DIVIDING_BY_ZERO, printf("%i\r\n", error));
	}
	{
		double_arr a = {.n = 2, .arr = (double[]){6,3}};
		double_arr b = {.n = 2, .arr = (double[]){3,3}};
		double_arr args[] = {a,b};
		double res[1];
		int n;
		calc("0/1", 2, args, &n, res);
		TEST(n == 1, printf("%i\r\n", n));
		TEST(res[0] == 3, printf("%g\r\n", res[0]));
	}
	printf("unit test complete\r\n");
}
