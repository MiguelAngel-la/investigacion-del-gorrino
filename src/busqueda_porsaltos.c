#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * Realiza una búsqueda por bloques de tamaño √n seguida de un barrido lineal.
 * PRECONDICIÓN: El arreglo debe estar ordenado de forma ascendente.
 * Complejidad Temporal: O(√n) | Complejidad Espacial: O(1)
 */
int busqueda_por_saltos(const int arr[], int n, int objetivo, long long *comparaciones) {
    *comparaciones = 0;
    if (n <= 0) return -1;

    int paso = (int)sqrt((double)n);
    int salto_base = paso;
    int prev = 0;

    // Fase 1: Avance por saltos de tamaño √n
    while (prev < n) {
        int indice_bloque = (paso < n ? paso : n) - 1;
        (*comparaciones)++;
        if (arr[indice_bloque] < objetivo) {
            prev = paso;
            paso += salto_base;
            if (prev >= n) {
                return -1;
            }
        } else {
            break;
        }
    }

    // Fase 2: Búsqueda lineal dentro del bloque identificado
    int limite_superior = (paso < n) ? paso : n;
    while (prev < limite_superior) {
        (*comparaciones)++;
        if (arr[prev] == objetivo) {
            return prev;
        }
        (*comparaciones)++;
        if (arr[prev] > objetivo) {
            return -1;
        }
        prev++;
    }

    return -1;
}

int main() {
    int tamanos[] = {100, 1000, 10000, 100000, 500000};
    int num_pruebas = 5;
    int repeticiones = 200;

    srand((unsigned int)time(NULL));

    printf("=== EXPERIMENTO: BUSQUEDA POR SALTOS (C) ===\n");
    printf("%-12s | %-18s | %-18s\n", "Tamano (n)", "Tiempo Prom (us)", "Comparaciones Prom");
    printf("-------------------------------------------------------\n");

    for (int t = 0; t < num_pruebas; t++) {
        int n = tamanos[t];
        int *datos = (int *)malloc(n * sizeof(int));
        if (datos == NULL) {
            fprintf(stderr, "Error al asignar memoria.\n");
            return 1;
        }

        // Generar arreglo ordenado de forma estrictamente ascendente (precondición)
        datos[0] = rand() % 10;
        for (int i = 1; i < n; i++) {
            datos[i] = datos[i - 1] + (rand() % 10) + 1;
        }

        double tiempo_total_us = 0.0;
        long long comp_totales = 0;

        for (int r = 0; r < repeticiones; r++) {
            int objetivo = (r % 2 == 0) ? datos[rand() % n] : -1;
            long long comps = 0;

            clock_t inicio = clock();
            busqueda_por_saltos(datos, n, objetivo, &comps);
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