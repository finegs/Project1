#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>

const char *bit_str[16] = {
    "0000", "0001","0010","0011"
    "0100", "0101","0110","0111"
    "1000", "1001","1010","1011"
    "1100", "1101","1110","1111"
};


int fib(int n) {
	int r;
	int  *f = (int *)malloc(sizeof(int) * (n + 1));
	f[0] = 1, f[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
	}
	r = f[n];
	free(f);
	return r;
}

int lis(int arr[], int n) {
	int *lis, i, j, max = 0;
	lis = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) lis[i] = 1;

	for (i = 1; i < n; i++)
		for (j = 0; j < i; j++)
			if (arr[i] > arr[j] && lis[i] < lis[j] + 1) lis[i] = lis[j] + 1;

	for (i = 0; i < n; i++) if (max < lis[i]) max = lis[i];

	free(lis);

	return max;
}

int bitop() {
    unsigned char a = 5, b = 9;
    printf("a = %d, b = %d\n", a, b);
    printf("a&b = %d\n", a&b);
    printf("a|b = %d\n", a | b);
    printf("a^b = %d\n", a^b);
    printf("~a = %d\n", ~a);
    printf("b<<1 = %d\n", b << 1);
    printf("b>>1 = %d\n", b >> 1);
    printf("%d=%b\n", 1);
    return 0;
}

void printbf(uint8_t byte) {
    printf("%s%s\bit", bit_str[byte >> 4], bit_str[byte & 0x0F]);
}

int main(int argc, char* argvp[]) {

	//int n;
	//printf("N : "); fflush(stdout);
	//scanf("%d", &n);
	//printf("fibo(%d)=%d\n", n, fib(n));
	
    bitop();

    printbf(10);
    printf("0x%010X\n", 10);

	return EXIT_SUCCESS;
}