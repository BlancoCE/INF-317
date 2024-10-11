#include "stdio.h"

double calcular_pi_iterativo(int n) {
	double pi = 0.0;
	for (int i = 0; i < n; i++) {
		double termino = (i % 2 == 0 ? 1 : -1) / (2.0 * i + 1);
		pi += termino;
	}
	return pi * 4;
}

int main() {
	int iteraciones= 1000000;
	printf("Valor de Pi iterativo: %.15f\n", calcular_pi_iterativo(iteraciones));
	return 0;
}
