#include <stdio.h>
#include <string.h>
#include "ip.h"
#include "funcionesIP.h"
#include "serial.h"
#include "slip.h"

#define MAX_DATA_SIZE 1500

int encapsularIP(IP &paquete, BYTE TTL, int id, BYTE ip_origen[4], BYTE ip_destino[4]){
    // Almacena longitud de datos
    printf("Ingrese mensaje a enviar: ");
    fgets((char*)paquete.datos, MAX_DATA_SIZE, stdin); // Almacena mensaje
    size_t len;
    len = strlen((const char*)paquete.datos);
        // elimina el salto de linea al final si existe.
        if (len > 0 && paquete.datos[len - 1] == '\n') {
            paquete.datos[len - 1] = '\0';
            len--; // Disminuir la longitud
        }
    paquete.lng_datos[0] = (BYTE)(len & 0xFF); // Byte bajo
    paquete.lng_datos[1] = (BYTE)(len >> 8); // Byte alto
    paquete.TTL = TTL; // Almacena TTL
    paquete.id = id; // Almacena Identificacion
    memcpy(paquete.ip_origen, ip_origen, sizeof(paquete.ip_origen));
    memcpy(paquete.ip_destino, ip_destino, sizeof(paquete.ip_destino));
    // Al  usar indice++ primero asigna y luego suma 1 a la variable indice.
    int indice = 0;
    // Empaqueta Longitud de los datos (16 bits)
    paquete.FRAMES[indice++] = paquete.lng_datos[0]; // Byte bajo
    paquete.FRAMES[indice++] = paquete.lng_datos[1]; // Byte alto

    paquete.FRAMES[indice++] = paquete.TTL & 0xFF; // Empaqueta TTL (8 bits)

    paquete.FRAMES[indice++] = paquete.id & 0xFF; // Empaqueta Identificación (16 bits)

    // Empaqueta IP origen (32 bits)
    memcpy(&paquete.FRAMES[indice], paquete.ip_origen, 4);
    indice += 4;

    // Empaqueta IP destino (32 bits)
    memcpy(&paquete.FRAMES[indice], paquete.ip_destino, 4);
    indice += 4;

    // Calcular la suma de verificación (FCS) solo para la cabecera
    int fcs_ip = fcs(paquete.FRAMES, indice);
    paquete.FCS[0] = (BYTE)(fcs_ip & 0xFF); // Byte alto del FCS
    paquete.FCS[1] = (BYTE)(fcs_ip >> 8); // Byte bajo del FCS

    // Empaquetar suma de verificacion de cabecera
    paquete.FRAMES[indice++] = paquete.FCS[0];
    paquete.FRAMES[indice++] = paquete.FCS[1];

    memcpy(&paquete.FRAMES[indice], paquete.datos, len); // Empaquetar mensaje
    indice += len;
    return indice; // retorna largo del paquete
}

bool desempaquetarIP(IP &paquete){
    size_t indice = 0;
    paquete.lng_datos[0] = paquete.FRAMES[indice++];
    paquete.lng_datos[1] = paquete.FRAMES[indice++];
    short len = (paquete.lng_datos[0] | (paquete.lng_datos[1] << 8));
    paquete.TTL = paquete.FRAMES[indice++];
    paquete.id = paquete.FRAMES[indice++];
    memcpy(paquete.ip_origen, &paquete.FRAMES[indice], 4);
    indice += 4;
    memcpy(paquete.ip_destino, &paquete.FRAMES[indice], 4);
    indice += 4;
    paquete.FCS[0] = paquete.FRAMES[indice++];
    paquete.FCS[1] = paquete.FRAMES[indice++];
    memcpy(paquete.datos, &paquete.FRAMES[indice], len);
    return true;
}

void convertir_ip(const char* ip_str, BYTE ip[4]) {
    int octet[4];
    if (sscanf(ip_str, "%d.%d.%d.%d", &octet[0], &octet[1], &octet[2], &octet[3]) == 4) {
        for (int i = 0; i < 4; i++) {
            ip[i] = (BYTE)octet[i];
        }
    } else {
        printf("Formato de IP no válido.\n");
    }
}

void imprimir_ip(BYTE ip[4]) {
    printf("%c.%c.%c.%c\n", ip[0], ip[1], ip[2], ip[3]);
}

int fcs(BYTE * arr, int tam){
    int sum_bits = 0;
    for(int i=0; i<tam; i++){
        for(int j=0; j<8; j++){
            sum_bits += (arr[i] >> j) & 0x01;
        } 
    }
    return sum_bits;
}

void enviarIP(IP paquete, FILE *vport_tx, BYTE ip_origen[4], BYTE ip_destino[4], BYTE TTL){
    int contador_id = 0;
    int lng_frame;
    while(true){
    // Encapsula en la trama FRAMES y ademas se guarda el largo de este en lng_frame

        lng_frame = encapsularIP(paquete, TTL, contador_id, ip_origen, ip_destino);
        contador_id++;
        writeSlip(paquete.FRAMES, lng_frame, vport_tx);// ENVIAR POR SLIP
    }
}

int menu_enviar(IP &paquete, FILE *vport_tx, BYTE ip_Nodo[4], BYTE ips[6][4]){
    int opcion;
    BYTE TTL; 
    printf("Nodo %X iniciado correctamente\n", ip_Nodo[0]);
    printf("A quien desea enviar el mensaje?\n");
    printf("1. B\n2. C\n3. D\n4. E\n5. A todos (broadcast)\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    getchar();
    switch (opcion) {
        case 1: // NODO B
            TTL = 1;
            enviarIP(paquete, vport_tx, ip_Nodo, ips[1], TTL);
            break;
        case 2: // NODO C
            TTL = 2;
            enviarIP(paquete, vport_tx, ip_Nodo, ips[2], TTL);
            break;
        case 3: // NODO D
            TTL = 3;
            enviarIP(paquete, vport_tx, ip_Nodo, ips[3], TTL);
            break;
        case 4: // NODO E
            TTL = 4;
            enviarIP(paquete, vport_tx, ip_Nodo, ips[4], TTL);
            break;
        case 5: // BROADCAST
            TTL = 5;
            enviarIP(paquete, vport_tx, ip_Nodo, ips[5], TTL);
            break;
        default:
            return 1;
    }
    return 1;
}