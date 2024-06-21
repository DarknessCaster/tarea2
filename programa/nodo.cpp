#include <stdio.h>
#include "serial.h"
#include "slip.h"
#include "ip.h"
#include "funcionesIP.h"
#include <string.h>

#define MAX_DATA_SIZE 1500
const char* ip_A = "A.A.A.A";
const char* ip_B = "B.B.B.B";
const char* ip_C = "C.C.C.C";
const char* ip_D = "D.D.D.D";
const char* ip_E = "E.E.E.E";
const char* ip_broadcast = "F.F.F.F";

int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        char opcion;
        struct IP paquete;
        char msg[MAX_DATA_SIZE];

        char* ip_nodo = arg_arr[1];
        char* puerto_tx = arg_arr[2];
        char* puerto_rx = arg_arr[3];
        
        FILE *vport_rx = fopen(puerto_rx, "r");
        FILE *vport_tx = fopen(puerto_tx, "w");
        printf("Ingrese opcion: \n");
        scanf(" %c", &opcion);
        printf("%c", opcion);
        getchar();
        if(strcmp(ip_nodo, ip_A) == 0){
            convertir_ip(ip_A, paquete.ip_origen);
            imprimir_ip(paquete.ip_origen);
            printf("\nNodo A iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. B\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");

            scanf(" %c", &opcion);
            printf("%c", opcion);
            // switch (opcion_1) {
            //     case '1':
            //         convertir_ip(ip_B, paquete.ip_destino);
            //         imprimir_ip(paquete.ip_destino);
            //         break;
            //     case 2:
            //         //paquete.ip_destino = ip_C;
            //         break;
            //     case 3:
            //         //paquete.ip_destino = ip_D;
            //         break;
            //     case 4:
            //         //paquete.ip_destino = ip_E;
            //         break;
            //     case 5:
            //         //paquete.ip_destino = ip_broadcast;
            //         break;
            //     default:
            //         return 1;
            // }
        }
        else if(strcmp(ip_nodo, ip_B) == 0){
            convertir_ip(ip_B, paquete.ip_origen);
            imprimir_ip(paquete.ip_origen);
            printf("\nNodo B iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            opcion = getchar();
            if(opcion == '1'){
                convertir_ip(ip_A, paquete.ip_destino);
                imprimir_ip(paquete.ip_destino);
            }
            else if(opcion == '2'){

            }
        }
        else if(strcmp(ip_nodo, ip_C) == 0){
            printf("\nNodo C iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. B\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%c", &opcion);
        }
        else if(strcmp(ip_nodo, ip_D) == 0){
            printf("\nNodo D iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. B\n3. C\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%c", &opcion);
        }
        else if(strcmp(ip_nodo, ip_E) == 0){
            printf("\nNodo E iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. B\n3. C\n4. D\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%c", &opcion);
            
        }
        fclose(vport_tx);
        fclose(vport_rx);
    } else{
        printf("Utilizar:\n");
    }
    return 0;
}