

int func_mul_mul(calc_data *data, int ac, double a[], int bc, double b[])
{
	int i;
	int max = ac > bc ? ac : bc;
	int error;
	for (i = 0; i < max; i++) {
		error = push(data, a[ac == 1 ? 0 : i] * b[bc == 1 ? 0 : i]);
		if (error > 0) return error;
	}
	return 0;
}

int func_add_add(calc_data *data, int ac, double a[], int bc, double b[])
{
	int i;
	int max = ac > bc ? ac : bc;
	int error;
	for (i = 0; i < max; i++) {
		error = push(data, a[ac == 1 ? 0 : i] + b[bc == 1 ? 0 : i]);
		if (error > 0) return error;
	}
	return 0;
}
