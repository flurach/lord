#include <stdio.h>

extern int test_add_sub();
extern int test_mul_div_mod();
extern int test_mul_div_mod_2();
extern int test_all();

int main()
{
	printf("test_add_sub = %d\n", test_add_sub());
	printf("test_mul_div_mod = %d\n", test_mul_div_mod());
	printf("test_mul_div_mod_2 = %d\n", test_mul_div_mod_2());
	printf("test_all = %d\n", test_all());
}
