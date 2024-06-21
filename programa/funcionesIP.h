#ifndef FUNCIONESIP_H
#define FUNCIONESIP_H

void encapsularIP(IP &paquete, size_t len);
void convertir_ip(const char* ip_str, BYTE ip[4]);
void imprimir_ip(BYTE ip[4]);

#endif