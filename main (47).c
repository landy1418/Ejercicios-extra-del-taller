#include <stdio.h>
#include <string.h>

#define MAX_TAREAS 5

void ingresarLimites(float *horasMax, float *presupuestoMax);
int ingresarTarea(char nombres[][50], float duraciones[], float costos[], float horasMax, float presupuestoMax, int *cantidad, float *horasUsadas, float *presupuestoUsado);
void mostrarTareas(int cantidad, char nombres[][50]);
void buscarTarea(int cantidad, char nombres[][50], float duraciones[], float costos[]);

int main() {
    char nombres[MAX_TAREAS][50];
    float duraciones[MAX_TAREAS] = {0};
    float costos[MAX_TAREAS] = {0};
    float horasMax, presupuestoMax;
    float horasUsadas = 0;
    float presupuestoUsado = 0;
    int cantidad = 0;
    int opcion;

    ingresarLimites(&horasMax, &presupuestoMax);

    do {
        printf("\n==== MENÚ ====\n");
        printf("1. Ingresar tarea\n");
        printf("2. Mostrar tareas\n");
        printf("3. Buscar tarea\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad >= MAX_TAREAS || horasUsadas >= horasMax || presupuestoUsado >= presupuestoMax) {
                    printf("Ya no se pueden ingresar más tareas.\n");
                } else {
                    ingresarTarea(nombres, duraciones, costos, horasMax, presupuestoMax, &cantidad, &horasUsadas, &presupuestoUsado);
                }
                break;
            case 2:
                mostrarTareas(cantidad, nombres);
                break;
            case 3:
                buscarTarea(cantidad, nombres, duraciones, costos);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 4);

    return 0;
}

void ingresarLimites(float *horasMax, float *presupuestoMax) {
    printf("Ingrese el total de horas disponibles: ");
    while (scanf("%f", horasMax) != 1 || *horasMax <= 0) {
        while (getchar() != '\n');
        printf("Valor inválido. Ingrese nuevamente: ");
    }

    printf("Ingrese el presupuesto total disponible: ");
    while (scanf("%f", presupuestoMax) != 1 || *presupuestoMax <= 0) {
        while (getchar() != '\n');
        printf("Valor inválido. Ingrese nuevamente: ");
    }
}

int ingresarTarea(char nombres[][50], float duraciones[], float costos[], float horasMax, float presupuestoMax, int *cantidad, float *horasUsadas, float *presupuestoUsado) {
    printf("Nombre de la tarea: ");
    scanf("%s", nombres[*cantidad]);

    float duracion;
    float costo;

    do {
        printf("Duración en horas: ");
        while (scanf("%f", &duracion) != 1 || duracion < 0) {
            while (getchar() != '\n');
            printf("Valor inválido. Intente de nuevo: ");
        }

        if (*horasUsadas + duracion > horasMax) {
            printf("Duración excede el límite. Horas restantes: %.2f\n", horasMax - *horasUsadas);
        }
    } while (*horasUsadas + duracion > horasMax);

    do {
        printf("Costo de la tarea: ");
        while (scanf("%f", &costo) != 1 || costo < 0) {
            while (getchar() != '\n');
            printf("Valor inválido. Intente de nuevo: ");
        }

        if (*presupuestoUsado + costo > presupuestoMax) {
            printf("Costo excede el presupuesto. Presupuesto restante: %.2f\n", presupuestoMax - *presupuestoUsado);
        }
    } while (*presupuestoUsado + costo > presupuestoMax);

    duraciones[*cantidad] = duracion;
    costos[*cantidad] = costo;
    *horasUsadas += duracion;
    *presupuestoUsado += costo;
    (*cantidad)++;

    return *cantidad;
}

void mostrarTareas(int cantidad, char nombres[][50]) {
    if (cantidad == 0) {
        printf("No hay tareas registradas.\n");
        return;
    }

    printf("\n--- Tareas Registradas ---\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, nombres[i]);
    }
}

void buscarTarea(int cantidad, char nombres[][50], float duraciones[], float costos[]) {
    if (cantidad == 0) {
        printf("No hay tareas para buscar.\n");
        return;
    }

    char buscar[50];
    int encontrada = 0;

    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", buscar);

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(buscar, nombres[i]) == 0) {
            printf("Tarea encontrada: %s\n", nombres[i]);
            printf("Duración: %.2f horas\n", duraciones[i]);
            printf("Costo: $%.2f\n", costos[i]);
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Tarea no encontrada.\n");
    }
}
