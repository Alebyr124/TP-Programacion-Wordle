#include <stdio.h>
#include <stdlib.h>

#define LARGO_PALABRA 5

typedef struct word {
  char palabra[LARGO_PALABRA+1];
  char letras_no_permitidas[28];
  int prioridad;
} word;

typedef struct {
    word *datos;  // Arreglo de palabras
    int capacidad; // Capacidad del heap
    int tamano;    // Número actual de elementos
} MaxHeap;

// Funciones para el Max-Heap
MaxHeap* crear_heap(int capacidad);
void intercambiar(word *a, word *b);
void insertar_heap(MaxHeap* heap, word nueva_palabra);
word eliminar_maximo(MaxHeap* heap);
void liberar_heap(MaxHeap* heap);
void expandir_heap(MaxHeap* heap);
