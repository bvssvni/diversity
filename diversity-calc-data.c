
void die(char *message)
{
	fprintf(stderr, message);
	exit(1);
}

void push_arr(calc_data *data, int n, double* arr)
{
	memcpy(data->buffer + data->buffer_index, arr, n * sizeof(double));
	data->buffer_index += n;
}

int push(calc_data *data, double a)
{
	if (data->result_index >= data->result_size) return ERROR_BUFFER_OVERFLOW;
	data->result[data->result_index++] = a;
	return 0;
}

void calc_push_stack(calc_data *data, int op)
{
	data->stack[data->stack_index++] = op;
}

int calc_pop_stack(calc_data *data)
{
	return data->stack[--data->stack_index];
}

int calc_last_operator(calc_data *data)
{
	if (data->stack_index <= 1) return -1;
	return data->stack[data->stack_index - 2];
}


void calc_read_whitespace(calc_data *data)
{
	data->delta = parse_whitespace(data->expr + data->pos);
	#if DEBUG
	if (data->delta > 0) printf("Read whitespace\r\n");
	#endif
}

void calc_read_variable(calc_data *data)
{
	data->delta = parse_number(data->expr + data->pos);
	if (data->delta <= 0) return;

	int v = atoi(data->expr + data->pos);
	if (v >= data->argc) die("Argument is too high");
	#if DEBUG
	printf("Read variable %i\r\n", v);
	#endif
	double_arr arg = data->argv[v];
	
	// Push location in buffer to stack.
	calc_push_stack(data, data->buffer_index);
	// Push array.
	push_arr(data, arg.n, arg.arr);
}

int calc_do_operation(calc_data *data)
{
	int arg2 = calc_pop_stack(data);
	int opIndex = calc_pop_stack(data);
	int arg1 = calc_pop_stack(data);
	
	int n1 = arg2 - arg1;
	int n2 = data->buffer_index - arg2;
	
	binary_operator op = data->ops[opIndex];
	int error = op.func(data, n1, data->buffer + arg1, n2, data->buffer + arg2);
	if (error > 0) return error;
	
	#if DEBUG
	printf("Result index %i\r\n", data->result_index);
	#endif
	
	// Copy data from result to buffer.
	memcpy(data->buffer + arg1, data->result, data->result_index * sizeof(double));
	data->buffer_index = arg1 + data->result_index;
	data->result_index = 0;
	
	#if DEBUG
	printf("Do operation stack index %i\r\n", data->stack_index);
	#endif
	
	calc_push_stack(data, arg1);
	
	#if DEBUG
	printf("Did it!\r\n");
	#endif
	
	return 0;
}

int calc_read_operator(calc_data *data)
{
	int opIndex;
	data->delta = parse_operator(data->ops_size, data->ops, data->expr + data->pos, &opIndex);
	if (data->delta <= 0) return 0;
	#if DEBUG
	printf("Read operator %s\r\n", ops[opIndex]);
	#endif
	
	int lastOpIndex = calc_last_operator(data);
	if (lastOpIndex != -1 && data->ops[lastOpIndex].prec >= data->ops[opIndex].prec) {
		int error = calc_do_operation(data);
		if (error > 0) return error;
	}
	
	calc_push_stack(data, opIndex);
	
	#if DEBUG
	if (data->stack_index % 2 == 1) die("Operator not following variable");
	printf("Stack index operator %i\r\n", data->stack_index);
	#endif
	
	data->state_index = STATE_INDEX_RESET;
	
	return 0;
}

