#include <stdio.h>
#include "serial.h"
#include "slip.h"

#define BYTE unsigned char
// #define VIRTUAL_PORT "../tmp/p1"

int main(int nargs, char* arg_arr[]){
    if(nargs == 2){
        char msg[500];
        char msg_rx[1000];
        int len = 0;
        
        //Obtiene puerto virtual
        char* virtual_port = arg_arr[1];

        FILE* vport = fopen(virtual_port, "w+");
        //Inicia la capa 1 y 2
        //Obtiene descriptores
        int stdin_desc = fileno(stdin);
        //Obtiene descriptores
  
        //Indica inicio del chat
        printf("chat\n");
        printf("Ya puede escribir sus mensajes !\n");

        while(true){
            //Lee mensajes del puerto virtual y los muestra
            len = readSlip((BYTE*)msg_rx, 1000,vport);
            msg_rx[len-1] = '\0';
            if(len>0){
                printf("El otro usuario dice: %s", msg_rx);
            }
            // len = readSlip((BYTE*)msg_rx,1000);
            // msg_rx[len] = '\0';
            // if(len>0){
            //     printf("El otro usuario dice: %s", msg_rx);
            // }
            //Lee consola y envía el mensaje por el puerto virtual
            len = readPort(stdin_desc, (BYTE*)msg, 500, 100);
            msg[len] = '\0';
            if(len>0){
                writeSlip((BYTE*)msg, len,vport);
            }
        }
    }else{
        //Se requiere un y solo un argumento; el puerto virtual
        printf("Debe indicar el puerto virtual!\n");
    }    
}