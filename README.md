# investigacion-del-gorrino

Universidad de COlima

Facultad: Facultad de Ingeniería Mecánica y Eléctrica (FIME)

Carrera: Ingeniería en Computación Inteligente

Asignatura: Estructura de Datos

Título del Estudio: Evaluación Teórica y Empírica de Algoritmos de Búsqueda y Ordenamiento: Búsqueda Lineal, Búsqueda por Saltos, Ordenamiento Burbuja y Ordenamiento Rápido

Integrante(s) y Matrícula(s):
LUIS GIOVANNI PINEDA TOCAVEN 20223363
EDUARDO ANTOLIN HERRERA SOLORZANO 20222987
MIGUEL ANGEL PALOMINO AGUILAR  20223533

Docente: LUIS EDUARDO MORAN LOPEZ

Fecha: 23 de noviembre de 2026

1. Resumen Ejecutivo (Abstract)
En el desarrollo de software de alto rendimiento, el crecimiento del volumen de datos convierte la selección algorítmica en un factor determinante entre tiempos de respuesta de milisegundos y cuellos de botella críticos. Este estudio presenta una evaluación matemática y experimental de cuatro algoritmos fundamentales: Búsqueda Lineal (O(n)) y Búsqueda por Saltos (O(√n)) en recuperación de información; junto con Ordenamiento Burbuja (O(n^2 )) y Ordenamiento Rápido (O(n log⁡n )) en reordenamiento de datos.
Las pruebas empíricas se ejecutaron bajo un entorno controlado de arquitectura x86_64 (8 núcleos, Python 3.10.16) utilizando arreglos sintéticos pseudoaleatorios y cronometraje de alta precisión (perf_counter). Los resultados demuestran que Quick Sort supera a Bubble Sort a partir de un umbral crítico de n≈14 elementos, alcanzando para n=10,000 un tiempo promedio de 40.05 ms (132,150 comparaciones) frente a los 13,692.15 ms (49,983,404 comparaciones) de Bubble Sort (341.9× más rápido). Asimismo, sobre arreglos ordenados de n=1,000,000, Jump Search reduce el tiempo promedio a 608.53 μs (979 comparaciones) frente a los 67,746.27 μs (579,069 comparaciones) de la Búsqueda Lineal (111.3× más rápido), validando las cotas asintóticas teóricas.

2. Fundamento Teórico y Análisis Asintótico
2.1. Definición Formal de las Cotas Asintóticas
Sea T(n):N→R^+ el costo temporal de un algoritmo para una entrada de tamaño n, y sea g(n):N→R^+ una función de referencia positiva:
	Cota Superior (O): T(n)∈O(g(n)) si existen constantes c>0 y n_0∈N tales que 0≤T(n)≤c⋅g(n) para todo n≥n_0.
	Cota Inferior (Ω): T(n)∈Ω(g(n)) si existen constantes c>0 y n_0∈N tales que 0≤c⋅g(n)≤T(n) para todo n≥n_0.
	Cota Ajustada (Θ): T(n)∈Θ(g(n)) si existen constantes c_1,c_2>0 y n_0∈N tales que 0≤c_1⋅g(n)≤T(n)≤c_2⋅g(n) para todo n≥n_0.
2.2. Búsqueda Lineal (Linear Search)
	Mecanismo: Recorre secuencialmente el arreglo A[0…n-1] desde el inicio hasta localizar la llave objetivo x o alcanzar el final. No requiere que los datos estén ordenados.
Pseudocódigo:
ALGORITMO BusquedaLineal(A, n, x)
    PARA i <- 0 HASTA n - 1 HACER
        SI A[i] == x ENTONCES
            RETORNAR i
        FIN SI
    FIN PARA
    RETORNAR -1
FIN ALGORITMO
Análisis de Complejidad:
	Mejor caso (Ω(1)): El objetivo está en A[0] (1 comparación).
	Caso promedio (Θ(n)): Con probabilidad uniforme 1/n por posición, T_"prom"  (n)=∑_(i=1)^n▒i/n=(n+1)/2∈Θ(n).
	Peor caso (O(n)): El elemento está en A[n-1] o ausente (n comparaciones).
	Complejidad espacial: O(1) auxiliar (solo el índice iterador).

2.3. Búsqueda por Saltos (Jump Search)
	Mecanismo: Exige que el arreglo A[0…n-1] esté ordenado. Avanza en bloques de tamaño m verificando los extremos de cada bloque hasta hallar un intervalo donde A[(k+1)m-1]≥x, ejecutando luego un barrido lineal interno.
