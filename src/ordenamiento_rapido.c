#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Función auxiliar de partición (esquema de Lomuto).
 * Toma el último elemento como pivote y ubica los menores a la izquierda.
 */
int particionar(int arr[], int bajo, int alto, long long *comparaciones) {
    int pivote = arr[alto];
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        (*comparaciones)++;
        if (arr[j] <= pivote) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;

    return i + 1;
}

/**
 * Ordenamiento Rápido (Quick Sort) recursivo.
 * Complejidad Temporal:
 *   - Mejor caso y caso promedio: O(n log n)
 *   - Peor caso (arreglos ya ordenados/inversos con pivote extremo): O(n^2)
 * Complejidad Espacial: O(log n) promedio en pila de recursión (O(n) peor caso)
 */
void quick_sort_recursivo(int arr[], int bajo, int alto, long long *comparaciones) {
    if (bajo < alto) {
        int indice_pivote = particionar(arr, bajo, alto, comparaciones);
        quick_sort_recursivo(arr, bajo, indice_pivote - 1, comparaciones);
        quick_sort_recursivo(arr, indice_pivote + 1, alto, comparaciones);
    }
}

void ordenamiento_rapido(int arr[], int n, long long *comparaciones) {
    *comparaciones = 0;
    if (n > 1) {
        quick_sort_recursivo(arr, 0, n - 1, comparaciones);
    }
}

void copiar_arreglo(const int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

int main() {
    // Mismos tamaños que Burbuja para comparar directamente en tus gráficas
    int tamanos[] = {100, 1000, 5000, 10000, 25000};
    int num_pruebas = 5;
    int repeticiones = 10;

    srand((unsigned int)time(NULL));

    printf("=== EXPERIMENTO: ORDENAMIENTO RAPIDO / QUICK SORT (C) ===\n");
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
            ordenamiento_rapido(copia, n, &comps);
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