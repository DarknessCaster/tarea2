#include <stdio.h>
#include <string.h>
#include "ip.h"
#include "funcionesIP.h"

void encapsularIP(IP){

}

void convertir_ip(const char* ip_str, BYTE ip_array[4]) {
    if (strlen(ip_str) == 7 && ip_str[1] == '.' && ip_str[3] == '.' && ip_str[5] == '.') {
        ip_array[0] = ip_str[0]; 
        ip_array[1] = ip_str[2]; 
        ip_array[2] = ip_str[4]; 
        ip_array[3] = ip_str[6]; 
    } else {
        printf("Formato de IP no válido.\n");
    }
}