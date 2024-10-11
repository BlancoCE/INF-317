#include "stdio.h"
#include "mpi.h"

#define N 10

int main(int argc, char** argv) {
    int procesador, size, i;
    int vec1[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int vec2[N] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int resul[N] = {0};
    int local_resul[N] = {0};  

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size != 3) {
        if (procesador == 0) {
            printf("Este programa requiere exactamente 3 procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }
    
    if (procesador == 0) {
        MPI_Recv(local_resul, N / 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Guardamos resultados(pares)
        for (i = 0; i < N / 2; i++) {
            resul[i * 2] = local_resul[i];
        }

        MPI_Recv(local_resul, N / 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Guardamos resultados (impares)
        for (i = 0; i < N / 2; i++) {
            resul[i * 2 + 1] = local_resul[i]; 
        }
        
        printf("Vector resultado (sumado):");
        for (i = 0; i < N; i++) {
            printf(" %d", resul[i]);
        }
        printf("\n");
    } else if (procesador == 1) {
        // Procesador 1: suma elementos en posiciones pares
        for (i = 0; i < N; i += 2) {
            local_resul[i / 2] = vec1[i] + vec2[i];
        }
        MPI_Send(local_resul, N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (procesador == 2) {
        // Procesador 2: suma elementos en posiciones impares
        for (i = 1; i < N; i += 2) {
            local_resul[i / 2] = vec1[i] + vec2[i];  
        }
        MPI_Send(local_resul, N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
