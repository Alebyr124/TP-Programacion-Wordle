#include "wordle.h"

int main(int argc, char** argv) {
    
    // Definicion de variables
    char palabra_secreta[LARGO_PALABRA + 1]; 
    intento intento_jugable[MAX_INTENTOS];
    intento intento_prueba[MAX_INTENTOS];

    // Inicialización de los intentos
    for (int i = 0; i < MAX_INTENTOS; i++) {
        strcpy(intento_jugable[i].letras_acertadas, "*****");
        strcpy(intento_prueba[i].letras_acertadas, "*****");
        strcpy(intento_prueba[i].palabra, "");

    }

    FILE *archivo = fopen("bd.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    MaxHeap* heap = crear_heap(1); 
    word intento_bot;
    int letras_no_permitidas[ALFABETO_SIZE];
    for (int k = 0; k < ALFABETO_SIZE; k++) {
        letras_no_permitidas[k] = 0; // Inicializa a 0 (permitido)
    }

    // Leer palabras del archivo y añadir al heap
    while (fscanf(archivo, "%[^,],%d\n", intento_bot.palabra, &intento_bot.prioridad) != EOF) {
        if (heap->tamano == heap->capacidad)
            expandir_heap(heap);
        insertar_heap(heap, intento_bot);
    }
    
    srand(time(NULL));
    int random = rand() % heap->tamano;
    int random2;
    do {
        random2 = rand() % heap->tamano;
    } while (random2 == random);  

    // Verifica si la palabra secreta es válida
    if(argc > 1 && strlen(argv[1]) == 5){
        *argv[1] = tolower(*argv[1]);
        strcpy(palabra_secreta, argv[1]);
    } 
    else 
        strcpy(palabra_secreta, heap->datos[random2].palabra);

    // Menú inicial
    printf("\n\n\t\t\t\tWORDLE: EL JUEGO");
    printf("\n\n\t\tAdivina la palabra secreta con 6 intentos.\n");
    sleep(1);
    printf("\n\n\t\t\tPulse ENTER para continuar");
    getchar();

    //jugable(palabra_secreta, intento_jugable);
    sleep(1);
    printf("\n\n\t\t\tPulse ENTER para continuar");
    getchar();

    printf("INTENTO BOT\n\n");
    strcpy(intento_prueba[0].palabra, heap->datos[random].palabra);
    printf("Palabra a adivinar: %s\n\n", palabra_secreta);

    for (int k = 0; k < MAX_INTENTOS; k++) {
        // Verificar el intento actual
        verificar(palabra_secreta, &intento_prueba[k]);
        //system(limpiar);
        printf("\n\tINTENTO BOT\n\n");
        printf("\tPalabra a adivinar: %s\n\n", palabra_secreta);
        tablero(k, intento_prueba);

        // Si el bot ha adivinado la palabra
        if (strcmp(intento_prueba[k].palabra, palabra_secreta) == 0) {
            printf("\nEl bot ha adivinado la palabra %s en el intento %d!\n", palabra_secreta, k + 1);
            break;
        }

        // Filtrar el heap después de cada intento
        int nuevo_tamano = 0;  // Mantendrá el tamaño del heap después de filtrar
        printf("%d",heap->tamano);
        for (int i = 0; i < heap->tamano; i++) {
            if (cumple_condiciones(intento_prueba[k].palabra, intento_prueba[k].letras_acertadas, letras_no_permitidas, &heap->datos[i])) {
                heap->datos[nuevo_tamano] = heap->datos[i]; // Guardar solo las palabras que cumplen las condiciones
                nuevo_tamano++;
            }
        }
        heap->tamano = nuevo_tamano;

        // Si el heap se queda sin palabras, el bot ha fallado
        if (heap->tamano == 0) {
            printf("No hay más palabras posibles en el heap, el bot falló.\n");
            k = MAX_INTENTOS; // Rompe el bucle si el heap está vacío
        }
        else {
            // Copiar la siguiente palabra del heap en el próximo intento
            strcpy(intento_prueba[k + 1].palabra, heap->datos[0].palabra);
        }
    }

    for(int i = 0; i < MAX_INTENTOS; i++)
        printf("%s  %s\n", intento_prueba[i].letras_acertadas, intento_prueba[i].palabra);
    for(int i=0; i < heap->tamano;i++)
        printf("%s  ", heap->datos[i].palabra);

    fclose(archivo);
    liberar_heap(heap);
    return 0;
}
