#include "funciones.h"

int main() {
    int op;

    cargar_datos_historicos();

    do {
        menu();
        printf("Seleccione una opción: ");
        scanf("%d", &op);

        switch (op) {
            case 1: monitoreo_actual(); break;
            case 2: prediccion_futura(); break;
            case 3: alertas_preventivas(); break;
            case 4: promedios_historicos(); break;
            case 5: recomendaciones(); break;
            case 6: exportar_datos(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción inválida\n");
        }

    } while (op != 0);

    return 0;
}
