#include <stdio.h>
#include "funciones.h"

int main() {
    char huespedes[5][2][40] = {{"", ""}};
    char cuartos[9][3][40] = {
        {"1", "individual", "Dan_Carlton"},
        {"2", "doble", "Dan_Carlton"},
        {"3", "triple", "Dan_Carlton"},
        {"4", "individual", "Swissotel"},
        {"5", "doble", "Swissotel"},
        {"6", "triple", "Swissotel"},
        {"7", "individual", "Sheraton"},
        {"8", "doble", "Sheraton"},
        {"9", "triple", "Sheraton"}
    };
    double tarifas[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};
    int reservas[10][4] = {
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0}
    };

    leerHuespedes(huespedes, "C:/Escritorio/huespedes.txt");
    leerReservas(reservas, "C:/Escritorio/reservas.txt");

    int opcion, numCuarto, numReserva;

    do {
        printf("\nEscoja una opción:\n1. Buscar Cuarto\n2. Hacer reserva\n3. Ver reservas\n4. Pagar Reserva\n>> ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("1. Por capacidad\n2. Por Hotel\n>> ");
                scanf("%d", &opcion);
                switch (opcion) {
                    case 1:
                        buscarPorCapacidad(&numCuarto, cuartos, tarifas);
                        break;
                    case 2:
                        buscarPorHotel(&numCuarto, cuartos, tarifas);
                        break;
                    default:
                        printf("Opción inválida.\n");
                        break;
                }
                break;
            case 2:
                hacerReserva(numCuarto, cuartos, huespedes, reservas);
                guardarHuespedes(huespedes, "huespedes.txt");
                guardarReservas(reservas, "reservas.txt");
                break;
            case 3:
                buscarReservaPorCedula(&numReserva, huespedes, reservas);
                imprimirReserva(numReserva, reservas, cuartos, tarifas, huespedes);
                break;
            case 4:
                buscarReservaPorCedula(&numReserva, huespedes, reservas);
                pagarReserva(numReserva, reservas, cuartos, tarifas);
                guardarReservas(reservas, "reservas.txt");
                break;
            default:
                printf("Opción inválida.\n");
                break;
        }
        printf("Desea elegir otra opción\n1. Sí\n2. No\n>> ");
        scanf("%d", &opcion);
    } while (opcion == 1);

    return 0;
}