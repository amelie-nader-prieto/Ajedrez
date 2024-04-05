#pragma once
#include "LogicaAjedrez.h"
#include <iostream>

class Pieza
{
protected:
	Color color; //el color determina a qué jugador pertenece
	int ubi_fila, ubi_columna;
	vector<int>ubi_prox; //vector que contiene las coordenadas de la posición siguiente
	vector<int>buffer_coordenadas;

	int fila_inicial(Tipo, Color, int);
	int columna_inicial(Tipo, int);
public:
	Pieza(Color, Tipo, int); //constructor por defecto
	Pieza(Color, int, int); //promoción: se llama a este constructor al promocionar a un peón
	
	void actualizar_coordenadas();
};
