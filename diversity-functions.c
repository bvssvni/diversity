

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

int func_mul(calc_data *data, int ac, double a[], int bc, double b[])
{
	int i;
	int max = ac > bc ? ac : bc;
	double sum = 0;
	for (i = 0; i < max; i++) {
		sum += a[ac == 1 ? 0 : i] * b[bc == 1 ? 0 : i];
	}
	int error = push(data, sum);
	if (error > 0) return error;
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

int func_add(calc_data *data, int ac, double a[], int bc, double b[])
{
	int i;
	double sum = 0;
	for (i = 0; i < ac; i++) sum += a[i];
	for (i = 0; i < bc; i++) sum += b[i];
	int error = push(data, sum);
	if (error > 0) return error;
	return 0;
}

int func_sub_sub(calc_data *data, int ac, double a[], int bc, double b[])
{
	int i;
	int max = ac > bc ? ac : bc;
	int error;
	for (i = 0; i < max; i++) {
		error = push(data, a[ac == 1 ? 0 : i] - b[bc == 1 ? 0 : i]);
		if (error > 0) return error;
	}
	return 0;
}

int func_sub(calc_data *data, int ac, double a[], int bc, double b[])
{
	int i;
	double sum = 0;
	for (i = 0; i < ac; i++) sum += a[i];
	for (i = 0; i < bc; i++) sum -= b[i];
	int error = push(data, sum);
	if (error > 0) return error;
	return 0;
}

