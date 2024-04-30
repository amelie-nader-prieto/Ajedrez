#pragma once
#include <iostream>

class Casilla
{
public:
    int row, col;
    //row: fila - va de 0 a 9
    //col: coluna - va de 0 a 10
    void imprime() {
        std::cout << "( " << row << " , " << col << " )" << std::endl;
    }
};
