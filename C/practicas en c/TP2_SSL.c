#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void ejercicio1(char *linea);
void ejercicio2(char *linea);
void ejercicio3(char *linea);
bool automataEj3(char *alfabeto,char *cadena);
bool perteneceAlAlfabeto(char elemento, char *alfabeto);
bool automata(int *i, char *alfabeto, char *palabra);

int main(int argc, char const *argv[])
{
    int caracter;
    size_t posicion = 0;
    size_t longitud = 10;
    char *linea = malloc(longitud * sizeof(char));
    if (linea == NULL)
    {
        printf("Error: No se pudo asignar memoria.\n");
        return -1;
    }
    memset(linea, '\0', sizeof(char) * 10);

    printf("Ingrese una cadena: ");
    while ((caracter = getc(stdin)) != '\n' && caracter != EOF) // leemos los caracteres ingresados por teclado
    {
        if (posicion + 1 == longitud) // pedimos mas memoria de forma dinamica
        {
            longitud = longitud + 10;
            void *aux = realloc(linea, longitud * sizeof(char));
            if (aux == NULL)
            {
                printf("Error: al asignar mas memoria para la cadena. ");
                return -1;
            }
            linea = aux;
            memset((linea + sizeof(char) * (posicion + 1)), '\0', 10 * sizeof(char));
        }
        linea[posicion] = (char)caracter; // agregamos el nuevo caracter a la cadena
        posicion++;
    }
    // aca ya se termino de ingresar la cadena completa.

    printf("cadena ingresada: %s \n", linea); // muestro los caracteres ingresados para verificar el correcto funcionamiento.

    int eleccion;
    printf("Que ejercicio desea Probar ( 1, 2, 3 ): ");
    scanf("%d", &eleccion);
    switch (eleccion)
    {
    case 1:
        ejercicio1(linea);
        break;
    case 2:
        ejercicio2(linea);
        break;
    case 3:
        ejercicio3(linea);
        break;
    default:
        printf("Eleccion invalida. Fin del Programa. ");
    }

    free(linea); // al finalizar liberamos toda la memoria reservada ( maldito C ).
    return 0;
}

