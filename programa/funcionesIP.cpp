#include <stdio.h>
#include <string.h>
#include "ip.h"
#include "funcionesIP.h"

#define MAX_DATA_SIZE 1500

int encapsularIP(IP &paquete, BYTE TTL, int id, const char* ip_origen, const char* ip_destino){
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
    convertir_ip(ip_origen, paquete.ip_origen); // Almacena ip de origen
    convertir_ip(ip_destino, paquete.ip_destino); // Almacena ip de destino

    // Empaqueta Longitud de los datos (16 bits)
    // Al  usar indice++ primero asigna y luego suma 1 a la variable indice.
    int indice = 0;
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