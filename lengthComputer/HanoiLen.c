#include <stdio.h>

long long int f(long long int n) {
	if(n == 3) return 7;
	return f(n - 1) * 2 + 1;
}


int main() {
	printf("%lld", f(10));
}
