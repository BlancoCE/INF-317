#include "stdio.h"

void suma(int *a, int *b, int*c) {
	*c = *a + *b;
}

void resta(int *a, int *b, int *c) {
	*c = *a - *b;
}

void multiplicacion(int *a, int *b, int *c) {
	*c = *a * *b;
}

void division(int *a, int *b, float *c) {
	if (*b != 0)
		*c = (float)*a / *b;
	else {
		printf("Error: Divisi[on por cero\n");
		*c = 0;
	}
}

int main() {
	int num1 = 10, num2 = 5;
	int res;
	float resdiv;
	
	suma(&num1, &num2, &res);
	printf("Suma: %d\n",res);
	
	resta(&num1, &num2, &res);
	printf("Resta: %d\n", res);
	
	multiplicacion(&num1, &num2, &res);
	printf("Multiplicaion: %d\n",res);
	
	division(&num1, &num2, &resdiv);
	printf("Division: %.2f\n", resdiv);
	
	return 0;
}
