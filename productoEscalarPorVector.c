#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int sizeVector, scalar, rank, size;
    int *vector, *result, *vectorRecvBuf;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        printf("Ingrese el tamanio del vector: ");
        scanf("%d", &sizeVector);

        printf("Ingrese el valor del escalar: ");
        scanf("%d", &scalar);
    }

    MPI_Bcast(&sizeVector, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&scalar, 1, MPI_INT, 0, MPI_COMM_WORLD);

    vector = (int*)malloc(sizeVector * sizeof(int));
    result = (int*)malloc(sizeVector * sizeof(int));
    vectorRecvBuf = (int*)malloc(sizeVector * sizeof(int));

    if(rank == 0) {
        printf("Ingrese los elementos del vector: \n");
        for(int i = 0; i < sizeVector; i++) {
            scanf("%d", &vector[i]);
        }
    }

    MPI_Scatter(vector, sizeVector/size, MPI_INT, vectorRecvBuf, sizeVector/size, MPI_INT, 0, MPI_COMM_WORLD);
        
    /* for(int i = 0; i < sizeVector/size; i++) {
        printf("Soy el proceso %d y Mi elemento %d tiene el valor: %d\n", rank, i, vectorRecvBuf[i]);
    }  */  

    for (int i = 0; i < sizeVector/size; i++) {
        vectorRecvBuf[i] *= scalar;
    } 

    MPI_Gather(vectorRecvBuf, sizeVector/size, MPI_INT, result, sizeVector/size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Vector original: [");
        for (int i = 0; i < sizeVector; i++) {
            if(i == sizeVector-1) {
                printf("%d]", vector[i]);
            } else {
                printf("%d, ", vector[i]);
            }
        }
        printf("\n");

        printf("Vector resultante: [");
        for (int i = 0; i < sizeVector; i++) {
            
            if(i == sizeVector-1) {
                printf("%d] ", result[i]);
            }else {
                printf("%d, ", result[i]);
            }
        }
        printf("\n");

    }

    free(vector);
    free(result);

    MPI_Finalize();
    return 0;

}