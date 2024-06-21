#include <stdio.h>
#include <string.h>
#include "serial.h"
#include "slip.h"
#include "ip.h"
#include "funcionesIP.h"

#define MAX_DATA_SIZE 1500
const char* ip_A = "A.A.A.A";
const char* ip_B = "B.B.B.B";
const char* ip_C = "C.C.C.C";
const char* ip_D = "D.D.D.D";
const char* ip_E = "E.E.E.E";
const char* ip_broadcast = "F.F.F.F";

int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        int opcion = 0;
        struct IP paquete; // Se inicializa paquete con protocolo IP modificado
        char msg[MAX_DATA_SIZE];
        int contador_id = 0;
        size_t len; // Longitud de mensaje ingresado
        // Obtener ip del nodo y puertos tx, rx
        char* ip_nodo = arg_arr[1]; 
        char* puerto_tx = arg_arr[2];
        char* puerto_rx = arg_arr[3];

        // 
        FILE *vport_rx = fopen(puerto_rx, "r");
        FILE *vport_tx = fopen(puerto_tx, "w");

        // Otra forma de implementar ips.
        BYTE ipprueba[4] = {0x42, 0x42, 0x42, 0x42};
        printf("%c hexa: %x", ip_nodo[0], ip_nodo[0]);
        printf("Ip prueba, ");
        imprimir_ip(ipprueba);

        if(strcmp(ip_nodo, ip_A) == 0){
            convertir_ip(ip_A, paquete.ip_origen); // se guarda ip de origen
            imprimir_ip(paquete.ip_origen);
            printf("%x\n", paquete.ip_origen[0]);
            printf("Nodo A iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. B\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            getchar();
            switch (opcion) {
                case 1: // NODO B
                    convertir_ip(ip_B, paquete.ip_destino); // se guarda ip de destino
                    printf("Ip destino: ");
                    imprimir_ip(paquete.ip_destino);
                    paquete.TTL = 1; // se guarda TTL
                    printf("TTL: %d\n", paquete.TTL);
                    printf("Ingrese mensaje a enviar: ");
                    fgets((char*)paquete.datos, MAX_DATA_SIZE, stdin); // se guarda mensaje o datos
                    
                    // se guarda longitud de datos
                    len = strlen((const char*)paquete.datos);
                    paquete.datos[len-1] = "\0"; // Arreglo para elimminar \n al final de datos
                    paquete.lng_datos[0] = (BYTE)(len >> 8); // Byte alto
                    paquete.lng_datos[1] = (BYTE)(len & 0xFF); // Byte bajo
                    printf("Longitud de datos: %d\n", (paquete.lng_datos[0] << 8) | paquete.lng_datos[1]);

                    paquete.id = contador_id; // se guarda identificacion de paquete
                    printf("ID: %d\n", paquete.id);
                    contador_id++;
                    printf("");
                    break;
                case 2: // NODO C
                    convertir_ip(ip_C, paquete.ip_destino);
                    break;
                case 3: // NODO D
                    convertir_ip(ip_D, paquete.ip_destino);
                    break;
                case 4: // NODO E
                    convertir_ip(ip_E, paquete.ip_destino);
                    break;
                case 5: // BROADCAST
                    convertir_ip(ip_broadcast, paquete.ip_destino);
                    break;
                default:
                    return 1;
            }
        }
        else if(strcmp(ip_nodo, ip_B) == 0){
            convertir_ip(ip_B, paquete.ip_origen);
            imprimir_ip(paquete.ip_origen);
            printf("\nNodo B iniciado correctamente\n");
            printf("A quien desea enviar el mensaje?\n");
            printf("1. A\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            if(opcion == 1){
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
        fclose(vport_tx);
        fclose(vport_rx);
    } else{
        printf("Utilizar:\n");
    }
    return 0;
}