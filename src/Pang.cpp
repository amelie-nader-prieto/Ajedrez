#include <iostream>
#include "LogicaAjedrez.h"

#define FILA 10
#define COLUMNA 11

// BUCLE PARA DIBUJAR EL TABLERO
void dibujar_tablero() {
	
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

// Dibujar según el color
void dibujar_tablero(Jugador color) {

	for (auto i = 0; i < FILA; i++) {
		for (auto j = 0; j < COLUMNA; j++) {
			if (Tablero[i][j]) {
				if (Tablero[i][j]->GetJugador() == color)
					std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
				else std::cout << "[ ]";
			}
			else
				std::cout << "   ";
		}
		std::cout << ' ' << FILA - i;
		std::cout << '\n';
	}

	std::cout << " a  b  c  d  e  f  g  h  i  j  k" << std::endl;

}

// Dibujar las casillas posibles para una pieza
void dibujar_posibles_movimientos(Pieza _p) {
	
	dibujar_tablero();

	vector<Casilla>posibles_movimientos = obtener_posibles_movimientos(_p);
	bool posible = false;

	std::cout << "\n\tPOSIBLES MOVIMIENTOS ("
		<< _p.GetTipo() << _p.GetJugador()
		<< "):\n";
	std::cout << "([.] - puedes mover\t[x] - puedes capturar)\n\n";

	for (auto i = 0; i < FILA; i++) {
		for (auto j = 0; j < COLUMNA; j++) {

			for (const auto& p : posibles_movimientos) {
				if (p.row == i && p.col == j) {
					posible = true;
					break;
				}
			}

			if (no_se_usa(i, j)) std::cout << "   ";

			else if (posible && (Tablero[i][j]->GetJugador() != _p.GetJugador()))
				std::cout << "[x]";

			else if (Tablero[i][j]->GetFila() == _p.GetFila() && Tablero[i][j]->GetColumna() == _p.GetColumna())
				std::cout << "[" << _p.GetTipo() << "]";

			else std::cout << (posible ? "[.]" : "[ ]");

			posible = false;
			
		}
		std::cout << ' ' << FILA - i;
		std::cout << '\n';
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

	iniciar_tablero();

	dibujar_tablero();
	std::cout << "\n\n\n";

		//Prueba de cambio de casilla
		// movemos el peón
	cambio_casilla(*Tablero[2][4], {3,4});
	dibujar_tablero();
	std::cout << "\n\n\n";

		// probamos a mover más piezas
	cambio_casilla(*Tablero[2][5], {
		obtener_posibles_movimientos(*Tablero[2][5])[0].row,
		obtener_posibles_movimientos(*Tablero[2][5])[0].col
		});
	dibujar_tablero();
	std::cout << "\n\n\n";

	cambio_casilla(*Tablero[1][5], {
		obtener_posibles_movimientos(*Tablero[1][5])[2].row,
		obtener_posibles_movimientos(*Tablero[1][5])[2].col
		});
	dibujar_tablero();
	std::cout << "\n\n\n";

	std::cout << "\n\n\n\n";

	int op = 0;
	do {
		std::cout << "\n¿qué jugador eres?\n1. blanco\n2. negro\n";
		std::cin >> op;
	} while (!(op == 1 || op == 2));

	vector<Pieza>tus_piezas{};

	switch (op) {
	case 1:tus_piezas = piezas_bla; dibujar_tablero(W); break;
	case 2:tus_piezas = piezas_neg; dibujar_tablero(B); break;
	default:break;
	}

	std::cout << "\ntus piezas son:\n";
	auto i = 1;
	for (auto& p : tus_piezas) {
		std::cout << i << ". ";
		std::cout << p.GetTipo();
		std::cout << p.GetJugador();
		std::cout << '\n';
		i++;
	}

	std::cout << "\nelige una\n";
	op = 0;
	do {
		std::cin >> op;
	} while (op<=0 || op>tus_piezas.size());

	dibujar_posibles_movimientos(tus_piezas.at(op - 1));
	std::cout << "\n\n";
	std::cout << "puedes moverte a:\n";
	for (auto& p : obtener_posibles_movimientos(tus_piezas.at(op - 1))) {
		std::cout << "   (" << p << ") ";
	}
	std::cout << '\n';

	// Liberar la memoria al final del programa
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 11; ++j) {
			delete Tablero[i][j]; // Liberar la memoria de cada pieza
		}
	}

	return 0;
}