Pseudocódigo:
ALGORITMO BusquedaPorSaltos(A, n, x)
    paso <- PISO(RAIZ_CUADRADA(n))
    prev <- 0
    MIENTRAS A[MIN(paso, n) - 1] < x HACER
        prev <- paso
        paso <- paso + PISO(RAIZ_CUADRADA(n))
        SI prev >= n ENTONCES
            RETORNAR -1
        FIN SI
    FIN MIENTRAS
    MIENTRAS prev < MIN(paso, n) HACER
        SI A[prev] == x ENTONCES
            RETORNAR prev
        FIN SI
        prev <- prev + 1
    FIN MIENTRAS
    RETORNAR -1
FIN ALGORITMO

Análisis de Complejidad:
	En el peor escenario realiza n/m saltos y m-1 pasos lineales. Minimizando f(m)=n/m+m-1:
df/dm=-n/m^2 +1=0⟹m^*=√n
	Sustituyendo m^*=√n, el máximo costo es 2√n-1 comparaciones.
	Mejor caso (Ω(1)): Coincide con el extremo del primer bloque (A[√n-1]=x).
	Caso promedio (Θ(√n)) y Peor caso (O(√n)): Crecimiento sublineal proporcional a √n.
	Complejidad espacial: O(1) auxiliar.

2.4. Ordenamiento Burbuja (Bubble Sort)
	Mecanismo: Algoritmo iterativo in-place que compara pares adyacentes A[j] y A[j+1], intercambiándolos si A[j]>A[j+1] para desplazar el máximo hacia el final en cada pasada. Incluye bandera booleana de corte temprano.
Pseudocódigo:
ALGORITMO OrdenamientoBurbuja(A, n)
    PARA i <- 0 HASTA n - 2 HACER
        intercambio <- FALSO
        PARA j <- 0 HASTA n - i - 2 HACER
            SI A[j] > A[j + 1] ENTONCES
                INTERCAMBIAR(A[j], A[j + 1])
                intercambio <- VERDADERO
            FIN SI
        FIN PARA
        SI NO intercambio ENTONCES
            ROMPER
        FIN SI
    FIN PARA
FIN ALGORITMO

Análisis de Complejidad:
	Sumatoria de comparaciones: T(n)=∑_(i=0)^(n-2)▒(n-i-1) =n(n-1)/2=1/2 n^2-1/2 n.
	Mejor caso (Ω(n)): Arreglo ya ordenado; la bandera detiene la ejecución tras la primera pasada (n-1 comparaciones).
	Caso promedio (Θ(n^2 )) y Peor caso (O(n^2 )): Arreglo aleatorio o inversamente ordenado (n(n-1)/2 comparaciones).
	Complejidad espacial: O(1) auxiliar.

2.5. Ordenamiento Rápido (Quick Sort)
	Mecanismo: Paradigma Divide y Vencerás. Elige un pivote (mediante mediana de tres) y particiona el subarreglo colocando los elementos menores o iguales al pivote a su izquierda y los mayores a su derecha, aplicando recursión sobre ambas particiones.
Pseudocódigo:
ALGORITMO QuickSort(A, low, high)
    SI low < high ENTONCES
        pi <- Particionar(A, low, high)
        QuickSort(A, low, pi - 1)
        QuickSort(A, pi + 1, high)
    FIN SI
FIN ALGORITMO

FUNCION Particionar(A, low, high)
    // Pivote seleccionado por mediana de tres colocado en A[high]
    pivote <- A[high]
    i <- low - 1
    PARA j <- low HASTA high - 1 HACER
        SI A[j] <= pivote ENTONCES
            i <- i + 1
            INTERCAMBIAR(A[i], A[j])
        FIN SI
    FIN PARA
    INTERCAMBIAR(A[i + 1], A[high])
    RETORNAR i + 1
FIN FUNCION
Análisis de Complejidad:
	Mejor caso (Ω(n log⁡n )): Particiones balanceadas n/2. Recurrencia T(n)=2T(n/2)+Θ(n)⟹Θ(n log_2⁡n ) por el Caso 2 del Teorema Maestro.
	Caso promedio (Θ(n log⁡n )): En permutaciones aleatorias realiza C(n)≈2n ln⁡n≈1.39n log_2⁡n comparaciones.
	Peor caso (O(n^2 )): Particiones completamente desbalanceadas (n-1 y 0), degenerando en T(n)=T(n-1)+Θ(n)∈O(n^2 ).
	Complejidad espacial: O(log⁡n ) promedio por la pila de recursión (O(n) en el peor caso).

