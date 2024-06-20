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

        char* ip_nodo = arg_arr[1];
        char* puerto_tx = arg_arr[2];
        char* puerto_rx = arg_arr[3];

        printf("IP del nodo: %s\n", ip_nodo);
        
        FILE *vport_rx = fopen(puerto_rx, "r");
        FILE *vport_tx = fopen(puerto_tx, "w");

        if(strcmp(ip_nodo, ip_A) == 0){
            printf("Nodo A iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. B\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
        }
        else if(strcmp(ip_nodo, ip_B) == 0){
            printf("Nodo B iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
        }
        else if(strcmp(ip_nodo, ip_C) == 0){
            printf("Nodo C iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. B\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
        }
        else if(strcmp(ip_nodo, ip_D) == 0){
            printf("Nodo D iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. B\n3. C\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
        }
        else if(strcmp(ip_nodo, ip_E) == 0){
            printf("Nodo E iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. B\n3. C\n4. D\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            
        }
    } else{
        printf("Utilizar:\n");
    }
    return 0;
}