#include "Coordinador.h"


void Coordinador::dibuja()
{
	switch (estado) {
	case MENU1:
		cout << "Pulsa J para jugar" << endl;
		cout << "Pulsa S para salir" << endl;
		break;
	case MENU2:
		cout << "Pulsa 1 para jugar contra jugador" << endl;
		cout << "Pulsa S para  jugar contra máquina" << endl;
		break;

	case GRAFICOS: 
		cout<<"PULSE LA TECLA -1- PARA JUEGO MODO BÁSICO"<<endl;
		cout << "PULSE LA TECLA -2- PARA JUAGO MODO STAR WORS" << endl;
		cout << "PULSE LA TECLA -3- PARA JUAGO MODO ANIMAL CROSSING" << endl;
		cout << "PULSE LA TECLA -S- PARA VOLVER" << endl;
		break;
	case EXPLICACION:
		cout << "Se explican las fichas de" << graf_tablero;
	case JUEGO:
		cout<<"Se esta jugando al"<<graf_tablero;
		break;
	}
}


void Coordinador::tecla(unsigned char key)
{
	switch (estado) {
	case MENU1:
		if (key == 's') exit(0);
		if (key == 'e')
		{
			estado = MENU2;
		}
		break;

	case MENU2:
		if (key == '1') //Modelidad contra máquina
			modalidad = jugadores;
		if (key == '2')//Modalidad contra 2 jugadores
			modalidad = maquina;
		estado = GRAFICOS;
		break;

	case GRAFICOS:
		if (key == 'e') {
			estado = MENU1; //Se irá al menu inicial
			break;
		}
		if (key == '1') {
			graf_tablero = clasic;
			estado = JUEGO;//Se irá al tablero tipo1
			break;
		}
		if (key == '2') graf_tablero = starwors;//Se irá al tablero tipo2
		if (key == '3') graf_tablero = animal;//Se irá al tablero tipo3

		mundo_grafico.init();//Se inicia la grafica del tablero deseado
		estado = EXPLICACION;
		break;

	case EXPLICACION:
		if (key == 'c')
			estado = JUEGO;
		break;
	case JUEGO:
		if (key == 'm') estado = PAUSA;
			//mundo_grafico.tecla(key);
		break;
	case PAUSA:
		if (key == 'c')
			estado = JUEGO;
		if(key == 'e')
			estado = MENU1;
		if (key == 'v')
			volumen = ON;
		if (key == 's')
			volumen = OFF;
		break;
	case GAMEOVER:
		if (key == 'r')
			estado = MENU2;
		if (key == 'e')
			estado = FIN;
		break;
	case FIN:
		exit(0);
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


void Coordinador::MouseBottom(int x, int y, int button, bool down, Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado)
{

	if (estado == JUEGO)
	{
	mundo_grafico.MouseButton(x, y, button, down, click_inicial, click_final, seleccionado);
	}
}


void Coordinador::iniciar()
{
	estado = MENU1;
}

Coordinador::~Coordinador()
{
}