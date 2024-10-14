#include "wordle.h"

int main(int argc, char** argv) {
    
    // Definicion de variables
    char palabra_secreta[LARGO_PALABRA+1]; 
    intento *intento_jugable =(intento*)malloc(MAX_INTENTOS*sizeof(intento));

    // Verifica si la palabra secreta es válida
    assert(argc > 1 && strlen(argv[1]) == 5);
    strcpy(palabra_secreta, argv[1]); 

    // Inicialización de los intentos
    for (int i = 0; i < MAX_INTENTOS; i++) {
        strcpy(intento_jugable[i].letras_acertadas, "*****");
    }

    // Menú inicial
    printf("\n\n\t\t\t\tWORDLE: EL JUEGO");
    printf("\n\n\t\tAdivina la palabra secreta con 6 intentos.\n");
    sleep(1);
    printf("\n\n\t\t\tPulse ENTER para continuar");
    getchar();



    // Modo de juego jugable
    //jugable(palabra_secreta, &intento_jugable);




    srand(time(NULL));

    FILE *archivo = fopen("bd.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    
    MaxHeap* heap = crear_heap(1); 
    word intento_bot;
    int cant_palabras = 0;
    
    // Leer palabras del archivo y añadir al heap
    while (fscanf(archivo, "%5[^,],%d\n", intento_bot.palabra, &intento_bot.prioridad) != EOF) {
        insertar_heap(heap, intento_bot);
        cant_palabras++;
        if(heap->capacidad == cant_palabras-1)
            expandir_heap(heap);
    }
    

    int random = rand() % cant_palabras;
    intento *intento_prueba = (intento *)malloc(sizeof(intento));

    strcpy(intento_prueba->palabra, heap->datos[random].palabra);
    strcpy(intento_prueba->letras_acertadas, "*****");

    for (int k = 0; k < MAX_INTENTOS; k++) {
        verificar(palabra_secreta, intento_prueba);

        printf("%s  %s\n", intento_prueba->letras_acertadas, intento_prueba->palabra);
        
        // Re-crear el heap auxiliar para cada intento
        MaxHeap* arbol_aux = crear_heap(100);
        for (int i = 0; i < heap->tamano; i++) {
            if (cumple_condiciones(intento_prueba->palabra, intento_prueba->letras_acertadas, &heap->datos[i])) {
                insertar_heap(arbol_aux, heap->datos[i]);
                if(heap->capacidad == i-1)
                    expandir_heap(heap);
            }
        }

        if (arbol_aux->tamano > 0) {
            printf("La palabra en la raíz del árbol es: %s\n", arbol_aux->datos[0].palabra);
            strcpy(intento_prueba->palabra, arbol_aux->datos[0].palabra);
        } else {
            printf("No hay palabras que cumplan las condiciones.\n");
        }
        
        liberar_heap(arbol_aux);

    }


    
    fclose(archivo);
    liberar_heap(heap);
    //free(intento_prueba);


    return 0;
}



