#include "IA.h"

void IA::inicializar(Tablero& tab) {
	// recorro los vecotres de piezas y guardo sus direcciones en los vectores piezas_propias y piezas_rival
	for (auto &i : tab.getTurno() == W ? tab.get_piezas_neg() : tab.get_piezas_bla())
		piezas_propias.push_back(i);
	for (auto &i : tab.getTurno() == W ? tab.get_piezas_bla() : tab.get_piezas_neg())
		piezas_rival.push_back(i);
}

void IA::mover_rndm(Tablero& tab) {
	cout << "\nTURNO DE LA MÁQUINA\n";
	piezas_propias.clear();
	for (auto& i : tab.get_piezas_neg())
		piezas_propias.push_back(i);
	fin_turno = false;
	while (!fin_turno) {
		// Elige una peiza al azar 
		Pieza pieza = piezas_propias[GetRandom(piezas_propias.size())];

		cout << " " << pieza << " ";

		vector<Vector2D>posibles_mov = obtener_movimientos_legales(pieza.GetPosicion(), tab);
		//if (puede_mover(pieza, posibles_mov, tab)) {
		//	// si puede, mueve la pieza a una casilla al azar
		//	mover_pieza(pieza.GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tab);
		//	fin_turno = true;
		//}
		//else cout << "  esa pieza no se puede mover crack xdxd  ";
		if (posibles_mov.size() == 0) {
			cout << " esa pieza no se puede mover crack xdxd ";
		}
		else {
			auto casilla_destino = posibles_mov[GetRandom(posibles_mov.size())];
			mover_pieza(pieza.GetPosicion(), casilla_destino, tab);
			fin_turno = true;
		}
	}
	piezas_propias.clear();
}

bool IA::puede_mover(Pieza& pieza, vector<Vector2D> &posibles_mov, Tablero& tab)
{
	posibles_mov = obtener_posibles_movimientos(pieza.GetPosicion(), tab);
	if (posibles_mov.size() == 0) return false;
	else {
		cout << "ha retornado true";
		return true;
	}
}
