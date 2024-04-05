#pragma once
#include "Pieza.h"
class Torre :
    public Pieza
{
protected:
    bool promocionada;
    int num_torre;
    bool capturada;
public:
    Torre(Color, int); //constructor por defecto
    Torre(Color, int, int); //promoción
};

