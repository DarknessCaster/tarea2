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
        char msg[1000];
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
        }
        fclose(vport_tx);
        fclose(vport_rx);
    } else{
        printf("Utilizar: \n");
    }
    return 0;
}