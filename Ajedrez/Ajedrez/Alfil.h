#pragma once
#include "Pieza.h"

class Alfil :
    public Pieza
{
protected:
    bool promocionado;
    int num_alfil;
    bool capturado;
public:
    Alfil(Color, int); //constructor por defecto
    Alfil(Color, int, int); //promoción

};

