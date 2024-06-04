#pragma once
#include "GLTablero.h"
#include "ETSIDI.h"


class Coordinador
{
	enum Estado { INICIO, OPCIONES, JUEGO, GAMEOBER, FIN} estado=JUEGO;
	enum Tipo_Tablero{TIPO1, TIPO2, TIPO3}graf_tablero;
	GLTablero mundo_grafico;

public:
	void tecla_especial(unsigned char key);
	void tecla(unsigned char key);
	void mueve();
	void dibuja();
	void MouseBottom(int b, int state, int x, int y);
};