#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Ordenamiento Burbuja (Bubble Sort) con optimización de parada temprana.
 * Complejidad Temporal:
 *   - Mejor caso (arreglo ya ordenado): O(n)
 *   - Caso promedio y peor caso: O(n^2)
 * Complejidad Espacial: O(1) (in-place)
 */
void ordenamiento_burbuja(int arr[], int n, long long *comparaciones) {
    *comparaciones = 0;
    for (int i = 0; i < n - 1; i++) {
        int hubo_intercambio = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparaciones)++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                hubo_intercambio = 1;
            }
        }
        // Si no hubo intercambios en una pasada completa, ya está ordenado
        if (!hubo_intercambio) {
            break;
        }
    }
}

void copiar_arreglo(const int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

int main() {
    // Nota: Para O(n^2), n mayores a 50,000 tomarán varios segundos
    int tamanos[] = {100, 1000, 5000, 10000, 25000};
    int num_pruebas = 5;
    int repeticiones = 10;

    srand((unsigned int)time(NULL));

    printf("=== EXPERIMENTO: ORDENAMIENTO BURBUJA (C) ===\n");
    printf("%-12s | %-18s | %-18s\n", "Tamano (n)", "Tiempo Prom (ms)", "Comparaciones Prom");
    printf("-------------------------------------------------------\n");

    for (int t = 0; t < num_pruebas; t++) {
        int n = tamanos[t];
        int *base = (int *)malloc(n * sizeof(int));
        int *copia = (int *)malloc(n * sizeof(int));

        if (base == NULL || copia == NULL) {
            fprintf(stderr, "Error al asignar memoria.\n");
            return 1;
        }

        // Generar datos aleatorios
        for (int i = 0; i < n; i++) {
            base[i] = rand() % (n * 10);
        }

        double tiempo_total_ms = 0.0;
        long long comp_totales = 0;

        for (int r = 0; r < repeticiones; r++) {
            copiar_arreglo(base, copia, n);
            long long comps = 0;

            clock_t inicio = clock();
            ordenamiento_burbuja(copia, n, &comps);
            clock_t fin = clock();

            tiempo_total_ms += ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
            comp_totales += comps;
        }

        printf("%-12d | %-18.4f | %-18.2f\n",
               n,
               tiempo_total_ms / repeticiones,
               (double)comp_totales / repeticiones);

        free(base);
        free(copia);
    }

    return 0;
}