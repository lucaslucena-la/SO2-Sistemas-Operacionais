#include "defs.h"
#include <stdarg.h>



int perimetro(int lados, ...){//aceita um numero variado de argumentos
    va_list ap;

    va_start(ap, lados);

    int perimetro = 0;
    for(int i = 0; i < lados; i++ ){
        perimetro += va_arg(ap, int); 
    }

    return perimetro;
}