#pragma once
#include "GLTablero.h"
#include "ETSIDI.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Coordinador
{
	//GLTablero mundo_grafico;
	enum Estado { MENU1, MENU2, GRAFICOS, EXPLICACION, JUEGO, PAUSA, GAMEOVER, FIN } estado = MENU1;
	enum Tipo_Tablero { classic = 1, starwors, animal }graficas_tablero = classic;
	enum Modalida { maquina, jugadores }modalidad = jugadores;
	enum Volumen { ON, OFF } volumen = OFF;
	bool inicial=true;


	void iniciarMusica();
	void pararMusica();

	string imagen = "bin/Menu/menu1.png";
	
	GLTablero mundo_grafico;

public:
	//Coordinador();
	//virtual ~Coordinador();
	//void mueve();
	//void tecla_especial(unsigned char key);
	void imagenes(const char* ruta);

	void iniciar();

	void tecla(unsigned char key);
	void dibuja(Tablero tab);
	void dibujar_Tablero(const int& Estadoskin);
	void MouseBottom(int x, int y, int button, bool down, Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado);
	void musica();

	/*devuelve 1 si la modalidad es J vs J, y 2 si es J vs IA*/
	int getModalidad() {return (modalidad == jugadores ? 1 : 2);}
};
