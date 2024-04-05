#pragma once
#include "Pieza.h"

class Reina :
    public Pieza
{
protected:
    bool promocionada;
    bool capturada;
public:
    Reina(Color); //constructor por defecto
    Reina(Color, int, int); //promoción
};

