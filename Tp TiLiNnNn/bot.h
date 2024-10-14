#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "ed1.h"


#define MAX_INTENTOS 6
#define LARGO_PALABRA 5



int cumple_condiciones(char palabra_intento[], char letras_acertadas[], word *intento_actual);

