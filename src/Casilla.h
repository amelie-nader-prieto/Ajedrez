#pragma once
#include <iostream>
#include "freeglut.h" //necesario para el dibujo de la casilla

class Casilla
{
public:
    int row, col;
    //row: fila - va de 0 a 9
    //col: coluna - va de 0 a 10
    void imprime() {
        std::cout << "( " << row << " , " << col << " )" << std::endl;
    }

    void dibuja(int i, int j, int ro, int go, int bo, int rc, int gc, int bc); //para el dibujo de una casilla
    void dibujaGrid(int i, int j); //para las lineas (delimita las casillas)
};
