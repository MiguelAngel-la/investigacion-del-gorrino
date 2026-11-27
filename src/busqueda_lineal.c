#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Realiza una búsqueda secuencial sobre el arreglo.
 * No requiere que el arreglo esté ordenado.
 * Complejidad Temporal: O(n) | Complejidad Espacial: O(1)
 */
int busqueda_lineal(const int arr[], int n, int objetivo, long long *comparaciones) {
    *comparaciones = 0;
    for (int i = 0; i < n; i++) {
        (*comparaciones)++;
        if (arr[i] == objetivo) {
            return i;
        }
    }
    return -1;
}

int main() {
    int tamanos[] = {100, 1000, 10000, 100000, 500000};
    int num_pruebas = 5;
    int repeticiones = 200;

    srand((unsigned int)time(NULL));

    printf("=== EXPERIMENTO: BUSQUEDA LINEAL (C) ===\n");
    printf("%-12s | %-18s | %-18s\n", "Tamano (n)", "Tiempo Prom (us)", "Comparaciones Prom");
    printf("-------------------------------------------------------\n");

    for (int t = 0; t < num_pruebas; t++) {
        int n = tamanos[t];
        int *datos = (int *)malloc(n * sizeof(int));
        if (datos == NULL) {
            fprintf(stderr, "Error al asignar memoria.\n");
            return 1;
        }

        // Llenar arreglo con valores aleatorios (sin ordenar)
        for (int i = 0; i < n; i++) {
            datos[i] = rand() % (n * 10);
        }

        double tiempo_total_us = 0.0;
        long long comp_totales = 0;

        for (int r = 0; r < repeticiones; r++) {
            // Alternar entre un elemento existente y uno inexistente (-1)
            int objetivo = (r % 2 == 0) ? datos[rand() % n] : -1;
            long long comps = 0;

            clock_t inicio = clock();
            busqueda_lineal(datos, n, objetivo, &comps);
            clock_t fin = clock();

            tiempo_total_us += ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000000.0;
            comp_totales += comps;
        }

        printf("%-12d | %-18.4f | %-18.2f\n",
               n,
               tiempo_total_us / repeticiones,
               (double)comp_totales / repeticiones);

        free(datos);
    }

    return 0;
}