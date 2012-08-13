

int parse_number(char* expr)
{
	char c;
	int i;
	for (i = 0;; i++) {
		c = expr[i];
		if (c < '0' || c > '9' || c == '\0') return i;
	}
	return 0;
}

int parse_whitespace(char* expr)
{
	char c;
	int i;
	for (i = 0;; i++) {
		c = expr[i];
		if (c != ' ' || c == '\0') return i;
	}
	return 0;
}

int parse_operator(int ops_size, binary_operator ops[], char *expr, int *opIndex)
{
	char c;
	int i;
	int j;
	char *op;
	for (j = 0; j < ops_size; j++) {
		op = ops[j].op;
		for (i = 0; (c = expr[i]) != '\0'; i++) {
			if (op[i] == '\0' || op[i] != c) break;
		}
		if (op[i] == '\0') {
			*opIndex = j;
			return i;
		}
	}
	return 0;
}

void print_array(int n, double arr[])
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%g\r\n", arr[i]);
	}
}
