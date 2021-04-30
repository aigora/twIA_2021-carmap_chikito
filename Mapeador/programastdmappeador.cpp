#include <stdio.h>
#include <windows.h>


void gotoxy(int x, int y)
{
	HANDLE mapa = GetStdHandle(STD_OUTPUT_HANDLE);//La utilizacion de gotoxy permite moverse por la pantalla 
	COORD sistcart;                              //para generar el mapa que imitara el robot.
	sistcart.X = x;
	sistcart.Y = y;
	SetConsoleCursorPosition(mapa, sistcart);

}

void VectorMovimiento(char m[], char dim);// vector que generara el movimiento 

void NumeroPulsaciones(int x1, int x2, int x3, int x4);// mide las pulsaciones de cada direccion en el co

typedef struct cont
{
	int a = 0, b = 0, c = 0, d = 0;  //Estos son los contadores para medir el numero de veces 
	                                // que sea pulsado cada direccion
}cont;





int main(void)
{
	int dim = 0;
	printf("Introduce el numero de rotaciones de autonomia que tendra el robot\n");//Aqui se introduce la autonomia 
	scanf_s("%d", &dim);                                                          //esto repercute en que luego el robot  
	                                                                             //no puede hacer mas movimientos
	cont t;
	char direccion, v[1000];
	int i, x = 60, y = 25; //punto de inicio en la pantalla 

	printf("Introduzca las letras para las direcciones\n");
	printf("La letra n para dirigirse hacia delante\n");
	printf("La letra s para dirigirse hacia atras\n");
	printf("La letra o para dirigirse hacia la izquierda\n");
	printf("La letra e para dirigirse hacia la derecha\n");
	printf("No olvide que si hace intro antes de completar toda la secuencia perdera una rotacion por cada vez que lo haga\n");
	

	gotoxy(x, y); printf("*");//El punto de inicio esta marcado con un asterisco para que se puede entender 
	gotoxy(0, 8);            //la direccion que toma el robot

    for(i=0;i<dim;i++)
	{


		scanf_s("%c", &direccion);


		if (direccion == 'n')
		{
			t.a++;
			gotoxy(x - t.c + t.d, y - t.a + t.b); printf(".");
			gotoxy(1 + t.c + t.d + t.a + t.b, 8);
			v[i] = 'n';
		}
		if (direccion == 's')
		{
			t.b++;
			gotoxy(x - t.c + t.d, y - t.a + t.b); printf(".");
			gotoxy(1 + t.c + t.d + t.a + t.b, 8);
			v[i] = 's';

		}

		if (direccion == 'o')
		{
			t.c++;
			gotoxy(x - t.c + t.d, y - t.a + t.b); printf(".");
			gotoxy(1 + t.c + t.d + t.a + t.b, 8);
			v[i] = 'o';
		}

		if (direccion == 'e')
		{
			t.d++;
			gotoxy(x - t.c + t.d, y - t.a + t.b); printf(".");
			gotoxy(1 + t.c + t.d + t.a + t.b, 8);
			v[i] = 'e';
		}

	}

	VectorMovimiento(v, dim); 
	NumeroPulsaciones(t.a, t.b, t.c, t.d);

}


void VectorMovimiento(char m[], char dim)
{
	int i=0;
	gotoxy(5, 60);
	printf("Generamos el vector movimiento\n");

	for (i = 0; i < dim; i++)
	{
		printf("direccion %c posicion del vector %d\n", m[i],i);

	}

}


void NumeroPulsaciones(int x1, int x2, int x3, int x4)
{
	printf("Numero de veces que sea pulsado el boton n es %d\n", x1);
	printf("Numero de veces que sea pulsado el vector s es %d\n",x2);
	printf("Numero de veces que sea pulsado el vector o es %d\n", x3);
	printf("Numero de veces que sea pulsado el vector e es %d\n", x4);
}




