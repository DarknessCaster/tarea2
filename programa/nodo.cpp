#include <stdio.h>
#include "serial.h"
#include "slip.h"
#include "ip.h"
#include <string.h>

#define MAX_DATA_SIZE 1500
const char* ip_A = "A.A.A.A";
const char* ip_B = "B.B.B.B";
const char* ip_C = "C.C.C.C";
const char* ip_D = "D.D.D.D";
const char* ip_E = "E.E.E.E";

int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        int opcion = 0;
        struct IP paquete;
        char msg[MAX_DATA_SIZE];

        const char* ip_nodo = arg_arr[1];
        const char* puerto_tx = arg_arr[2];
        const char* puerto_rx = arg_arr[3];
        printf("%s", ip_nodo);
        FILE *rx_stream = fopen(puerto_rx, "r");
        FILE *tx_stream = fopen(puerto_tx, "w");

        if(strcmp(ip_nodo, ip_A) == 0){
            printf("Nodo A iniciado correctamente\n");
            printf("========= MENU =========");
        }
    } else{
        printf("Utilizar: ");
    }
    return 0;
    }