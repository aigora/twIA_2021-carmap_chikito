#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y)
{
	HANDLE mapa = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sistcart; //Sistema cartesiano con x e y 
	sistcart.X = x;
	sistcart.Y = y;
	SetConsoleCursorPosition(mapa, sistcart);


}

char(direccion);
int x = 60, y = 10;



int main(void)
{
	while (direccion != 'z')//Si se pulsa z se acaba el programa 

	{
		
		gotoxy(x, y); cout << ".";
		direccion = _getch();

		switch (direccion)
		{
		case 'e':x++;//mover en direccion este 
			break;
		case 'o':x--;//mover en direccion oeste 
			break;
		case 'n':y--;//mover en direccion norte
			break;
		case 's':y++;//mover en direccion sur
			break;
		default:
			break;
		}


	}

	return 0;



}








