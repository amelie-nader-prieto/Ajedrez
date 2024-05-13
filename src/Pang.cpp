#include "LogicaAjedrez.h"

int main(){
	// vamos a crear un tablero para ver si funciona bien
	Tablero tab;

	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			// vamos a comprobar si est�n bien las posiciones de memoria
			if (tab.tablero[i][j])
			{
				cout << (tab.tablero[i][j]->GetPosicion()) << ":\t";
				cout << tab.tablero[i][j] << '\n';
			}
		}
		cout << '\n';
	}

	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			// comprobamos si se han creado las piezas correctamente
			if (tab.tablero[i][j]) {
				if (tab.tablero[i][j]->GetTipo() != no_hay){
					cout << "(" << i << ',' << j << ")" << '\t';
					cout << (*tab.tablero[i][j]) << '\n';
				}
			}
		}
	}

	// por favor enlazador no me traiciones
	dibujar(tab);

}

//#define FILA 10
//#define COLUMNA 11
//
//bool rivales(Pieza& p1, Pieza& p2) {
//	if (p1.GetTipo() == no_hay || p2.GetTipo() == no_hay) return false;
//	else return(
//		(p1.GetJugador() == B && p2.GetJugador() == W) ||
//		(p1.GetJugador() == W && p2.GetJugador() == B) ?
//		true : false);
//}
//
//// BUCLE PARA DIBUJAR EL TABLERO
//void dibujar_tablero() {
//	
//	for (auto i = 0; i < FILA; i++) {
//		for (auto j = 0; j < COLUMNA; j++) {
//			if (Tablero[i][j])
//				std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
//			else
//				std::cout << "   ";
//		}
//		std::cout << ' ' << FILA - i << std::endl;
//	}
//
//	std::cout << " a  b  c  d  e  f  g  h  i  j  k" << std::endl;
//
//}
//
//// Dibujar seg�n el color
//void dibujar_tablero(Jugador color) {
//
//	for (auto i = 0; i < FILA; i++) {
//		for (auto j = 0; j < COLUMNA; j++) {
//			if (Tablero[i][j]) {
//				if (Tablero[i][j]->GetJugador() == color)
//					std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
//				else std::cout << "[ ]";
//			}
//			else
//				std::cout << "   ";
//		}
//		std::cout << ' ' << FILA - i;
//		std::cout << '\n';
//	}
//
//	std::cout << " a  b  c  d  e  f  g  h  i  j  k" << std::endl;
//
//}
//
//// Dibujar las casillas posibles para una pieza
//void dibujar_posibles_movimientos(Pieza _p) {
//	
//	dibujar_tablero();
//
//	vector<Casilla>posibles_movimientos = obtener_posibles_movimientos(_p);
//	bool posible = false;
//
//	std::cout << "\n\tPOSIBLES MOVIMIENTOS ("
//		<< _p.GetTipo() << _p.GetJugador()
//		<< "):\n";
//	std::cout << "([.] - puedes mover\t[x] - puedes capturar)\n\n";
//
//	for (auto i = 0; i < FILA; i++) {
//		for (auto j = 0; j < COLUMNA; j++) {
//
//			for (const auto& p : posibles_movimientos) {
//				if (p.row == i && p.col == j) {
//					posible = true;
//					break;
//				}
//			}
//
//			// casillas que no se usan - no las dibuja
//			if (no_se_usa(i, j)) std::cout << "   ";
//
//			// casillas con posible captura
//			/*else if (posible && (Tablero[i][j]->GetJugador() != _p.GetJugador()))
//				std::cout << "[x]";*/
//			else if (posible && rivales(*Tablero[i][j], _p)) std::cout << "[x]";
//
//			else if (posible && !rivales(*Tablero[i][j], _p)) std::cout << "[.]";
//
//			// casilla en la que est�s
//			else if (Tablero[i][j]->GetFila() == _p.GetFila() && Tablero[i][j]->GetColumna() == _p.GetColumna())
//				std::cout << "[" << _p.GetTipo() << "]";
//
//			else std::cout << "[ ]";
//			// casillas con posible movimiento
//			//else std::cout << (posible ? "[.]" : "[ ]");
//
//			posible = false;
//			
//		}
//		std::cout << ' ' << FILA - i;
//		std::cout << '\n';
//	}
//
//	std::cout << " a  b  c  d  e  f  g  h  i  j  k" << std::endl;
//
//}
//
//int main() 
//{
//
//	//Colocar los espacios donde puede haber piezas
//	//Espacio_tablero(Tablero[FILA][COLUMNA]);
//	for (auto i = 9; i >= 0; i--)
//	{
//		for (auto j = 10; j >= 0; j--)
//		{
//			// CASILLAS EN LAS QUE INICIALMENTE NO HAY PIEZAS
//			if (
//				((j == 10 || j == 0) && (i == 4 || i == 5)) ||
//				((j == 9 || j == 1) && (i == 4 || i == 5 || i == 3 || i == 6)) ||
//				((j == 8 || j == 2) && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7)) ||
//				((j == 7 || j == 3) && (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8)) ||
//				(j == 4 || j == 5 || j == 6) )
//			{
//				Tablero[i][j] = new No_pieza(i, j);
//			}
//
//		}
//	}
//
//	iniciar_tablero();
//
//	//dibujar_tablero();
//	//std::cout << "\n\n\n";
//
//	//	//Prueba de cambio de casilla
//	//	// movemos el pe�n
//	//cambio_casilla(*Tablero[2][4], {3,4});
//	//dibujar_tablero();
//	//std::cout << "\n\n\n";
//
//	//	// probamos a mover m�s piezas
//	//cambio_casilla(*Tablero[2][5], {
//	//	obtener_posibles_movimientos(*Tablero[2][5])[0].row,
//	//	obtener_posibles_movimientos(*Tablero[2][5])[0].col
//	//	});
//	//dibujar_tablero();
//	//std::cout << "\n\n\n";
//
//	//cambio_casilla(*Tablero[1][5], {
//	//	obtener_posibles_movimientos(*Tablero[1][5])[2].row,
//	//	obtener_posibles_movimientos(*Tablero[1][5])[2].col
//	//	});
//	//dibujar_tablero();
//	//
//
//	int op_jugador = 0, op_pieza = 0, op_casilla_destino = 0;
//	vector<Pieza>tus_piezas{};
//	vector<Casilla>posibles_destinos{};
//
//	// ELEGIR JUGADOR
//	do {
//		std::cout << "\nElige jugador\n1. blanco\n2. negro\n";
//		std::cin >> op_jugador;
//	} while (!(op_jugador == 1 || op_jugador == 2));
//
//	switch (op_jugador) {
//	case 1:tus_piezas = piezas_bla; /*std::cout << "\n\nBLANCO\n"; dibujar_tablero(W);*/ break;
//	case 2:tus_piezas = piezas_neg; /*std::cout << "\n\nNEGRO\n"; dibujar_tablero(B);*/ break;
//	default:break;
//	}
//
//	while(1) {
//
//		op_pieza = 0; op_casilla_destino = 0;
//		posibles_destinos.clear();
//
//		std::cout << "\n";
//		dibujar_tablero();
//		std::cout << "\n";
//
//		std::cout << "\ntus piezas son:\n";
//		auto i = 1;
//		for (auto& p : tus_piezas) {
//			std::cout << i << ". ";
//			std::cout << p.GetTipo() << p.GetJugador() << " (" << obtener_casilla(p) << ") ";
//			std::cout << "  ";
//			i++;
//		}
//
//		// ELEGIR PIEZA
//		std::cout << "\nelige pieza\n   (0 para salir)\n";
//		do {
//			std::cin >> op_pieza;
//			if (op_pieza == 0)break;
//			
//			// avisos en caso de opci�n no v�lida
//			if (op_pieza > tus_piezas.size()) {
//				std::cout << "   CABRON ELIGE UNA PIEZA DE LAS QUE TIENES  " << '\n';
//				//op_pieza = 0;
//				continue;
//			}
//			if (obtener_posibles_movimientos(tus_piezas.at(op_pieza - 1)).size() == 0) {
//				std::cout << "   (esa pieza no se puede mover, porfi elige otra)  " << '\n';
//				//op_pieza = 0;
//				continue;
//			}
//			
//
//		} while (op_pieza <= 0 || op_pieza > tus_piezas.size() ||
//			obtener_posibles_movimientos(tus_piezas.at(op_pieza - 1)).size() == 0); // si no puedes moverla no te deja seleccionarla
//
//		// 0 para salir
//		if (op_pieza == 0)break;
//
//		posibles_destinos = obtener_posibles_movimientos(tus_piezas.at(op_pieza - 1));
//
//		dibujar_posibles_movimientos(tus_piezas.at(op_pieza - 1));
//		std::cout << "\n\n";
//		std::cout << "puedes moverte a:\n";
//
//		i = 1;
//		for (auto& p : posibles_destinos) {
//			std::cout << i << ". ";
//			std::cout << "(" << p << ")  ";
//			i++;
//		}
//		std::cout << '\n';
//
//		// ELEGIR CASILLA DE DESTINO
//		do {
//			std::cin >> op_casilla_destino;
//
//		} while (op_casilla_destino <= 0 || op_casilla_destino > posibles_destinos.size());
//
//		//Vector2D destino = { posibles_destinos.at(op_casilla_destino - 1).row,posibles_destinos.at(op_casilla_destino - 1).col };
//
//		// MOVER PIEZA A LA CASILLA DE DESTINO
//		cambio_casilla(tus_piezas.at(op_pieza - 1),
//			{ posibles_destinos.at(op_casilla_destino - 1).row,posibles_destinos.at(op_casilla_destino - 1).col });
//
//		/*std::cout << "\n\n" << tus_piezas.at(op_pieza - 1).GetTipo() << tus_piezas.at(op_pieza - 1).GetJugador() <<
//			" movido a " << posibles_destinos.at(op_casilla_destino - 1) << '\n';*/
//
//		std::cout << "\n\n\n\t\t --------------------------------------------- \n\n\n";
//
//	}
//
//	std::cout << "\nok hasta luego\n";
//
//	// Liberar la memoria al final del programa
//	for (int i = 0; i < 10; ++i) {
//		for (int j = 0; j < 11; ++j) {
//			delete Tablero[i][j]; // Liberar la memoria de cada pieza
//		}
//	}
//
//	return 0;
//}
