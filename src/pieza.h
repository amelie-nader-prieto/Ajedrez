#pragma once
#include "Tipos_piezas.h"
#include "vector2D.h"


class Pieza
{
protected:
	int fila=0;
	int columna=0;

	Vector2D posicion;
	Tipo tipo;
	Jugador jugador;
		
	bool primer_movimiento = true;
	bool capturada = false;

	bool promocionado = false; // s�lo para peones

public:
	Pieza(int fila, int columna, Tipo t,Jugador j=B) : fila(fila), columna(columna),posicion(fila,columna), tipo(t), jugador(j) {}
	Pieza(Vector2D _posicion = Vector2D(0, 0), Jugador _jugador = ninguno, Tipo _tipo = no_hay) :
		posicion(_posicion), tipo(_tipo), jugador(_jugador)
	{
	}

	// funciones de interfaz
	inline Tipo GetTipo() const { return tipo; }
	inline Jugador GetJugador()const { return jugador; }
	inline Vector2D GetPosicion()const { return posicion; }
	inline bool GetCapturada()const { return capturada; }
	inline bool GetPromocionado()const { return promocionado; }
	/*
	* Consulta si la pieza se ha movido o todav�a no
	* true si ya se ha movido, false si todav�a no
	*/
	inline bool ha_movido() { return primer_movimiento ? false : true; }


	// llamar a esta funci�n cuando la pieza haga el primer movimiento
	inline void set_ha_movido() { primer_movimiento = false; }
	// llamar a esta funci�n si la pieza es capturada
	inline void set_captura() { capturada = true; }
	// llamar a esta funci�n si la pieza promociona (s�lo si es un pe�n)
	inline void set_promocion() { if (tipo == P)promocionado = true; }
	// actualiza las coordenadas de la pieza
	inline void actualizar_coordenadas(const Vector2D& _posicion) {
		posicion = _posicion;
	}


};
