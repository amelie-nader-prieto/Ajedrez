#include <iostream>

#include "pieza.h"

#include "peon.h"
#include "dama.h"
#include "rey.h"
#include "torre.h"
#include "alfil.h"
#include "caballo.h"
#include "No_pieza.h"


#define FILA 10
#define COLUMNA 11

#include "Funciones_main.cpp"

static Pieza* Tablero[FILA][COLUMNA] = { nullptr };



void iniciar(Tipo tipo, Vector2D posicion)
{
	switch (tipo)
	{
	case D:
		Tablero[posicion.x][posicion.y] = new Dama(posicion.x, posicion.y);
		break;
	case P:
		Tablero[posicion.x][posicion.y] = new Peon(posicion.x, posicion.y);
		break;
	case T:
		Tablero[posicion.x][posicion.y] = new Torre(posicion.x, posicion.y);
		break;
	case C:
		Tablero[posicion.x][posicion.y] = new Caballo(posicion.x, posicion.y);
		break;
	case R:
		Tablero[posicion.x][posicion.y] = new Rey(posicion.x, posicion.y);
		break;
	case A:
		Tablero[posicion.x][posicion.y] = new Alfil(posicion.x, posicion.y);
		break;
	default:
		break;
	}
}


void cambio_casilla(Pieza pieza, Vector2D final) { ///ESTÁ MEDIO HECHA
	
	Vector2D inicio = pieza.GetPosicion();

	Tablero[inicio.x][inicio.y]= new No_pieza(inicio.x, inicio.y);
	

}




int main() 
{

	//Colocar los espacios donde puede haber piezas
	//Espacio_tablero(Tablero[FILA][COLUMNA]);
	for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			if (
				((j == 10 || j == 0) && (i == 4 || i == 5)) ||
				((j == 9 || j == 1) && (i == 4 || i == 5 || i == 3 || i == 6)) ||
				((j == 8 || j == 2) && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7)) ||
				((j == 7 || j == 3) && (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8)) ||
				(j == 4 || j == 5 || j == 6) )
			{
				Tablero[i][j] = new No_pieza(i, j);
			}

		}
	}

	
		//Establecer piezas en el tablero
		for (int i = 2; i <= 8;i++)
		{
			iniciar(P, {2,i});//creación peones
			
		}

		iniciar(T, {1,3});
		iniciar(C, { 1,4 });
		iniciar(A, { 1,5 });
		iniciar(C, { 1,6 });
		iniciar(T, { 1,7 });
		
		iniciar(R, { 0,4 });
		iniciar(A, { 0,5 });
		iniciar(D, { 0,6 });



	for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			if (Tablero[i][j])
				std::cout << "  " << Tablero[i][j]->GetTipo() << "  ";
			else
				std::cout << "     ";
		}
		std::cout << std::endl;
	}

	// Liberar la memoria al final del programa
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 11; ++j) {
			delete Tablero[i][j]; // Liberar la memoria de cada pieza
		}
	}

	return 0;
}

