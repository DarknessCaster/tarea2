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
BYTE ip_a[4] = {0xA, 0xA, 0xA, 0xA};
BYTE ip_b[4] = {0xB, 0xB, 0xB, 0xB};
BYTE ip_c[4] = {0xC, 0xC, 0xC, 0xC};
BYTE ip_d[4] = {0xD, 0xD, 0xD, 0xD};
BYTE ip_e[4] = {0xF, 0xF, 0xF, 0xF};
BYTE ip_broadcast[4] = {0xF, 0xF, 0xF, 0xF};


int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        int opcion = 0;
        int opcion_2 = 0;
        IP paquete; // Se inicializa paquete con protocolo IP modificado
        BYTE ip_Nodo[4];
        //char msg[MAX_DATA_SIZE];
        int contador_id = 0;
        short largo;
        int lng_frame;
        // Obtener ip del nodo y sus respectivos puertos.
        char* ip_nodo = arg_arr[1]; 
        char* puerto_tx = arg_arr[2];
        char* puerto_rx = arg_arr[3];
        // Abrir puertos tx y rx
        FILE *vport_tx = fopen(puerto_tx, "w");
        FILE *vport_rx = fopen(puerto_rx, "r");
        // Otra forma de implementar ips.
        convertir_ip(ip_nodo, ip_Nodo);
        printf("Nodo %c iniciado correctamente\n", ip_Nodo[0]);
        printf("Bienvenido al programa nodo\nQue accion desea hacer con el nodo?\n");
        printf("1. Enviar mensaje\n2. Recibir mensaje\n3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion_2);
        if(opcion_2 == 1){
            //ejecutar emisor
            if(memcmp(ip_a, ip_Nodo, 4) == 0){
                printf("Nodo A iniciado correctamente\n");
                printf("A quien desea enviar el mensaje?\n");
                printf("1. B\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &opcion);
                getchar();
                switch (opcion) {
                    case 1: // NODO B
                        while(true){
                            // Encapsula en la trama FRAMES y ademas se guarda el largo de este en lng_frame
                            lng_frame = encapsularIP(paquete, 1, contador_id, ip_nodo, ip_B);
                            contador_id++;
                            writeSlip(paquete.FRAMES, lng_frame, vport_tx);// ENVIAR POR SLIP
                        }
                        break;
                    case 2: // NODO C
                        while(true){
                            // Encapsula en la trama FRAMES y ademas se guarda el largo de este en lng_frame
                            lng_frame = encapsularIP(paquete, 2, contador_id, ip_nodo, ip_C);
                            contador_id++;
                            // LUEGO DE ENCAPSULAR, ENVIAR POR SLIP
                            writeSlip(paquete.FRAMES, lng_frame, vport_tx);
                        }
                        break;
                    case 3: // NODO D
                        encapsularIP(paquete, 3, contador_id, ip_nodo, ip_D);
                        break;
                    case 4: // NODO E
                        encapsularIP(paquete, 4, contador_id, ip_nodo, ip_E);
                        break;
                    case 5: // BROADCAST
                        encapsularIP(paquete, 5, contador_id, ip_nodo, ip_Broadcast);
                        break;
                    default:
                        return 1;
                }
            }
            else if(strcmp(ip_nodo, ip_B) == 0){
                printf("\nNodo B iniciado correctamente\n");
                printf("A quien desea enviar el mensaje?\n");
                printf("1. A\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &opcion);
                getchar();
                switch (opcion) {
                    case 1: // NODO A
                        encapsularIP(paquete, 4, contador_id, ip_nodo, ip_A);
                        printf("Ip origen: ");
                        imprimir_ip(paquete.ip_origen);
                        printf("Ip destino: ");
                        imprimir_ip(paquete.ip_destino);
                        printf("ID: %d\n", paquete.id);
                        printf("TTL: %d\n", paquete.TTL);
                        printf("Longitud de datos: %d\n", (paquete.lng_datos[0] << 8) | paquete.lng_datos[1]);
                        contador_id++;
                        break;
                    case 2: // NODO C
                        encapsularIP(paquete, 1, contador_id, ip_nodo, ip_C);
                        break;
                    case 3: // NODO D
                        encapsularIP(paquete, 2, contador_id, ip_nodo, ip_D);
                        break;
                    case 4: // NODO E
                        encapsularIP(paquete, 3, contador_id, ip_nodo, ip_E);
                        break;
                    case 5: // BROADCAST
                        encapsularIP(paquete, 5, contador_id, ip_nodo, ip_Broadcast);
                        break;
                    default:
                        return 1;
                }
            }
            else if(strcmp(ip_nodo, ip_C) == 0){
                printf("\nNodo C iniciado correctamente\n");
                printf("A quien desea enviar el mensaje?\n");
                printf("1. A\n2. B\n3. D\n4. E\n5. A todos (broadcast)\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &opcion);
            }
            else if(strcmp(ip_nodo, ip_D) == 0){
                printf("\nNodo D iniciado correctamente\n");
                printf("A quien desea enviar el mensaje?\n");
                printf("1. A\n2. B\n3. C\n4. E\n5. A todos (broadcast)\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &opcion);
            }
            else if(strcmp(ip_nodo, ip_E) == 0){
                printf("\nNodo E iniciado correctamente\n");
                printf("A quien desea enviar el mensaje?\n");
                printf("1. A\n2. B\n3. C\n4. D\n5. A todos (broadcast)\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &opcion);

            }
            }
        else if(opcion_2 == 2){
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
                        largo = (paquete.lng_datos[0] | (paquete.lng_datos[1] << 8));
                        printf("Largo ip: %hd   Largo slip: %d\n", largo, len_rx);
                        if (memcmp(paquete_rx.ip_destino, ip_Nodo, 4) == 0) {
                            printf("Se recibio un mensaje tipo unicast:\n%s\n", paquete_rx.datos);
                        }
                        else if (memcmp(paquete_rx.ip_destino, ip_Nodo, 4) == 0){

                        }
                        else{
                            paquete_rx.TTL--;
                            writeSlip(paquete_rx.FRAMES, len_rx, vport_tx);// ENVIAR POR SLIP
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