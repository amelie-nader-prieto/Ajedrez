#pragma once
#include "Pieza.h"
class Peon :
    public Pieza
{
protected:
    bool promocionable;
    int num_peon;
    bool capturado;
public:
    Peon(Color, int, int, int);
    void checkProm();
    void coordenadas_avance();
    void coordenadas_comer();
};

