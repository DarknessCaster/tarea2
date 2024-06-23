#ifndef FUNCIONESIP_H
#define FUNCIONESIP_H

int encapsularIP(IP &paquete, BYTE TTL, int id, const char* ip_origen, const char* ip_destino);
void convertir_ip(const char* ip_str, BYTE ip[4]);
void imprimir_ip(BYTE ip[4]);
bool desempaquetarIP(IP &paquete);
int fcs(BYTE * arr, int tam);

#endif