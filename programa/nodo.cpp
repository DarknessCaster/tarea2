#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "serial.h"
#include "slip.h"
#include "ip.h"
#include "funcionesIP.h"

#define MAX_DATA_SIZE 1500
BYTE ips[6][4] = {
    {0xA, 0xA, 0xA, 0xA},  // ip_A
    {0xB, 0xB, 0xB, 0xB},  // ip_B
    {0xC, 0xC, 0xC, 0xC},  // ip_C
    {0xD, 0xD, 0xD, 0xD},  // ip_D
    {0xE, 0xE, 0xE, 0xE},  // ip_E
    {0xF, 0xF, 0xF, 0xF}   // ip_Broadcast
};

int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        int opcion = 0;
        BYTE ip_Nodo[4];
        // Obtener ip del nodo y sus respectivos puertos.
        char* ip_nodo = arg_arr[1]; 
        char* puerto_tx = arg_arr[2];
        char* puerto_rx = arg_arr[3];
        // Abrir puertos tx y rx
        FILE *vport_tx = fopen(puerto_tx, "w");
        FILE *vport_rx = fopen(puerto_rx, "r");
        // Otra forma de implementar ips.
        convertir_ip(ip_nodo, ip_Nodo);
        printf("Nodo %X iniciado correctamente\n", ip_Nodo[0]);
        printf("Bienvenido al programa nodo\nQue accion desea hacer con el nodo?\n");
        printf("1. Enviar mensaje\n2. Recibir mensaje\n3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        if(opcion == 1){
            //ejecutar emisor
            if(memcmp(ips[0], ip_Nodo, 4) == 0){
                menu_enviar(vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[1], ip_Nodo, 4) == 0){
                menu_enviar(vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[2], ip_Nodo, 4) == 0){
                menu_enviar(vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[3], ip_Nodo, 4) == 0){
                menu_enviar(vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[4], ip_Nodo, 4) == 0){
                menu_enviar(vport_tx, ip_Nodo, ips);
            }
            }
        else if(opcion == 2){
            //ejecutar receptor
            if(memcmp(ips[0], ip_Nodo, 4) == 0){
                menu_recibir(vport_tx, vport_rx, ip_Nodo, ips);
            }
            else if(memcmp(ips[1], ip_Nodo, 4) == 0){
                menu_recibir(vport_tx, vport_rx, ip_Nodo, ips);
            }
            else if(memcmp(ips[2], ip_Nodo, 4) == 0){
                menu_recibir(vport_tx, vport_rx, ip_Nodo, ips);
            }
            else if(memcmp(ips[3], ip_Nodo, 4) == 0){
                menu_recibir(vport_tx, vport_rx, ip_Nodo, ips);
            }
            else if(memcmp(ips[4], ip_Nodo, 4) == 0){
                menu_recibir(vport_tx, vport_rx, ip_Nodo, ips);
            }
        else if (opcion == 3) {
            // Salir del programa
            printf("Programa finalizado correctamente.\n");
            break;
        }
        else {
            printf("Opción no válida. Por favor ingrese 1, 2 o 3.\n");
            
        }
        fclose(vport_tx);
        fclose(vport_rx);
    } else{
        printf("--------------------MANUAL DE USUARIO--------------------\n");
        printf("---------------------------------------------------------\n");
        printf("Para ejecutar el programa debe inicializar el nodo con su\nrespectiva letra usando el comando:\n\n");
        printf("\t make run_nodo_(Letra del nodo)\n\n");
        printf("Ejemplos:\n\n");
        printf("\t Nodo A:\t make run_nodo_A\n");
        printf("\t Nodo B:\t make run_nodo_B\n");
        printf("\t Nodo C:\t make run_nodo_C\n");
        printf("\t Nodo D:\t make run_nodo_D\n");
        printf("\t Nodo E:\t make run_nodo_E\n\n");
        printf("Descripción del Programa:\n");
        printf("-------------------------\n");
        printf("Este programa simula una red de nodos interconectados en un anillo. Cada nodo puede enviar o recibir\n");
        printf("mensajes a otros nodos a través de un protocolo IP modificado. Los mensajes pueden ser unicast (a un\nsolo nodo)");
        printf("o broadcast (a todos los nodos).\n\n");
    }
    return 0;
}