2.6. Cuadro Comparativo de Complejidades
Algoritmo	Tipo	Mejor Caso	Caso Promedio	Peor Caso	Espacio Auxiliar
Búsqueda Lineal	Búsqueda	Ω(1)	Θ(n)	O(n)	O(1)
Búsqueda por Saltos	Búsqueda	Ω(1)	Θ(√n)	O(√n)	O(1)
Ordenamiento Burbuja	Ordenamiento	Ω(n)	Θ(n^2 )	O(n^2 )	O(1)
Ordenamiento Rápido	Ordenamiento	Ω(n log⁡n )	Θ(n log⁡n )	O(n^2 )	O(log⁡n )

3. Diseño Experimental e Instrumentación
	Hardware de Prueba: Arquitectura x86_64 GenuineIntel (familia 6, modelo 63), 8 núcleos físicos (1 hilo por núcleo), frecuencia efectiva ≈3.0" GHz"  (2998.15" BogoMIPS" ), soporte vectorial AVX2/SSE4.2, líneas de caché de 64 bytes (clflush size 64) y direccionamiento físico de 46 bits.
	Software e Intérprete: Sistema operativo Linux 4.19.0 (glibc 2.36), intérprete CPython 3.10.16 compilado con GCC -O3, sin librerías externas en C para evaluar el costo algorítmico puro.
	Generación de Datos y Cronometraje:
	Ordenamiento: Arreglos de enteros pseudoaleatorios uniformes en [1,10n] (random.seed(42)) para n∈{100,500,1000,2500,5000,10000} (5 réplicas por tamaño), más un barrido fino para n∈[10,100] (50 réplicas) para ubicar el umbral de cruce.
	Búsqueda: Arreglos ordenados A[i]=2i para n∈{1000,10000,50000,100000,500000,1000000} con 100 consultas por tamaño (80 % exitosas aleatorias, 20 % fallidas).
	Medición: Reloj monotónico de alta resolución time.perf_counter() y contadores exactos de comparaciones de llaves.

	4. Resultados y Discusión Técnica
	4.1. Tablas de Resultados Empíricos
	Tabla 1: Rendimiento promedio en algoritmos de ordenamiento
Tamaño (n)	Bubble Time (ms)	Bubble Comp.	Quick Time (ms)	Quick Comp.	Aceleración (B / Q)
100	1.057	4,816	0.203	553	5.21×
500	33.290	123,973	1.701	4,156	19.57×
1,000	134.955	498,392	3.043	9,126	44.35×
2,500	816.179	3,119,601	8.237	27,661	99.09×
5,000	3,252.847	12,490,353	21.220	61,213	153.29×
10,000	13,692.153	49,983,404	40.049	132,150	341.89×
	Tabla 2: Rendimiento promedio en algoritmos de búsqueda (arreglos ordenados)
Tamaño (n)	Lineal Time (μs)	Lineal Comp.	Saltos Time (μs)	Saltos Comp.	Aceleración (L / S)
1,000	103.41	626	29.06	33	3.56×
10,000	722.54	5,955	56.10	100	12.88×
50,000	3,537.65	27,544	106.10	211	33.34×
100,000	7,705.96	60,289	192.59	317	40.01×
500,000	36,914.11	296,198	486.56	701	75.87×
1,000,000	67,746.27	579,069	608.53	979	111.33×

4.2. Discusión Técnica y Análisis Crítico
	¿A partir de qué umbral de n el algoritmo O(n log⁡n ) supera al O(n^2 )?
En el barrido fino experimental, para n=10 Bubble Sort obtiene 15.13" " μ"s"  frente a los 17.10" " μ"s"  de Quick Sort. Esto ocurre porque Quick Sort incurre en un costo fijo inicial (overhead) por la creación de marcos de pila recursivos y el cálculo de mediana de tres. Sin embargo, a partir de n≈14 elementos, el crecimiento cuadrático de Bubble Sort supera dicha constante (n=20: 51.12" " μ"s"  vs. 34.46" " μ"s" ). Por ello, algoritmos híbridos industriales como Introsort o Timsort conmutan a métodos cuadráticos simples únicamente en subarreglos menores a 16–32 elementos.
	¿Por qué Quick Sort puede degradarse a O(n^2 )?
Si la selección de pivote elige sistemáticamente el mínimo o máximo del subarreglo (por ejemplo, tomando siempre el primer o último elemento en arreglos ya ordenados o inversos), cada partición produce subproblemas de tamaño n-1 y 0. Esto colapsa el árbol binario de recursión de altura log_2⁡n en una cadena lineal de profundidad n, elevando las comparaciones a n(n-1)/2∈O(n^2 ). El uso de mediana de tres (como en nuestra implementación) o pivotes aleatorios previene esta degeneración.
	¿Cómo influye la localidad de referencia (caché) en el rendimiento real?
