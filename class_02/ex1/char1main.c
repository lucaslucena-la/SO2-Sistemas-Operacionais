#include <stdio.h>




char first_char(char *s);

int main() {
    char *s ="uma string em memoria";
   //s = 0x1;
    //*s = "B";
    char c = first_char(s);
    printf("%c eh o primeiro caractere de: %s\n",c, s);
    return 0;
}