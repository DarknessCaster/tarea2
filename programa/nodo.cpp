#include <stdio.h>

int opcion = 0;

int main(int nargs, char* arg_arr[]){
    if(nargs == 4){
        do {
            printf("\n================== MENU ==================\n");
            printf("1. Enviar mensaje de prueba\n");
            printf("2. Enviar mensaje de texto\n");
            printf("3. Buscar archivo txt\n");
            printf("4. Ver cantidad de mensajes enviados\n");
            printf("5. Listar archivos de texto del receptor\n");
            printf("6. Crear archivo y registrar un mensaje\n"); //  *** PUNTAJES EXTRAS: 2.
            printf("7. Cerrar programa receptor\n");
            printf("==============================================\n");
            printf("Ingrese la opcion deseada: ");
            scanf("%d", &opcion);
            getchar(); 
            switch (opcion) {
                case 1:
                    printf("Hola mundo");
                    break;
                default:
                    break;
            }
        } while (opcion != 7);
    } else{
        printf("");
    }
    return 0;
    }