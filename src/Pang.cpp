#include <iostream>

#include "pieza.h"

#include "peon.h"
#include "dama.h"
#include "rey.h"
#include "torre.h"
#include "alfil.h"
#include "caballo.h"
#include "No_pieza.h"

#include "Casilla.h"

#define FILA 10
#define COLUMNA 11

//#include "Funciones_main.cpp"

static Pieza* Tablero[FILA][COLUMNA] = { nullptr };


//Esta función hace que cuando se quiera iniciar una pieza se manda el tipo y dirección 
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
	case no_hay:
		Tablero[posicion.x][posicion.y] = new No_pieza (posicion.x, posicion.y);
		break;

	default:
		break;
	}
}

//En esta función se mandará la pieza y se dará la dirección final 
void cambio_casilla(Pieza& pieza, Vector2D final) { 
	
	Vector2D inicio = pieza.GetPosicion();

	iniciar(no_hay, { inicio });
	 
	iniciar(pieza.GetTipo(), {final});
	

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

		//Creación de las fichas de la fila 2
		//  T  C  A  C  T
		iniciar(T, {1,3});
		iniciar(C, { 1,4 });
		iniciar(A, { 1,5 });
		iniciar(C, { 1,6 });
		iniciar(T, { 1,7 });
		
		//Creación de las fichas de la fila 2
		//  R  C  D
		iniciar(R, { 0,4 });
		iniciar(A, { 0,5 });
		iniciar(D, { 0,6 });



		//Prueba de cambio de casilla
		cambio_casilla(*Tablero[2][4], {3,4});


	for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			if (Tablero[i][j])
				std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
			else
				std::cout << "   ";
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

