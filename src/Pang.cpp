#include <iostream>
#include "LogicaAjedrez.h"

#define FILA 10
#define COLUMNA 11


//Esta funci�n hace que cuando se quiera iniciar una pieza se manda el tipo y direcci�n 
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
		Tablero[posicion.x][posicion.y] = new No_pieza(posicion.x, posicion.y);
		break;
	default:
		break;
	}
}

//En esta funci�n se mandar� la pieza y se dar� la direcci�n final 
void cambio_casilla(Pieza& pieza, Vector2D final) {

	// No permite acceder a casillas que se salgan del tablero o del rombo
	if (no_se_usa(final.x, final.y) ||
		(final.x < 0 || final.y < 0 || final.x >= COLUMNA || final.y >= FILA)) {
		return void{};
	}

	bool movimiento_posible = false;

	// No permite acceder a casillas que no est�n entre los movimientos permitidos de la pieza
	for (const auto& p : obtener_posibles_movimientos(pieza)) {
		if (final.x == p.row && final.y == p.col) {
			movimiento_posible = true;
			break;
		}
	}

	if (!movimiento_posible)return void{};

	Vector2D inicio = pieza.GetPosicion();

	// la casilla en la que estabas se queda vac�a
	iniciar(no_hay, { inicio });
	// vuelve a crear la pieza en la posici�n final
	iniciar(pieza.GetTipo(), { final });

}

// BUCLE PARA DIBUJAR EL TABLERO
void dibujar_tablero() {
	/*for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			if (Tablero[i][j])
				std::cout << "[" << Tablero[i][j]->GetTipo() << "]";

			else
				std::cout << "   ";
		}
		std::cout << std::endl;
	}*/

	
	for (auto i = 0; i < FILA; i++) {
		for (auto j = 0; j < COLUMNA; j++) {
			if (Tablero[i][j])
				std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
			else
				std::cout << "   ";
		}
		std::cout << ' ' << FILA - i << std::endl;
	}

	std::cout << " a  b  c  d  e  f  g  h  i  j  k" << std::endl;

}

int main() 
{

	//Colocar los espacios donde puede haber piezas
	//Espacio_tablero(Tablero[FILA][COLUMNA]);
	for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			// CASILLAS EN LAS QUE INICIALMENTE NO HAY PIEZAS
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
			iniciar(P, {2,i});//creaci�n peones
			
		}

		//Creaci�n de las fichas de la fila 2
		//  T  C  A  C  T
		iniciar(T, { 1,3 });
		iniciar(C, { 1,4 });
		iniciar(A, { 1,5 });
		iniciar(C, { 1,6 });
		iniciar(T, { 1,7 });
		
		//Creaci�n de las fichas de la fila 2
		//  R  C  D
		iniciar(R, { 0,4 });
		iniciar(A, { 0,5 });
		iniciar(D, { 0,6 });

		// dibujamos el tablero
		dibujar_tablero();
		std::cout << "\n\n";


		//Prueba de cambio de casilla
		// movemos el pe�n
		cambio_casilla(*Tablero[2][4], {3,4});
		dibujar_tablero();
		std::cout << "\n\n\n";

		// probamos a mover m�s piezas
		cambio_casilla(*Tablero[2][5], {
			obtener_posibles_movimientos(*Tablero[2][5])[0].row,obtener_posibles_movimientos(*Tablero[2][5])[0].col
			});
		dibujar_tablero();
		std::cout << "\n\n\n";

		cambio_casilla(*Tablero[1][5], {
			obtener_posibles_movimientos(*Tablero[1][5])[1].row,obtener_posibles_movimientos(*Tablero[1][5])[1].col
			});
		dibujar_tablero();
		std::cout << "\n\n\n";


	// Liberar la memoria al final del programa
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 11; ++j) {
			delete Tablero[i][j]; // Liberar la memoria de cada pieza
		}
	}

	return 0;
}

