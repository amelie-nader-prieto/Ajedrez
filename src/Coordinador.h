#pragma once
#include "GLTablero.h"
#include "ETSIDI.h"


class Coordinador
{
	//GLTablero mundo_grafico;
	enum Estado { INICIO, OPCIONES, JUEGO, PAUSA, GAMEOVER, FIN} estado=INICIO;
	enum Tipo_Tablero{TIPO1=1, TIPO2, TIPO3}graf_tablero=TIPO1;
	

public:
	GLTablero mundo_grafico;
	//Coordinador();
	void iniciar();
	virtual ~Coordinador();
	void tecla_especial(unsigned char key);
	void tecla(unsigned char key);
	void mueve();
	void dibuja();
	void MouseBottom(int x, int y, int button, bool down, Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado);
};

