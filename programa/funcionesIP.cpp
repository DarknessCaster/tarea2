#include <stdio.h>
#include <string.h>
#include "ip.h"
#include "funcionesIP.h"

void encapsularIP(IP &paquete, size_t len){
    len = strlen((const char*)paquete.datos);
    paquete.datos[len-1] = (BYTE)'\0'; // Arreglo para elimminar \n al final de datos
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
    printf("IP del nodo %c: %c.%c.%c.%c\n", ip[0], ip[0], ip[1], ip[2], ip[3]);
}