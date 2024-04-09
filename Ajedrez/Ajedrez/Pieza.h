#pragma once
#include "LogicaAjedrez.h"
#include <iostream>

/*
* Clase abstracta pieza - contiene los atributos básicos de una pieza
* - Color
* - Fila y columna en la que se halla
* Todas las piezas tienen una ubicación a no ser que estén capturadas (salvo el rey, a él no se le captura)
* El tipo de pieza no es un atributo de esta clase, ya que cada tipo es su propia clase subordinada
*/
class Pieza
{
protected:
	Color color; //el color determina a qué jugador pertenece
	int ubi_fila, ubi_columna;
	vector<int>ubi_prox; //vector que contiene las coordenadas de la posición siguiente
	vector<int>buffer_coordenadas; //vector intermedio para las operaciones de movimiento

	//funciones para asignar las casillas en las que empieza cada pieza, según su tipo y color
	int fila_inicial(Tipo, Color, int);
	int columna_inicial(Tipo, int);
public:
	Pieza(Color, Tipo, int); //constructor por defecto - se llama a este constructor únicamente al crear las piezas al principio de la partida
	Pieza(Color, int, int); //promoción: se llama a este constructor al promocionar un peón
	
	void actualizar_coordenadas(); //función genérica para actualizar las coordenadas, podemos usarla luego cuando programemos el movimiento
};