Quick Sort presenta alta localidad espacial porque recorre posiciones contiguas de memoria durante la partición, aprovechando las líneas de caché de 64 bytes y el hardware prefetching de la CPU; esto le permite superar en tiempo real a otros algoritmos O(n log⁡n ) como Heap Sort. En búsqueda, aunque la Búsqueda Lineal aprovecha óptimamente la lectura secuencial en caché L1 para arreglos pequeños, cuando n≥500,000 excede la caché L2/L3; ahí, aunque cada salto de tamaño √n en Jump Search genera un cache miss, reducir las comparaciones de 579,069 a 979 compensa ampliamente la latencia de acceso a RAM.

5. Conclusiones y Criterios de Selección
	Búsqueda Lineal (O(n)): Usar solo cuando los datos no estén ordenados y se realicen pocas consultas (donde ordenar previamente en O(n log⁡n ) no se amortiza), o en colecciones muy pequeñas (n<50).
	Búsqueda por Saltos (O(√n)): Ideal para estructuras ordenadas donde retroceder es costoso (cintas, listas con punteros de salto, bloques de disco) o cuando se busca simplicidad iterativa con memoria O(1) sin la complejidad de índices de la Búsqueda Binaria.
	Ordenamiento Burbuja (O(n^2 )): Descartar para producción en n>20; útil únicamente para fines didácticos, arreglos diminutos (n≤14) o verificación en O(n) de arreglos casi ordenados.
	Ordenamiento Rápido (O(n log⁡n )): Estándar recomendado para ordenamiento general en memoria RAM por su bajo consumo de memoria auxiliar (O(log⁡n )) y excelente afinidad con la caché del procesador.
6. Referencias Bibliográficas (Formato IEEE)
	T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, Introduction to Algorithms, 4th ed. Cambridge, MA, USA: MIT Press, 2022.
	R. Sedgewick and K. Wayne, Algorithms, 4th ed. Upper Saddle River, NJ, USA: Addison-Wesley Professional, 2011.
	D. E. Knuth, The Art of Computer Programming, Volume 3: Sorting and Searching, 2nd ed. Reading, MA, USA: Addison-Wesley, 1998.
	B. Shneiderman, "Jump searching: a fast sequential search technique," Communications of the ACM, vol. 21, no. 10, pp. 831–834, Oct. 1978.

7. Apéndice: Código Fuente Instrumentado (benchmark_algoritmos.py)
import math
import random
import time


def busqueda_lineal(arr: list, objetivo: int) -> tuple[int, int]:
    comparaciones = 0
    for i, val in enumerate(arr):
        comparaciones += 1
        if val == objetivo:
            return i, comparaciones
    return -1, comparaciones


def busqueda_saltos(arr: list, objetivo: int) -> tuple[int, int]:
    n = len(arr)
    paso = int(math.sqrt(n))
    prev = 0
    comparaciones = 0
    while prev < n:
        comparaciones += 1
        idx = min(paso, n) - 1
        if arr[idx] < objetivo:
            prev = paso
            paso += int(math.sqrt(n))
            if prev >= n:
                return -1, comparaciones
        else:
            break
    while prev < min(paso, n):
        comparaciones += 1
        if arr[prev] == objetivo:
            return prev, comparaciones
        prev += 1
    return -1, comparaciones


def ordenamiento_burbuja(arr: list) -> tuple[list, int]:
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    for i in range(n):
        intercambio = False
        for j in range(0, n - i - 1):
            comparaciones += 1
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                intercambio = True
        if not intercambio:
            break
    return a, comparaciones


def ordenamiento_rapido(arr: list) -> tuple[list, int]:
    a = arr.copy()
    comparaciones = [0]

    def particionar(low: int, high: int) -> int:
        mid = (low + high) // 2
        if a[mid] < a[low]:
            a[low], a[mid] = a[mid], a[low]
        if a[high] < a[low]:
            a[low], a[high] = a[high], a[low]
        if a[mid] < a[high]:
            a[mid], a[high] = a[high], a[mid]
        pivote = a[high]
        i = low - 1
        for j in range(low, high):
            comparaciones[0] += 1
            if a[j] <= pivote:
                i += 1
                a[i], a[j] = a[j], a[i]
        a[i + 1], a[high] = a[high], a[i + 1]
        return i + 1

    def quicksort_rec(low: int, high: int) -> None:
        if low < high:
            pi = particionar(low, high)
            quicksort_rec(low, pi - 1)
            quicksort_rec(pi + 1, high)

    if len(a) > 1:
        quicksort_rec(0, len(a) - 1)
    return a, comparaciones[0]
