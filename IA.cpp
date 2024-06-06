#include "IA.h"

void IA::inicializar(Tablero& tab) {
	// recorro los vecotres de piezas y guardo sus direcciones en los vectores piezas_propias y piezas_rival
	for (auto i : tab.getTurno() == W ? tab.get_piezas_neg() : tab.get_piezas_bla())
		piezas_propias.push_back(&i);
	for (auto i : tab.getTurno() == W ? tab.get_piezas_bla() : tab.get_piezas_neg())
		piezas_rival.push_back(&i);
}

void IA::mover_rndm(Tablero& tab) {
	for (auto i : tab.get_piezas_neg())
		piezas_propias.push_back(&i);
	Pieza* pieza = piezas_propias[GetRandom(piezas_propias.size())];
	vector<Vector2D>posibles_mov;
	if (puede_mover(*pieza, posibles_mov, tab)) {
		mover_pieza(pieza->GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tab);
		fin_turno = true;
	}
}

bool IA::puede_mover(Pieza& pieza, vector<Vector2D> posibles_mov, Tablero& tab)
{
	posibles_mov = obtener_posibles_movimientos(pieza.GetPosicion(), tab);
	if (posibles_mov.size() == 0) return false;
	else return true;
}
