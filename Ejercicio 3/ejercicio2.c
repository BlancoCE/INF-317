#include "stdio.h"

int suma(int a, int b) {
	return a+b;
}
int resta(int a, int b) {
	return a-b;
}
int multiplicacion(int a, int b){
	return a*b;
}
float division(int a, int b) {
	if(b!=0)
		return (float)a/b;
	else {
		printf("Error> Division por cero\n");
		return 0;
	}
}

int main() {
	int num1 = 10, num2 = 5;
	printf("Suma: %d\n", suma(num1,num2));
	printf("Resta: %d\n", resta(num1,num2));
	printf("Multiplicacion: %d\n", multiplicacion(num1,num2));
	printf("Division: %.2f\n", division(num1,num2));
	return 0;
}
