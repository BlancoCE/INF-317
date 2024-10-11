#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define N 6  

int main(int argc, char** argv) {
    int procesador, i;
    char *cadenas[N] = {"Hola", "mundo", "esto", "es", "INF", "317"};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);

    if (procesador == 0) {
        // Procesador 0: Envía las cadenas a los procesadores 1 y 2
        MPI_Send(cadenas, N, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(cadenas, N, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    } else if (procesador == 1) {
        printf("Procesador 1 (pares):\n");
        for (i = 0; i < N; i += 2) {
            printf("%s\n", cadenas[i]);
        }
    } else if (procesador == 2) {
        printf("Procesador 2 (impares):\n");
        for (i = 1; i < N; i += 2) {
            printf("%s\n", cadenas[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
