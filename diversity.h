
#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define STACK_SIZE 1024
#define RESULT_SIZE 1024

#define STATE_INDEX_RESET 0

#define ERROR_BUFFER_OVERFLOW 1

typedef struct double_arr {int n;double *arr;} double_arr;

typedef struct binary_operator binary_operator;

typedef struct calc_data
{
	int buffer_size; double *buffer; int buffer_index;
	int stack_size; int *stack; int stack_index;
	int result_size; double *result; int result_index;
	char *expr; int pos; int delta;
	int argc; double_arr *argv;
	int state_length; int state_index;
	int ops_size; binary_operator *ops;
} calc_data;

typedef struct binary_operator
{
	char* op; int prec; int (*func)(calc_data*, int, double[], int, double[]);
} binary_operator;

int parse_number(char* expr);
int parse_whitespace(char* expr);
int parse_operator(int ops_size, binary_operator ops[], char *expr, int *opIndex);
void calc_read_whitespace(calc_data *data);

