#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void ejercicio1(char *linea);
void ejercicio2(char *linea);
bool perteneceAlAlfabeto(char elemento, char *alfabeto);

int main(int argc, char const *argv[])
{   
    int caracter;
    size_t posicion = 0; 
    size_t longitud = 10;
    char *linea = malloc(longitud * sizeof(char));
    if (linea == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return -1;
    }
    memset(linea,'\0',sizeof(char)*10);

    printf("Ingrese una cadena: ");
    while ((caracter = getc(stdin)) != '\n' && caracter != EOF) // leemos los caracteres ingresados por teclado
    {   
        if(posicion + 1 == longitud) // pedimos mas memoria de forma dinamica
        {
            longitud = longitud + 10;
            void *aux = realloc(linea,longitud*sizeof(char));
            if(aux==NULL){
                printf("Error: al asignar mas memoria para la cadena. ");
                return -1;
            }
            linea = aux;
            memset((linea + sizeof(char)*(posicion+1)),'\0',10*sizeof(char));
        }
        linea[posicion] = (char)caracter; // agregamos el nuevo caracter a la cadena
        posicion++;
    }
    // aca ya se termino de ingresar la cadena completa.

    printf("cadena ingresada: %s \n", linea); // muestro los caracteres ingresados para verificar el correcto funcionamiento.

    int eleccion;
    printf("Que ejercicio desea Probar ( 1, 2, 3 ): ");
    scanf("%d",&eleccion);
    switch (eleccion)
    {
    case 1: 
        ejercicio1(linea);
        break;
    case 2: break;
    case 3: break;
    default:
        printf("Eleccion invalida. Fin del Programa. ");
    }

    free(linea); // al finalizar liberamos toda la memoria reservada ( maldito C ).
    return 0;
}

void ejercicio1(char *linea)
{   /*
    Dada una cadena que contenga varios números que pueden ser decimales, octales o hexadecimales,
    con o sin signo para el caso de los decimales, separados por el carácter ‘@’ ,
    reconocer los tres grupos de constantes enteras, indicando si
    hubo un error léxico , en caso de ser correcto contar la cantidad de cada grupo.
    */
    // Decimal -> 0-9 || ± 0-9
    // Octal -> 0-7
    // Hexadecimal -> 0x 0-F
    // si empieza con signo o numero del 1-9 entonces es decimal
    // si empieza con 0 entonces es octal
    // si empieza con 0x entonces es hexadecimal
    char alfabetoHexa[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F','a','b','c','d','e','f','\0'};
    char alfabetoDec[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0','\0'};
    char alfabetoOct[] = {'1', '2', '3', '4', '5', '6', '7', '0','\0'};
    int contadorDeDecimal = 0; 
    int contadorDeOctal = 0;
    int contadorDeHexadecimal = 0;
    int contadorDeErrores = 0;
    int i = 0;

    while(linea[i]!='\0')
    {
        bool flag = true;
        if(linea[i] == '0'){ // es Octal o Hexadecimal
            i++;

            if(linea[i] == 'x' || linea[i] == 'X') // es Hexadecimal
            {
                i++; // consumo el caracter x/X
                if(!perteneceAlAlfabeto(linea[i], alfabetoHexa)) flag = false;
                while(flag && linea[i] != '\0' && linea[i] != '@')
                {
                    if(!perteneceAlAlfabeto(linea[i],alfabetoHexa))
                    {
                        flag = false;
                        break;
                    }
                    i++;
                }
                if(flag){
                    contadorDeHexadecimal++; // la cadena se reconocio con exito (es una palabra)
                    if(linea[i] == '@') i++; // saltea el '@' que indica el fin de la cadena
                    continue; // si todo sale bien sigo con la siguiente cadena 
                }
            }
            else if(perteneceAlAlfabeto(linea[i],alfabetoOct) || linea[i] == '@' || linea[i] == '\0'){ // es octal
                while(linea[i] != '\0' && linea[i] != '@')
                {
                    if(!perteneceAlAlfabeto(linea[i],alfabetoOct))
                    {
                        flag = false;
                        break;
                    }
                    i++;
                }
                if(flag){
                    contadorDeOctal++; // la cadena se reconocio con exito (es una palabra)
                    if(linea[i] == '@') i++; // saltea el '@' que indica el fin de la cadena
                    continue; // si todo sale bien sigo con la siguiente cadena 
                }
            }
        }
        else if(linea[i] == '+' || linea[i] == '-' || perteneceAlAlfabeto(linea[i],alfabetoDec)) // es decimal
        {
            if(!perteneceAlAlfabeto(linea[i],alfabetoDec)) i++; // si el primer caracter es + - se consume
            if(!perteneceAlAlfabeto(linea[i],alfabetoDec)) flag=false;
            while(flag && linea[i] != '\0' && linea[i] != '@')
            {
                if(!perteneceAlAlfabeto(linea[i],alfabetoDec))
                {
                    flag = false;
                    break;
                }
                i++;
            }
            if(flag) {
            contadorDeDecimal++; // la cadena se reconocio con exito (es una palabra).
            if(linea[i] == '@') i++; // salteo el '@' que indica el fin de la cadena
            continue; // si todo sale bien sigo con la siguiente cadena.
            }
        }
        // se trata de un error o una cadena que no pertenece a ningun lenguaje
        contadorDeErrores++; // se aumenta el contador
        while(linea[i] != '\0' && linea[i] != '@') {i++;} // se itera entre los caracteres hasta finalizar la cadena actual.
        if(linea[i] == '@') i++; // se sigue con la siguiente cadena.
    }
    printf("Cantidad de Hexadecimales: %d. \nCantidad de Decimales: %d.\n",contadorDeHexadecimal,contadorDeDecimal);
    printf("Cantidad de Octales: %d. \nCantidad de Errores %d.\n",contadorDeOctal,contadorDeErrores);
}

void ejercicio2(char *linea)
{
    // ejercicio 2
}

bool perteneceAlAlfabeto(char elemento, char *alfabeto){
    
    int i=0;
    while(alfabeto[i] != '\0'){
        if(elemento == alfabeto[i]){
            return true;
        }
        i++;
    }
    return false;
}