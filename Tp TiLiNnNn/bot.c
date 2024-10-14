#include "bot.h"

int cumple_condiciones(char palabra_intento[], char letras_acertadas[], word *intento_actual) {
    for (int i = 0; i < LARGO_PALABRA; i++) {
        // Si la letra ya es considerada no permitida, devuelve 0
        if (strchr(intento_actual->letras_no_permitidas, intento_actual->palabra[i]) != NULL) {
            return 0;
        }
        else{
            if (isalpha(letras_acertadas[i]) && letras_acertadas[i] != intento_actual->palabra[i]) {
                return 0;
            } 
            else if (letras_acertadas[i] == '+') {
                int verificador = 0;
                // Letra correcta pero en la posición incorrecta
                for (int j = 0; j < LARGO_PALABRA; j++) {
                    if (palabra_intento[i] == intento_actual->palabra[j]) {
                        verificador = 1;
                        j = LARGO_PALABRA;  // Salir del bucle si se encontró
                    }
                }
                if (!verificador)
                    return 0;  
            }
            else
                intento_actual->letras_no_permitidas[strlen(intento_actual->letras_no_permitidas)] = intento_actual->palabra[i];
        }
    }
    return 1;  // Si todo está bien, retorna 1 (cumple condiciones)
}
