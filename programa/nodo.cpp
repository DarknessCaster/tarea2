#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "serial.h"
#include "slip.h"
#include "ip.h"
#include "funcionesIP.h"

#define MAX_DATA_SIZE 1500
const char* ip_A = "10.10.10.10";
const char* ip_B = "11.11.11.11";
const char* ip_C = "12.12.12.12";
const char* ip_D = "13.13.13.13";
const char* ip_E = "14.14.14.14";
const char* ip_Broadcast = "15.15.15.15";
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
        IP paquete; // Se inicializa paquete con protocolo IP modificado
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
                menu_enviar(paquete, vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[1], ip_Nodo, 4) == 0){
                menu_enviar(paquete, vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[2], ip_Nodo, 4) == 0){
                menu_enviar(paquete, vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[3], ip_Nodo, 4) == 0){
                menu_enviar(paquete, vport_tx, ip_Nodo, ips);
            }
            else if(memcmp(ips[4], ip_Nodo, 4) == 0){
               menu_enviar(paquete, vport_tx, ip_Nodo, ips);
            }
            }
        else if(opcion == 2){
            //ejecutar receptor
            IP paquete_rx;
            int len_rx = 0;
            if(strcmp(ip_nodo, ip_A) == 0){
                
            }
            else if(strcmp(ip_nodo, ip_B) == 0){
                while (true) {
                    len_rx = readSlip(paquete_rx.FRAMES, MAX_DATOS_SIZE + 16, vport_rx);
                    if (len_rx > 0) { // Si detecta escritura
                        desempaquetarIP(paquete_rx); // Desempaqueta los datos IP recibidos
                        short largo = (paquete_rx.lng_datos[0] | (paquete_rx.lng_datos[1] << 8));
                        printf("Largo ip: %hd   Largo slip: %d\n", largo, len_rx);
                        paquete_rx.datos[largo] = '\0';
                        if (memcmp(paquete_rx.ip_destino, ip_Nodo, 4) == 0) {
                            printf("Se recibio un mensaje tipo unicast:\n%s\n", paquete_rx.datos);
                        }
                        else if (memcmp(paquete_rx.ip_destino, ip_Broadcast, 4) == 0){
                            // Verificar que no sea el propio nodo que envió el broadcast
                            if (memcmp(paquete_rx.ip_origen, ip_Nodo, 4) != 0) {
                                printf("Se recibio un mensaje tipo --broadcast--\n");
                                printf("Mensaje enviado por el nodo %X\n", paquete_rx.ip_origen[0]);
                                printf("%s", paquete_rx.datos);
                                paquete_rx.TTL--;
                                encapsularIP(paquete_rx, paquete_rx.TTL, paquete_rx.id, paquete_rx.ip_origen, paquete_rx.ip_destino);
                                writeSlip(paquete_rx.FRAMES, len_rx, vport_tx); // ENVIAR POR SLIP
                            } else {
                                printf("El mensaje broadcast es propio, se descarta.\n");
                            }
                        }
                    }
                
                }
            }
            else if(strcmp(ip_nodo, ip_C) == 0){
                
            }
            else if(strcmp(ip_nodo, ip_D) == 0){
                
            }
            else if(strcmp(ip_nodo, ip_E) == 0){
                
            }
        }
        fclose(vport_tx);
        fclose(vport_rx);
    } else{
        printf("Utilizar: \n");
    }
    return 0;
}