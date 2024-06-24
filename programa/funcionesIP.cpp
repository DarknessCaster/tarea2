#include <stdio.h>
#include <string.h>
#include "ip.h"
#include "funcionesIP.h"
#include "serial.h"
#include "slip.h"

#define MAX_DATA_SIZE 1500

/*  Nombre de la función: encapsularIP
 *  Tipo de función: int
 *  Parámetros: IP &paquete, BYTE TTL, int id, BYTE ip_origen[4], BYTE ip_destino[4].
 *  Descripción de la función: Esta función empaqueta los datos de la estructura IP en el formato adecuado para la transmisión.
 *                             Calcula la longitud de los datos, elimina cualquier salto de línea final, y llena los campos del
 *                             paquete con los valores proporcionados (TTL, id, IP de origen y destino). Además, calcula la suma
 *                             de verificación (FCS) y la incluye en el paquete. Finalmente, retorna la longitud total del paquete.
 */
int encapsularIP(IP &paquete, BYTE TTL, int id, BYTE ip_origen[4], BYTE ip_destino[4]){
    // Almacena longitud de datos
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
    memcpy(paquete.ip_origen, ip_origen, 4);
    memcpy(paquete.ip_destino, ip_destino, 4);
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

/*  Nombre de la función: desempaquetarIP
 *  Tipo de función: bool
 *  Parámetros: IP &paquete
 *  Descripción de la función: Esta función desempaqueta los datos de la estructura IP.
 *                             Extrae los campos de longitud de datos, TTL, ID, direcciones IP de origen y destino, y FCS del campo FRAMES.
 *                             Luego copia los datos del paquete en el campo correspondiente.
 *                             Retorna true indicando que la operación fue exitosa.
 */
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

/*  Nombre de la función: convertir_ip
 *  Tipo de función: void
 *  Parámetros: const char* ip_str, BYTE ip[4].
 *  Descripción de la función: Esta función convierte una dirección IP en formato de cadena (por ejemplo, "192.168.1.1")
 *                             a un arreglo de 4 bytes. Si la conversión es exitosa, los octetos de la IP se almacenan
 *                             en el arreglo ip. Si el formato de la cadena no es válido, se muestra un mensaje de error.
 */
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

/*  Nombre de la función: imprimir_ip
 *  Tipo de función: void
 *  Parámetros: BYTE ip[4].
 *  Descripción de la función: Esta función imprime la dirección IP en el formato 
 *                             "x.x.x.x", donde x es un valor numérico correspondiente
 *                             a cada byte de la dirección IP.
 */
void imprimir_ip(BYTE ip[4]) {
    printf("%c.%c.%c.%c\n", ip[0], ip[1], ip[2], ip[3]);
}

/*  Nombre de la función: fcs
 *  Tipo de función: int
 *  Parámetros: BYTE *arr, int tam.
 *  Descripción de la función: Esta función calcula la suma de verificación (FCS) 
 *                             de un arreglo de bytes. La suma de verificación se 
 *                             obtiene contando el número de bits en 1 en todo el arreglo hasta tam.
 *                             Retorna la suma total de bits en 1.
 */
int fcs(BYTE * arr, int tam){
    int sum_bits = 0;
    for(int i=0; i<tam; i++){
        for(int j=0; j<8; j++){
            sum_bits += (arr[i] >> j) & 0x01;
        } 
    }
    return sum_bits;
}

/*  Nombre de la función: enviarIP
 *  Tipo de función: void
 *  Parámetros: IP paquete, FILE *vport_tx, BYTE ip_origen[4], BYTE ip_destino[4], BYTE TTL
 *  Descripción de la función: Esta función encapsula y envía un paquete IP a través del puerto de transmisión.
 *                             La función solicita al usuario que ingrese un mensaje, lo encapsula en el paquete IP,
 *                             y lo envía utilizando la función writeSlip. La función incrementa un contador de ID para cada paquete enviado.
 */
void enviarIP(IP paquete, FILE *vport_tx, BYTE ip_origen[4], BYTE ip_destino[4], BYTE TTL){
    int contador_id = 0;
    int lng_frame;
    while(true){
    // Encapsula en la trama FRAMES y ademas se guarda el largo de este en lng_frame
        printf("Escriba un mensaje: ");
        fgets((char*)paquete.datos, MAX_DATA_SIZE, stdin); // Almacena mensaje
        lng_frame = encapsularIP(paquete, TTL, contador_id, ip_origen, ip_destino);
        contador_id++;
        writeSlip(paquete.FRAMES, lng_frame, vport_tx);// ENVIAR POR SLIP
    }
}

/*  Nombre de la función: menu_enviar
 *  Tipo de función: int
 *  Parámetros: FILE *vport_tx, BYTE ip_Nodo[4], BYTE ips[6][4].
 *  Descripción de la función: Esta función muestra un menú al usuario para seleccionar el nodo de destino al que desea enviar un mensaje.
 *                             Según la opción seleccionada, la función llama a la función enviarIP con los parámetros correspondientes,
 *                             incluyendo el TTL adecuado para cada nodo de destino.
 */
int menu_enviar(FILE *vport_tx, BYTE ip_Nodo[4], BYTE ips[6][4]){
    int opcion;
    BYTE TTL; 
    IP paquete; // Se inicializa paquete con protocolo IP modificado
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

/*  Nombre de la función: menu_recibir
 *  Tipo de función: void
 *  Parámetros: FILE *vport_tx, FILE *vport_rx, BYTE ip_Nodo[4], BYTE ips[6][4]
 *  Descripción de la función: Esta función recibe paquetes a través del puerto de recepción, desempaqueta los datos IP,
 *                             verifica el tipo de mensaje (unicast, broadcast) y actúa en consecuencia. Si es necesario,
 *                             retransmite el mensaje al siguiente nodo en la red.
 */
void menu_recibir(FILE *vport_tx, FILE *vport_rx, BYTE ip_Nodo[4], BYTE ips[6][4]){
    IP paquete_rx;
    int len_rx = 0;
    while (true) {
        len_rx = 0;
        len_rx = readSlip(paquete_rx.FRAMES, MAX_DATOS_SIZE + 20, vport_rx);
        if (len_rx > 0) { // Si detecta escritura
            desempaquetarIP(paquete_rx); // Desempaqueta los datos IP recibidos
            short largo = (paquete_rx.lng_datos[0] | (paquete_rx.lng_datos[1] << 8));
            paquete_rx.datos[largo] = '\0';
            if (memcmp(paquete_rx.ip_destino, ip_Nodo, 4) == 0) {
                printf("Se recibio un mensaje tipo unicast:\n%s\n", paquete_rx.datos);
            }
            else if (memcmp(paquete_rx.ip_destino, ips[5], 4) == 0){
                // Verificar que no sea el propio nodo que envió el broadcast
                printf("Se recibio un mensaje tipo --broadcast--\n");
                if (memcmp(paquete_rx.ip_origen, ip_Nodo, 4) != 0) {
                    printf("Mensaje enviado por el nodo %X\n", paquete_rx.ip_origen[0]);
                    printf("%s", paquete_rx.datos);
                    paquete_rx.TTL--;
                    encapsularIP(paquete_rx, paquete_rx.TTL, paquete_rx.id, paquete_rx.ip_origen, paquete_rx.ip_destino);
                    writeSlip(paquete_rx.FRAMES, len_rx, vport_tx); // ENVIAR POR SLIP
                } else {
                    printf("El mensaje broadcast es propio, se descarta.\n");
                }
            }
            else{
                paquete_rx.TTL--;
                encapsularIP(paquete_rx, paquete_rx.TTL, paquete_rx.id, paquete_rx.ip_origen, paquete_rx.ip_destino);
                writeSlip(paquete_rx.FRAMES, len_rx, vport_tx); // ENVIAR POR SLIP
            }
        }
    }
}
