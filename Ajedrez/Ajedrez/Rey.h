#pragma once
#include "Pieza.h"
class Rey :
    public Pieza
{
protected:
    bool amenazado;
public:
    Rey(Color);
};

