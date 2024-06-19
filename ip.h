#ifndef IP_H
#define IP_H

#include <stdio.h>
#define BYTE unsigned char

// Definimos la estructura que representa el protocolo IPv4 modificado
struct ipv4_modificado {
    BYTE flag_fragmento;       // 8 bits para el flag de fragmento
    BYTE offset_fragmento;     // 8 bits para el offset de fragmento
    BYTE ttl;                  // 8 bits para TTL
    BYTE identificacion;      // 16 bits para identificación
    BYTE longitud_datos;      // 16 bits para longitud de los datos
    BYTE suma_verificacion;   // 16 bits para la suma de verificación
    BYTE ip_origen;           // 32 bits para la IP de origen
    BYTE ip_destino;          // 32 bits para la IP de destino
    BYTE datos[];              // Arreglo de datos (tamaño variable)
};
#endif