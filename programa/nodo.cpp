#include <stdio.h>
#include "serial.h"
#include "slip.h"
#include "ip.h"
#include <string.h>

#define MAX_DATA_SIZE 1500
const char* ip_A = "A.A.A.A";
const char* ip_B = "A.A.A.A";
const char* ip_C = "A.A.A.A";
const char* ip_D = "A.A.A.A";
const char* ip_E = "A.A.A.A";

int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        int opcion = 0;
        struct IP paquete;
        char msg[MAX_DATA_SIZE];

        const char* ip_nodo = arg_arr[1];
        const char* puerto_tx = arg_arr[2];
        const char* puerto_rx = arg_arr[3];

        FILE *rx_stream = fopen(puerto_rx, "r");
        FILE *tx_stream = fopen(puerto_tx, "w");

        if(strcmp(ip_nodo, "A.A.A.A") == 0){
            printf("Nodo A iniciado correctamente\n");
            printf("========= MENU =========");
        }
        printf("Ingrese el mensaje a enviar ");
        do {
            printf("\n================== MENU ==================\n");
            printf("1. Enviar mensaje de prueba\n");
            printf("2. Enviar mensaje de texto\n");
            printf("3. Buscar archivo txt\n");
            printf("4. Ver cantidad de mensajes enviados\n");
            printf("5. Listar archivos de texto del receptor\n");
            printf("6. Crear archivo y registrar un mensaje\n"); //  *** PUNTAJES EXTRAS: 2.
            printf("7. Cerrar programa receptor\n");
            printf("==============================================\n");
            printf("Ingrese la opcion deseada: ");
            scanf("%d", &opcion);
            getchar(); 
            switch (opcion) {
                case 1:
                    printf("Hola mundo");
                    break;
                default:
                    break;
            }
        } while (opcion != 7);
    } else{
        printf("Utilizar: ");
    }
    return 0;
    }