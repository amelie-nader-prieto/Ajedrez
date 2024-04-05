#pragma once
#include "Pieza.h"
class Caballo :
    public Pieza
{
protected:
    bool promocionado;
    int num_caballo;
    bool capturado;
public:
    Caballo(Color, int); //constructor por defecto
    Caballo(Color, int, int); //promoción
};

