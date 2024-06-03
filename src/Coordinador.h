#pragma once
//#include "GLTablero.h"
#include "ETSIDI.h"
#include <iostream>
using std::cout;
using std::endl;


class Coordinador
{
	//GLTablero mundo_grafico;
	enum Estado { MENU1, MENU2, GRAFICOS,EXPLICACION, JUEGO, PAUSA, GAMEOVER, FIN} estado=MENU1;
	enum Tipo_Tablero{classic=1, starwors, animal}graficas_tablero=classic;
	enum Modalida { maquina, jugadores }modalidad = jugadores;
	enum Volumen {ON, OFF} volumen=ON;
public:
	//GLTablero mundo_grafico;
	//Coordinador();
	void iniciar();
	/*virtual ~Coordinador();
	void tecla_especial(unsigned char key);*/
	void tecla(unsigned char key);
//	void mueve();
	void dibuja();
//	void MouseBottom(int x, int y, int button, bool down, Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado);
	void musica();
};

