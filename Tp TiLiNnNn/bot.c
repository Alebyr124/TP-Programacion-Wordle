#include "bot.h"

int cumple_condiciones(char palabra_intento[], char letras_acertadas[], int letras_no_permitidas[], word *intento_actual) {
    int contador_letras[LARGO_PALABRA]; // Para contar cuántas veces se repite cada letra en la palabra actual
    for(int i = 0; i < LARGO_PALABRA; i++)
        contador_letras[i] = 0;

    for (int i = 0; i < LARGO_PALABRA; i++) {
        char letra_actual = intento_actual->palabra[i];
        
        // Evitar usar letras que no están permitidas
        if (letras_no_permitidas[letra_actual - 'a']) {
            return 0;  // Esta letra no está permitida
        }
        
        // Verificar si las letras acertadas están en la posición correcta
        if (isalpha(letras_acertadas[i])) {
            // Si la letra no coincide con la de la palabra actual, no se cumple
            if (letras_acertadas[i] != letra_actual) {
                return 0;
            }
        } 
        // Si la letra está en la palabra, pero en otra posición
        else if (letras_acertadas[i] == '+') {
            int encontrado = 0;
            for (int j = 0; j < LARGO_PALABRA; j++) {
                if (palabra_intento[i] == intento_actual->palabra[j] && i != j) {
                    encontrado = 1;  // La letra está en la palabra pero no en la misma posición
                    break;
                }
            }
            if (!encontrado) {
                return 0;  // Si la letra no se encuentra en otra posición, no se cumple
            }
        }

        // Contar cuántas veces se repite cada letra en la palabra secreta
        contador_letras[letra_actual - 'a']++;
    }

    // Controlar repeticiones de letras
    for (int i = 0; i < LARGO_PALABRA; i++) {
        char letra_actual = palabra_intento[i];
        int repeticiones_palabra_secreta = 0;
        for (int j = 0; j < LARGO_PALABRA; j++) {
            if (palabra_intento[j] == letra_actual) {
                repeticiones_palabra_secreta++;
            }
        }
        // Si la letra se repite más veces en la palabra que en la palabra secreta
        if (repeticiones_palabra_secreta > contador_letras[letra_actual - 'a']) {
            return 0;
        }
    }

    return 1;  // Cumple las condiciones si llega aquí
}




int tiene_repeticiones(char palabra[], char letra) {
    int contador = 0;  // Inicializa el contador en 0
    for (int i = 0; palabra[i] != '\0'; i++) {
        if (palabra[i] == letra) {
            contador++;  
        }
        
    }
    return (contador > 1) ? 1 : 0;
}