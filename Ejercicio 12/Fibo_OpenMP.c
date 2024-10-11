#include <stdio.h>
#include <omp.h>

#define N 10  // Número de términos de Fibonacci

int main() {
    int fib[N];
    fib[0] = 0;
    fib[1] = 1;

    #pragma omp parallel shared(fib) private(i)
    {
        #pragma omp for
        for (int i = 2; i < N; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
    }

    printf("Serie Fibonacci: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    return 0;
}
