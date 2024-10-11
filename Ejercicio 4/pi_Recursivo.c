
#include "stdio.h"

double calcular_pi_recursivo(int i, int n, double pi) {
	if (i >= n) {
		return pi * 4;
	}
	double termino = (i % 2 == 0 ? 1 : -1) / (2.0 * i + 1);
	return calcular_pi_recursivo(i + 1, n, pi + termino);
}

int main() {
	int iteraciones = 100000;
	printf("Valor de Pi recursivo: %.15f\n", calcular_pi_recursivo(0, iteraciones, 0.0));
	return 0;
}