void ejercicio1(char *cadena)
{ /*
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
    char alfabetoHexa[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f', '\0'};
    char alfabetoDec[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\0'};
    char alfabetoOct[] = {'1', '2', '3', '4', '5', '6', '7', '0', '\0'};
    int contadorDeDecimal = 0;
    int contadorDeOctal = 0;
    int contadorDeHexadecimal = 0;
    int contadorDeErrores = 0;
    int i = 0;

    while (cadena[i] != '\0') // comienzo del automata
    {
        bool flag = true;
        char C = cadena[i];
        if (C == '0')
        { // es Octal o Hexadecimal
            i++;

            if (C == 'x' || C == 'X') // es Hexadecimal
            {
                i++; // consumo el caracter x/X
                flag = automata(&i, alfabetoHexa, cadena);
                if (flag)
                {
                    contadorDeHexadecimal++; // la cadena se reconocio con exito (es una palabra)
                    if (cadena[i] == '@')   i++;  // saltea el '@' que indica el fin de la cadena
                    continue; // si todo sale bien sigo con la siguiente cadena
                }
            }
            else if (perteneceAlAlfabeto(cadena[i], alfabetoOct) || cadena[i] == '@' || cadena[i] == '\0')
            { // es octal
                if (cadena[i] != '@' && cadena[i] != '\0')
                    flag = automata(&i, alfabetoOct, cadena);
                if (flag)
                {
                    contadorDeOctal++; // la cadena se reconocio con exito (es una palabra)
                    if (cadena[i] == '@')   i++;  // saltea el '@' que indica el fin de la cadena
                    continue; // si todo sale bien sigo con la siguiente cadena
                }
            }
        }
        else if (C == '+' || C == '-' || perteneceAlAlfabeto(C, alfabetoDec)) // es decimal
        {
            if (!perteneceAlAlfabeto(C, alfabetoDec))
                i++; // si el primer caracter es + - se consume
            flag = automata(&i, alfabetoDec, cadena);
            if (flag)
            {
                contadorDeDecimal++; // la cadena se reconocio con exito (es una palabra).
                if (cadena[i] == '@')   i++;  // salteo el '@' que indica el fin de la cadena
                continue; // si todo sale bien sigo con la siguiente cadena.
            }
        }
        // se trata de un error o una cadena que no pertenece a ningun lenguaje
        contadorDeErrores++; // se aumenta el contador
        while (cadena[i] != '\0' && cadena[i] != '@')   i++; // se itera entre los caracteres hasta finalizar la cadena actual.   
        if (cadena[i] == '@')   i++; // se sigue con la siguiente cadena.
    }
    printf("Cantidad de Hexadecimales: %d. \nCantidad de Decimales: %d.\n", contadorDeHexadecimal, contadorDeDecimal);
    printf("Cantidad de Octales: %d. \nCantidad de Errores %d.\n", contadorDeOctal, contadorDeErrores);
}

bool perteneceAlAlfabeto(char elemento, char *alfabeto)
{

    int i = 0;
    while (alfabeto[i] != '\0')
    {
        if (elemento == alfabeto[i])
        {
            return true;
        }
        i++;
    }
    return false;
}

bool automata(int *i, char *alfabeto, char *cadena)
{

    if (!perteneceAlAlfabeto(cadena[*i], alfabeto))
        return false;
    while (cadena[*i] != '\0' && cadena[*i] != '@')
    {
        if (!perteneceAlAlfabeto(cadena[*i], alfabeto))
        {
            return false;
            break;
        }
        (*i)++;
    }
    return true;
}

void ejercicio2(char *cadena)
{ // Debe realizar una función que reciba un carácter numérico y retorne un número entero.
    // tener en cuenta que en la tabla ascii los numeros estan consecutivos y estan en la posicion del 48 (0) al 57 (9)
    int i = 0, numero = 0, j = 0;
    while (cadena[j] != '\0')
        j++;

    while (j > 0)
    {
        if (cadena[i] >= 48 && cadena[i] <= 57)
        {
            numero += (-48 + cadena[i]) * (pow(10, j - 1)); //
        }
        else
        {
            numero = -1; // en la cadena hay un digito invalido
            break;
        }
        i++;
        j--;
    }
    printf("numero ingresado: %d", numero);
}

void ejercicio3(char *cadena)
{   /*Ingresar una cadena que represente una operación simple con enteros decimales y obtener su resultado, se debe operar
    con +,- y *. Ejemplo = 3+4*7+3-5 = 29.
    Considerando que el alfabeto son los números decimales, signos +,- y * valide con un automata previo a la operación
    que dicha cadena que representa la operación pertenezca al lenguaje.
    */
    int i = 0;
    char alfabeto[] = {'1','2','3','4','5','6','7','8','9','0','*','-','+','\0'}; // alfabeto del lenguaje

    if(!automataEj3(alfabeto,cadena)) // verificamos que la cadena pertenece al lenguaje
    {
        printf("La cadena ingresada no pertenece al lenguaje");
        return;
    }
    int longitud = length(cadena) + 1; // la cadena auxiliar va a ser menor o igual tamaño a la original.
    char *cadenaAux = malloc(longitud * sizeof(char)); // reservamos memoria para la cadena auxiliar donde vamos a guardar los resultados parciales 
    while(cadena[i] != '\0')
    {
        
    }
    return;
}

bool automataEj3(char *alfabeto,char *cadena){
    int i = 0;    
    while(cadena[i] != '\0') // recorrer toda la cadena
    {
        if(!perteneceAlAlfabeto(cadena[i],alfabeto)) return false;
        char C = cadena[i];
        if( C == '*' || C == '+' || C== '-')
        {
            char C_sig = cadena[i+1]; 
            if( C_sig == '\0' || C_sig == '*' || C_sig == '+' || C_sig == '-' || i == 0) // no pueden haber operadores consecutivos, empezar con operador o terminar con uno
            {
                return false;
            }
        }
        i++;
    }
    return true;
}