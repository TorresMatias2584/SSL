#include<stdio.h>

int main() {

    FILE *salida;

    printf("hello world");

    salida=fopen("output.txt","w");

    fprintf(salida,"Hello World");

    fclose(salida);   

return 0;
}