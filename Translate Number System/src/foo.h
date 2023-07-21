
#ifndef FOO_H
#define FOO_H

#include <stdio.h>

#define NMAX 13
#define IMAX 100

int input(int* b1, int* b2);
void input_number(int* dot, int* size_int, int* size_float, char* number);
int check_number(int b1, int* dot, int* size_int, int* size_float,
                 char* number);
double to_value_number_in_ten(char* number, int dot, int size_int,
                              int size_float, int b1);
void to_value_number_in_b2(double* ten, int dot, int b2);
int range(int j, int b1, char* number);
void output_int(double* ten, long long* output, int b2, int* flag_integer);
void output_float(int dot, int flag_integer, double* ten, long long* output,
                  int b2);

#endif
