#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorCapacidad(int *numCuarto, char cuartos[][3][40], double tarifas[]) {
    char capacidad[40];
    printf("Ingrese la capacidad de cuarto que desea buscar: ");
    scanf("%s", capacidad);
    printf("#\t\tCapacidad\t\tHotel\t\tTarifa\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(cuartos[i][1], capacidad) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", cuartos[i][0], cuartos[i][1], cuartos[i][2], tarifas[i]);
        }
    }
    printf("Elija el cuarto que desea reservar: ");
    scanf("%d", numCuarto);
}

void buscarPorHotel(int *numCuarto, char cuartos[][3][40], double tarifas[]) {
    char hotel[40];
    printf("Ingrese el nombre del hotel que desea buscar: ");
    scanf("%s", hotel);
    printf("#\t\tCapacidad\t\tHotel\t\tTarifa\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(cuartos[i][2], hotel) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", cuartos[i][0], cuartos[i][1], cuartos[i][2], tarifas[i]);
        }
    }
    printf("Elija el cuarto que desea reservar: ");
    scanf("%d", numCuarto);
}

void hacerReserva(int numCuarto, char cuartos[][3][40], char huespedes[][2][40], int reservas[][4]) {
    int nuevoHuesped = -1;
    for (int i = 0; i < 5; i++) {
        if (huespedes[i][0][0] == '\0') {
            nuevoHuesped = i;
            break;
        }
    }
    if (nuevoHuesped == -1) {
        printf("No hay espacio para más huéspedes.\n");
        return;
    }

    if (reservas[numCuarto - 1][1] != -1) {
        printf("El cuarto %d ya está reservado.\n", numCuarto);
        return;
    }

    printf("Ingrese el nombre del huésped: ");
    scanf("%s", huespedes[nuevoHuesped][0]);
    printf("Ingrese la cédula del huésped: ");
    scanf("%s", huespedes[nuevoHuesped][1]);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = nuevoHuesped;
            reservas[i][1] = numCuarto - 1;
            reservas[i][2] = 0;
            reservas[i][3] = 0;
            printf("Reserva realizada correctamente.\n");
            return;
        }
    }

    printf("No hay espacio para más reservas.\n");
}

void buscarReservaPorCedula(int *numReserva, char huespedes[][2][40], int reservas[][4]) {
    char cedula[40];
    printf("Ingrese la cédula para buscar la reserva: ");
    scanf("%s", cedula);
    for (int i = 0; i < 10; i++) {
        if ((reservas[i][0] != -1) && (strcmp(huespedes[reservas[i][0]][1], cedula) == 0)) {
            *numReserva = i;
            return;
        }
    }
    *numReserva = -1;
}

void imprimirReserva(int numReserva, int reservas[][4], char cuartos[][3][40], double tarifas[], char huespedes[][2][40]) {
    if (numReserva != -1) {
        int indiceHuesped = reservas[numReserva][0];
        int indiceCuarto = reservas[numReserva][1];
        char *nombreHuesped = huespedes[indiceHuesped][0];
        printf("Reserva %d: Huésped %s en Cuarto %s (%s) de %s con tarifa %.2lf\n",
               numReserva + 1, nombreHuesped, cuartos[indiceCuarto][0], cuartos[indiceCuarto][1],
               cuartos[indiceCuarto][2], tarifas[indiceCuarto]);
        if (reservas[numReserva][3] == 1) {
            printf("Estado: Pagada\n");
        } else {
            printf("Estado: No Pagada\n");
        }
    } else {
        printf("Reserva no encontrada.\n");
    }
}

void pagarReserva(int numReserva, int reservas[][4], char cuartos[][3][40], double tarifas[]) {
    if (numReserva != -1) {
        if (reservas[numReserva][3] == 1) {
            printf("La reserva ya está pagada.\n");
        } else {
            reservas[numReserva][3] = 1;
            printf("Reserva %d pagada.\n", numReserva + 1);
            guardarReservas(reservas, "C:/Escritorio/reservas.txt");
        }
    } else {
        printf("Reserva no encontrada.\n");
    }
}

void leerHuespedes(char huespedes[][2][40], const char *filename) {
    FILE *file = fopen("C:/Escritorio/huespedes.txt", "r");

    for (int i = 0; i < 5; i++) {
        if (fscanf(file, "%s %s", huespedes[i][0], huespedes[i][1]) != 2) {
            break;
        }
    }
    fclose(file);
}

void leerReservas(int reservas[][4], const char *filename) {
    FILE *file = fopen("C:/Escritorio/reservas.txt", "r");

    for (int i = 0; i < 10; i++) {
        if (fscanf(file, "%d %d %d %d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]) != 4) {
            break;
        }
    }

    fclose(file);
}

void guardarHuespedes(char huespedes[][2][40], const char *filename) {
    FILE *file = fopen("C:/Escritorio/huespedes.txt", "a+");

    for (int i = 0; i < 5; i++) {
        if (huespedes[i][0][0] != '\0') {
            fprintf(file, "%s %s\n", huespedes[i][0], huespedes[i][1]);
        }
    }
    fclose(file);
}

void guardarReservas(int reservas[][4], const char *filename) {
    FILE *file = fopen("C:/Escritorio/reservas.txt", "a+");

    for (int i = 0; i < 10; i++) {
        fprintf(file, "%d %d %d %d\n", reservas[i][0], reservas[i][1], reservas[i][2], reservas[i][3]);
    }
    fclose(file);
}