#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char codigo[120];
    char A[]={"boton1"};
    int contador=0;
    char*tok;
    printf("Introduce el codigo:\n");
    gets_s(codigo);
    fflush(stdin);

    printf("Ahora veremos el numero de veces que se repite el boton1\n");
    tok=strtok(A,",.;:")
    while(tok!=NULL)
    {
        if (strcmp(tok,"boton1")===0)
        {
            contador++;
        }
        tok=strtok(NULL,".,:;");
    }
    printf("Numero de veces que se ha pulsado en el codigo el boton 1 es %d\n",contador);
    return 0;
}
