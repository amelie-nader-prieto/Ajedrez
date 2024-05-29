#include "Coordinador.h"



void Coordinador::dibuja()
{
	switch (estado) {
	case INICIO:
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("Pang 1.2", -5, 8);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("PULSE LA TECLA -E- PARA EMPEZAR", -5, 7);
		ETSIDI::printxy("PULSE LA TECLA -S- PARA SALIR", -5, 6);
	
		break;

	case OPCIONES: 
		ETSIDI::printxy("PULSE LA TECLA -1- PARA JUEGO MODO BÁSICO", -5, 7);
		ETSIDI::printxy("PULSE LA TECLA -2- PARA JUAGO MODO STAR WORS", -5, 6);
		ETSIDI::printxy("PULSE LA TECLA -3- PARA JUAGO MODO ANIMAL CROSSING", -5, 8);
		ETSIDI::printxy("PULSE LA TECLA -S- PARA VOLVER", -5, 9);
		break;
	case JUEGO:
		mundo_grafico.dibuja();
		break;
	}
}


void Coordinador::tecla(unsigned char key)
{
	switch (estado) {
	case INICIO:
		if (key == 's') exit(0);
		if (key != 'e') return;
		estado = OPCIONES;
		break;

	case OPCIONES:
		if(key == 's') estado = INICIO; //Se irá al tablero tipo1
		if (key == '1') graf_tablero= TIPO1; //Se irá al tablero tipo1
		if (key == '2') graf_tablero = TIPO2;//Se irá al tablero tipo2
		if (key == '3') graf_tablero = TIPO3;//Se irá al tablero tipo3
		mundo_grafico.init();//Se inicia la grafica del tablero deseado
		estado = JUEGO;
		break;

	case JUEGO:
		ETSIDI::printxy("ESTA EN JUEGO", -5, 9);
			//mundo_grafico.tecla(key);
		break;
	}
}

void Coordinador::tecla_especial(unsigned char key)
{
	//if (estado == JUEGO)
		//mundo_grafico.tecla_especial(key);
}
void Coordinador::mueve()
{
	//if (estado == JUEGO)
		//mundo_grafico.mueve();
}




//Variables globales para la gestión de los clicks
Vector2D click_inicial{ -1, -1 };
Vector2D click_final{ -1,-1 };
bool seleccionado = true;
//true cuando estamos seleccionando la pieza inicial
//false cuando estamos seleccionando la posicion final

void Coordinador::MouseBottom(int b, int state, int x, int y)
{

	if (estado == JUEGO)
	{
		bool down = (state == GLUT_DOWN);
		int button;
		if (b == GLUT_LEFT_BUTTON) {
			button = MOUSE_LEFT_BUTTON;
		}
	mundo_grafico.MouseButton(x, y, b, down, click_inicial, click_final, seleccionado);
}
}