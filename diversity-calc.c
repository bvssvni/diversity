
binary_operator STANDARD_OPS[] = {
	{.op = "++-", .prec = 0, .func = func_sub_sub},
	{.op = "**", .prec = 1, .func = func_mul_mul},
	{.op = "//", .prec = 1, .func = func_div_div},
	{.op = "++", .prec = 0, .func = func_add_add},
	{.op = "*", .prec = 1, .func = func_mul},
	{.op = "/", .prec = 1, .func = func_div},
	{.op = "+", .prec = 0, .func = func_add},
	{.op = "-", .prec = 0, .func = func_sub}
};

int STANDARD_OPS_SIZE = sizeof(STANDARD_OPS)/sizeof(binary_operator);

int calc(char* expr, int argc, double_arr argv[], int *resc, double resv[])
{
	double buffer[BUFFER_SIZE];
	double result[RESULT_SIZE];
	int stack[STACK_SIZE];
	char* state = " v + v +";
	int error;

	calc_data data = {
		.buffer_size = BUFFER_SIZE, .buffer = buffer,
		.stack_size = STACK_SIZE, .stack = stack,
		.result_size = RESULT_SIZE, .result = result,
		.expr = expr,
		.argc = argc, .argv = argv,
		.state_length = strlen(state),
		.ops = STANDARD_OPS, .ops_size = STANDARD_OPS_SIZE
	};
	
	for (data.state_index = 0; data.state_index < data.state_length;
	data.state_index++, data.pos += data.delta) {
		#if DEBUG
		if (data.delta > 0 ) printf("%i\r\n", data.pos);
		#endif
		switch (state[data.state_index]) {
			case ' ':
				calc_read_whitespace(&data);
				break;
			case 'v':
				calc_read_variable(&data);
				break;
			case '+':
				error = calc_read_operator(&data);
				if (error > 0) return error;
				break;
		}
	}
	
	#if DEBUG
	if ((data.stack_index % 2) != 1) die("Not ending with variable");
	#endif
	
	// Perform rest of the operations.
	for (; data.stack_index > 2;) {
		#if DEBUG
		printf("Rest stack index %i\r\n", data.stack_index);
		#endif
		error = calc_do_operation(&data);
		if (error > 0) return error;
	}
	
	memcpy(resv, data.buffer, data.buffer_index * sizeof(double));
	*resc = data.buffer_index;
	
	return 0;
}
