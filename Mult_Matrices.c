#include <stdio.h>
#include <mpi.h>

#define N 3  


void imprimir_matriz(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// Función para multiplicar una fila de la primera matriz con la segunda
void multiplicar_fila(int fila[N], int mat2[N][N], int resultado[N]) {
    for (int j = 0; j < N; j++) {
        resultado[j] = 0;
        for (int k = 0; k < N; k++) {
            resultado[j] += fila[k] * mat2[k][j];
        }
    }
}

int main(int argc, char** argv) {
    int procesador, size, i;
    int mat1[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int mat2[N][N] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int resultado[N][N]; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (procesador == 0) {
        // Procesador 0: Distribuye las filas de mat1 a los demás procesadores
        for (i = 1; i < size && i-1 < N; i++) {
            MPI_Send(mat1[i-1], N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Recibe los resultados de los procesadores
        for (i = 1; i < size && i-1 < N; i++) {
            MPI_Recv(resultado[i-1], N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Resultado de la multiplicación de matrices:\n");
        imprimir_matriz(resultado);

    } else if (procesador > 0 && procesador < size) {
        int fila[N], res[N];
        MPI_Recv(fila, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        multiplicar_fila(fila, mat2, res);
        MPI_Send(res, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
