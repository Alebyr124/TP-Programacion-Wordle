#include "ed1.h"

MaxHeap* crear_heap(int capacidad) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap == NULL) {
        printf("Error de memoria al crear heap.\n");
        return NULL;
    }
    heap->capacidad = capacidad;
    heap->tamano = 0;
    heap->datos = (word*)malloc(capacidad * sizeof(word));
    if (heap->datos == NULL) {
        free(heap);
        printf("Error de memoria al crear el arreglo del heap.\n");
        return NULL;
    }
    return heap;
}

void intercambiar(word *a, word *b) {
    word temp = *a;
    *a = *b;
    *b = temp;
}

void insertar_heap(MaxHeap* heap, word nueva_palabra) {
    if (heap->tamano == heap->capacidad) {
        printf("Heap lleno. No se puede insertar.\n");
        return;
    }
    // Insertar la nueva palabra en la última posición
    heap->datos[heap->tamano] = nueva_palabra;
    heap->tamano++;

    // Ajustar la posición del nuevo elemento
    int i = heap->tamano - 1;
    while (i != 0 && heap->datos[i].prioridad > heap->datos[(i - 1) / 2].prioridad) {
        intercambiar(&heap->datos[i], &heap->datos[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

word eliminar_maximo(MaxHeap* heap) {
    word max = heap->datos[0]; // Guardar el máximo
    heap->datos[0] = heap->datos[heap->tamano - 1]; // Reemplazar raíz con el último elemento
    heap->tamano--; // Reducir el tamaño

    // Ajustar el heap (hacer heapify hacia abajo)
    int i = 0;
    while (1) {
        int mayor = i;
        int izquierda = 2 * i + 1;
        int derecha = 2 * i + 2;

        // Comparar con el hijo izquierdo
        if (izquierda < heap->tamano && heap->datos[izquierda].prioridad > heap->datos[mayor].prioridad) {
            mayor = izquierda;
        }
        // Comparar con el hijo derecho
        if (derecha < heap->tamano && heap->datos[derecha].prioridad > heap->datos[mayor].prioridad) {
            mayor = derecha;
        }
        // Si el padre es mayor que ambos hijos, detener
        if (mayor == i) {
            break;
        }

        // Intercambiar con el hijo mayor y continuar
        intercambiar(&heap->datos[i], &heap->datos[mayor]);
        i = mayor;
    }

    return max;
}


void liberar_heap(MaxHeap* heap) {
    if (heap != NULL) {
        if (heap->datos != NULL) {
            free(heap->datos);
            heap->datos = NULL; // Evitar acceso a memoria liberada
        }
        free(heap);
        heap = NULL; // Evitar acceso a memoria liberada
    }
}


void expandir_heap(MaxHeap* heap) {
    int nueva_capacidad = heap->capacidad * 2;  // Duplicar la capacidad
    word* nuevos_datos = (word*)realloc(heap->datos, nueva_capacidad * sizeof(word));

    if (nuevos_datos == NULL) {
        printf("Error: No se pudo expandir la memoria del heap.\n");
        return;  // Error al asignar más memoria
    }

    heap->datos = nuevos_datos;    // Asignar el nuevo bloque de memoria
    heap->capacidad = nueva_capacidad;  // Actualizar la capacidad
}
