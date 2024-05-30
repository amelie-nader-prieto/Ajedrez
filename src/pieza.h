#pragma once
#include "Tipos_piezas.h"
#include "vector2D.h"
#include "ETSIDI.h"
#include "freeglut.h"

using ETSIDI::SpriteSequence; //facilita el uso de texturas, fuentes y sonidos 

class Pieza
{
protected:
	int fila;
	int columna;

	Vector2D posicion;
	Tipo tipo;
	Jugador jugador;
		
	bool primer_movimiento = true;
	bool capturada = false;

public:
	Pieza(int fila, int columna, Tipo t,Jugador j=B) : fila(fila), columna(columna),posicion(fila,columna), tipo(t), jugador(j) {}
	Pieza(Vector2D _posicion = Vector2D(0, 0), Jugador _jugador = ninguno, Tipo _tipo = no_hay) :
		posicion(_posicion), tipo(_tipo), jugador(_jugador)
	{
		fila = _posicion.y;
		columna = _posicion.x;
	}

	// funciones de interfaz
	inline Tipo GetTipo()const { return tipo; }
	inline Jugador GetJugador()const { return jugador; }
	inline Vector2D GetPosicion()const { return posicion; }
	/*
	* Consulta si la pieza se ha movido o todavía no
	* true si ya se ha movido, false si todavía no
	*/
	inline bool ha_movido() { return primer_movimiento ? false : true; }

	// llamar a esta función cuando la pieza haga el primer movimiento
	inline void set_ha_movido() { primer_movimiento = false; }
	// llamar a esta función si la pieza es capturada
	inline void set_captura() { capturada = true; }
	// actualiza las coordenadas de la pieza
	inline void actualizar_coordenadas(const Vector2D& _posicion) {
		posicion = _posicion;
	}


};
