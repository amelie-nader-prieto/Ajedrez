#pragma once
#include "LogicaAjedrez.h"
#include <iostream>

/*
* Clase abstracta pieza - contiene los atributos b�sicos de una pieza
* - Color
* - Fila y columna en la que se halla
* Todas las piezas tienen una ubicaci�n a no ser que est�n capturadas (salvo el rey, a �l no se le captura)
* El tipo de pieza no es un atributo de esta clase, ya que cada tipo es su propia clase subordinada
*/
class Pieza
{
protected:
	Color color; //el color determina a qu� jugador pertenece
	int ubi_fila, ubi_columna;
	vector<int>ubi_prox; //vector que contiene las coordenadas de la posici�n siguiente
	vector<int>buffer_coordenadas; //vector intermedio para las operaciones de movimiento

	//funciones para asignar las casillas en las que empieza cada pieza, seg�n su tipo y color
	int fila_inicial(Tipo, Color, int);
	int columna_inicial(Tipo, int);
public:
	Pieza(Color, Tipo, int); //constructor por defecto - se llama a este constructor �nicamente al crear las piezas al principio de la partida
	Pieza(Color, int, int); //promoci�n: se llama a este constructor al promocionar un pe�n
	
	void actualizar_coordenadas(); //funci�n gen�rica para actualizar las coordenadas, podemos usarla luego cuando programemos el movimiento
};
