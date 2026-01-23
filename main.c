#include <stdio.h>
#include "funciones.h"
/*cc .\main.c .\funciones.c -o main*/
int main() {
    int op;

    cargar_datos_quito();


    do {
        menu();
        printf("Seleccione una opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1: monitoreo_actual(); break;
            case 2: ingresar_datos_zona(); break;
            case 3: alertas_preventivas(); break;
            case 4: promedios_historicos(); break;
            case 5: recomendaciones(); break;
            case 6: exportar_datos(); break;
            case 7: prediccion_futura(); break;
            case 0: printf("hasta pronto \n"); break;
            default: printf("Opcion invalida\n");
        }

    } while (op != 0);

    return 0;
}
