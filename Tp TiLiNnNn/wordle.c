#include "wordle.h"

void jugable(char palabra_secreta[], intento intento_actual[]){
    int gano = 0;
    // Bucle de intentos
    for (int Nintentos = 0; Nintentos < MAX_INTENTOS && gano; Nintentos++) {
        system(limpiar);  // Limpia pantalla
        tablero(Nintentos, intento_actual);  // Muestra tablero
        printf("Intentos restantes: %d\n", MAX_INTENTOS-Nintentos);

        // Pide palabra y verifica que sea válida
        while(strlen(intento_actual[Nintentos].palabra) != 5){
            printf("Ingrese la palabra de 5 letras que desea adivinar: ");
            scanf("%s", intento_actual[Nintentos].palabra);
        }

        // Si adivina la palabra
        if (verificar(palabra_secreta, &intento_actual[Nintentos])) {
            system(limpiar);
            printf("\n\n\t\t\t  ¡HAS GANADO! La palabra secreta era: %s\n\n", palabra_secreta);
            gano = 1;
        } 
    }

    // Fin del juego si no adivina
    if(!gano)
        printf("Lo siento, no adivinaste la palabra. La palabra secreta era: %s\n\n", palabra_secreta);
}

// Dibuja el tablero con los intentos hasta el momento
void tablero(int Nintentos, intento intento_actual[]) {
    printf("\n\n\t\t\t   WORDLE: EL JUEGO");
    printf("\n\n\t\t\t╔═══╦═══╦═══╦═══╦═══╗");

    // Imprime cada intento
    for (int j = 0; j < Nintentos; j++) {    
        printf("\n\t\t\t║");
        for(int i = 0; i < LARGO_PALABRA; i++) {
            // Colores: verde si es correcto, amarillo si es letra en lugar incorrecto o blanco si no está en la palabra
            if(isalpha(intento_actual[j].letras_acertadas[i]))
                printf(" %s%c%s ║", GREEN, intento_actual[j].palabra[i], RESET_COLOR);
            else if(intento_actual[j].letras_acertadas[i] == '+')
                printf(" %s%c%s ║", YELLOW, intento_actual[j].palabra[i], RESET_COLOR);
            else
                printf(" %s%c%s ║", WHITE, intento_actual[j].palabra[i], RESET_COLOR);
        }
        printf("\n\t\t\t╠═══╬═══╬═══╬═══╬═══╣");
    }
    printf("\n\t\t\t║   ║   ║   ║   ║   ║");
    printf("\n\t\t\t╚═══╩═══╩═══╩═══╩═══╝\n\n");
}

// Verifica el intento actual comparándolo con la palabra secreta
int verificar(char palabra_secreta[], intento* intento_actual) {
    if (strcmp(intento_actual->palabra, palabra_secreta) == 0) 
        return 1;  // Palabra adivinada correctamente
    else {
        // Compara letras del intento con la palabra secreta
        for (int i = 0; i < LARGO_PALABRA; i++) {
            if (palabra_secreta[i] == intento_actual->palabra[i])
                intento_actual->letras_acertadas[i] = intento_actual->palabra[i];
            else {
                for (int j = 0; j < LARGO_PALABRA; j++) {
                    if (palabra_secreta[i] == intento_actual->palabra[j]){
                        intento_actual->letras_acertadas[j] = '+';
                        j = LARGO_PALABRA;
                    }
                }
            }
        }
        return 0;  // Aún no adivina
    }
}
