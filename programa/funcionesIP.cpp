#include <stdio.h>
#include <string.h>
#include "ip.h"
#include "funcionesIP.h"

#define MAX_DATA_SIZE 1500

void encapsularIP(IP &paquete, BYTE TTL, int id, const char* ip_origen, const char* ip_destino){
    size_t len;
    convertir_ip(ip_origen, paquete.ip_origen); // Almacena ip de origen
    convertir_ip(ip_destino, paquete.ip_destino); // Almacena ip de destino
    paquete.TTL = TTL; // Almacena TTL
    paquete.id = id; // Almacena Identificacion
    printf("Ingrese mensaje a enviar: ");
    fgets((char*)paquete.datos, MAX_DATA_SIZE, stdin); // Almacena mensaje
    
    // Almacena longitud de datos
    len = strlen((const char*)paquete.datos); 
        // Si el l
        if (len > 0 && paquete.datos[len - 1] == '\n') {
            paquete.datos[len - 1] = '\0';
            len--; // Disminuir la longitud
        }
        paquete.lng_datos[0] = (BYTE)(len >> 8); // Byte alto
        paquete.lng_datos[1] = (BYTE)(len & 0xFF); // Byte bajo
}

void convertir_ip(const char* ip_str, BYTE ip[4]) {
    if (strlen(ip_str) == 7 && ip_str[1] == '.' && ip_str[3] == '.' && ip_str[5] == '.') {
        ip[0] = ip_str[0]; 
        ip[1] = ip_str[2]; 
        ip[2] = ip_str[4]; 
        ip[3] = ip_str[6]; 
    } else {
        printf("Formato de IP no válido.\n");
    }
}

void imprimir_ip(BYTE ip[4]) {
    printf("%c.%c.%c.%c\n", ip[0], ip[1], ip[2], ip[3]);
}