#include "LogicaAjedrez.h"


// FUNCIONES QUE REVISAN EL TABLERO
bool hay_pieza_tuya(Vector2D _posicion, Jugador _jugador, Tablero tab) {
    if (tab.tablero[_posicion.x][_posicion.y]->GetTipo() == no_hay)return false;
    else if (tab.tablero[_posicion.x][_posicion.y]->GetJugador() == _jugador)return true;
    else return false;
}
bool hay_pieza_rival(Vector2D _posicion, Jugador _jugador, Tablero tab) {
    if (tab.tablero[_posicion.x][_posicion.y]->GetTipo() == no_hay)return false;
    else if (tab.tablero[_posicion.x][_posicion.y]->GetJugador() != _jugador)return true;
    else return false;
}
bool condiciones_captura_peon(Pieza _peon, Tablero tab) {
    vector<Dir_t>direcciones_diagonal{}; // direcciones en las que el peón puede capturar. se inicializa según el color
    Vector2D posicion_siguiente;

    switch (_peon.GetJugador()) {
    case B:
        direcciones_diagonal.push_back(Dir_t::UPLEFT);
        direcciones_diagonal.push_back(Dir_t::UPRIGHT);
        break;
    case W:
        direcciones_diagonal.push_back(Dir_t::DOWNLEFT);
        direcciones_diagonal.push_back(Dir_t::RIGHTDOWN);
        break;
    default:break;
    }

    // Determina si el peón puede capturar
    for (const auto& p : direcciones_diagonal) {
        siguienteCasilla(p, _peon.GetPosicion(), posicion_siguiente);
        if (omitir_posicion(posicion_siguiente))continue;
        if(hay_pieza_rival(posicion_siguiente,_peon.GetJugador(),tab)) return true;
    }

    return false;

}
bool condiciones_captura_al_paso(Pieza posible_peon_capturado, Tablero tab, vector<Vector2D>posicion_posible_capturador) {
    // el argumento posible_peon_capturado DEBE HABER AVANZADO DOS FILAS EN EL TURNO ANTERIOR
    // Las condiciones para la captura al paso se cumplen si hay un peón del color opuesto en esa misma fila
    auto jugador = posible_peon_capturado.GetJugador();
    int fila = 0;
    switch (jugador) {
    case B: fila = 4; break;
    case W: fila = 5; break;
    default:break;
    }

    for (auto j = 0; j < COLUMNA; j++){
        if (
            (hay_pieza_rival({ fila,j }, jugador, tab)) && (tab.tablero[fila][j]->GetTipo() == P)
            )
            return true;
    }

    return false;
}
bool condiciones_promocion(Pieza peon) {
    if (peon.GetTipo() != P)return false; // sólo promocionan los peones
    
    auto jugador = peon.GetJugador();
    auto columna = peon.GetPosicion().y;
    auto fila = peon.GetPosicion().x;

    switch (jugador) {
    case W:
        // Blanco - las filas últimas son 0, 1 y 2 (la 2 sólo para caballo o alfil)
        if (
            ((columna == 2 || columna == 8) && fila == 2) ||
            ((columna == 3 || columna == 7) && fila == 1) ||
            ((columna > 3 && columna < 7) && fila == 0))return true;
        break;
    case B:
        // Negro - las filas últimas son 7, 8 y 9 (la 7 sólo para caballo o alfil)
        if (
            ((columna == 2 || columna == 8) && fila == 7) ||
            ((columna == 3 || columna == 7) && fila == 8) ||
            ((columna > 3 && columna < 7) && fila == 9))return true;
        break;
    default:break;
    }

    return false;

}
bool amenazado(Vector2D casilla, Tablero tab) {
    vector<Pieza>piezas_rival{}; // se inicializa con las piezas que pertenecen al color opuesto
    auto jugador = tab[casilla]->GetJugador();

    switch (jugador) {
    case B:piezas_rival = tab.get_piezas_bla(); break;
    case W:piezas_rival = tab.get_piezas_neg(); break;
    default:return false; break;
    }

    // Itera sobre las piezas del jugador rival
    for (const auto& p : piezas_rival) {
        if (p.GetCapturada() ||
            (p.GetTipo() == P && p.GetPromocionado())
            )continue;

        // Para cada pieza rival, itera sobre sus posibles movimientos
        for (const auto& u : obtener_posibles_movimientos(p.GetPosicion(), tab)) {
            // Para cada posible movimiento de la pieza rival,
            // lo compara con la posición del rey (si coinciden, el rey está amenazado)
            if (casilla == u) { return true; break; }
        }
    }

    return false;

}
bool amenazado(Vector2D casilla, Tablero tab, vector<Vector2D>& piezas_que_lo_amenazan) {
    vector<Vector2D>v; // se irá rellenando con las posiciones de las piezas que amenazan a tu rey, si hay
    vector<Pieza>piezas_rival{}; // se inicializa con las piezas que pertenecen al color opuesto
    auto jugador = tab[casilla]->GetJugador();

    switch (jugador) {
    case B:piezas_rival = tab.get_piezas_bla(); break;
    case W:piezas_rival = tab.get_piezas_neg(); break;
    default:return false; break;
    }

    // Itera sobre las piezas del jugador rival
    for (const auto& p : piezas_rival) {
        if (p.GetCapturada() ||
            (p.GetTipo() == P && p.GetPromocionado())
            )continue;

        // Para cada pieza rival, itera sobre sus posibles movimientos
        for (const auto& u : obtener_posibles_movimientos(p.GetPosicion(), tab)) {
            // Para cada posible movimiento de la pieza rival,
            // lo compara con la posición del rey (si coinciden, el rey está amenazado)
            if (casilla == u) {
                v.push_back(p.GetPosicion()); // añade la pieza rival al vector para retornarlo
                break; //para dejar de iterar sobre sus movimientos
            }
        }
    }

    piezas_que_lo_amenazan = v;
    return(v.size() == 0 ? false : true);

}
bool condiciones_fin_de_la_partida(Tablero tab, Jugador& derrotado) {
    Vector2D posicion_rey; // se usará para localizar a los reyes de ambos jugadores
    bool Rb_mate = true, Rn_mate = true;

    // Evalúa las condiciones para cada jugador
    for (auto jugador : { B,W }) {

        posicion_rey = tab.get_rey(jugador);
        bool& R_mate = (jugador == B ? Rn_mate : Rb_mate);

        // comprobamos si está en jaque (amenazado
        // Si NO está en jaque, no hay que comprobar nada más
        if (!amenazado(posicion_rey, tab)) {
            R_mate = false;
            continue;
        }
        
        // comprobamos todas las jugadas legales que pueden sacarte del jaque
        // (Si no hay ninguna posible, hay mate)
        else {
            // MOVIENDO AL REY
            // si puede moverse a alguna otra casilla en la que no vaya a estar amenazado, no hay mate
            if (sitios_sin_amenaza(posicion_rey, tab).size() != 0) { 
                R_mate = false;
                continue;
            }

            // MOVIENDO ALGUNA OTRA PIEZA
            vector<Vector2D>posiciones_amenaza{}; // se inicializa con las posiciones en las que están las piezas que te amenazan
            amenazado(posicion_rey, tab, posiciones_amenaza);

            // Si sólo estás amenazado por UNA pieza del rival...
            if (posiciones_amenaza.size() == 1) {
                //... y puedes capturarla, no hay mate.
                if (amenazado(posiciones_amenaza[0], tab)) { /*la lógica de esta función permite utilizarla para cualquier pieza*/
                    R_mate = false;
                    continue;
                }

                // Si no puedes capturarla, PERO:
                // - es D, A o T (se mueven en línea recta), Y
                // - alguna de tus piezas puede meterse en su camino (poniéndose entre esa pieza y el rey)
                // tampoco hay mate.
                if (
                    tab[posiciones_amenaza[0]]->GetTipo() == T ||
                    tab[posiciones_amenaza[0]]->GetTipo() == D ||
                    tab[posiciones_amenaza[0]]->GetTipo() == A
                    ) {

                    auto p_amenaza = posiciones_amenaza[0];
                    vector<Vector2D>camino{}; // casillas entre la pieza rival y tu rey
                    Vector2D p_ini = p_amenaza, p_buffer = p_ini, p_siguiente;
                    Dir_t direccion_camino;

                    // Recorrido desde la pieza rival hasta tu rey
                    auto recorrido = posicion_rey - p_amenaza; // es como posición final (rey) - posición inicial (la otra pieza)
                    // Para obtener la dirección
                    if (recorrido.x == 0 && recorrido.y == 0) /*el recorrido es horizontal o vertical*/ {
                        direccion_camino = (recorrido.x == 0 ?
                            (recorrido.y > 0 ? Dir_t::UP : Dir_t::DOWN) : /* misma columna */
                            (recorrido.x > 0 ? Dir_t::RIGHT : Dir_t::LEFT) /* misma fila */
                            );
                    }
                    else /*el recorrido es diagonal*/ {

                    }

                    // Inicializar el camino


                    // Comprobar si alguna de tus piezas puede meterse en el camino


                }

            }

        }

    }

    // Una vez evaluadas las condiciones para ambos jugadores
    if (Rb_mate || Rn_mate) {
        derrotado = (Rb_mate ? W : B); // inicializa el valor del jugador derrotado (aquél cuyo rey está en mate)
        return true;
    }
    return false;

}


// FUNCIONES QUE HACEN COPIAS DEL TABLERO
vector<Vector2D>sitios_sin_amenaza(Vector2D casilla, Tablero tab) {
    vector<Vector2D>sitios_ok{}; // se rellenará con las casillas en las que ya no estaría amenazado
    
    auto tab_copia = new Tablero; // se hace una copia del tablero
    *tab_copia = tab;
    // Itera sobre los posibles movimientos de tu rey
    for (auto p : obtener_posibles_movimientos(casilla, tab)) {
        mover_pieza(casilla, p, *tab_copia); // hacemos dicho movimiento y vemos si tu rey sigue amenazado
        if (!amenazado(p, *tab_copia)) sitios_ok.push_back(p); // si al hacer el movimiento ya no está amenazado, lo añadimos
        *tab_copia = tab; // resetea el tablero copiado
    }
    delete tab_copia;
    
    return sitios_ok;

}


// FUNCIONES DE MOVIMIENTO
void siguienteCasilla(Dir_t dir, Vector2D ini, Vector2D& fin) {
    switch (dir)
    {
    case Dir_t::LEFT:
        fin.x = ini.x; fin.y = ini.y - 1;
        break;
    case Dir_t::UPLEFT:
        fin.x = ini.x + 1; fin.y = ini.y - 1;
        break;
    case Dir_t::UP:
        fin.x = ini.x + 1; fin.y = ini.y;
        break;
    case Dir_t::UPRIGHT:
        fin.x = ini.x + 1; fin.y = ini.y + 1;
        break;
    case Dir_t::RIGHT:
        fin.x = ini.x; fin.y = ini.y + 1;
        break;
    case Dir_t::RIGHTDOWN:
        fin.x = ini.x - 1; fin.y = ini.y + 1;
        break;
    case Dir_t::DOWN:
        fin.x = ini.x - 1; fin.y = ini.y;
        break;
    case Dir_t::DOWNLEFT:
        fin.x = ini.x - 1; fin.y = ini.y - 1;
        break;
    default:
        break;
    }
}
vector<Vector2D>obtener_posibles_movimientos(Pieza _p, Tablero tab) {

    vector<Vector2D>posibles_movimientos{}; // aqu� almacenar� los movimientos
    vector<Dir_t>direcciones{}; // se inicializa seg�n el tipo de la pieza
    vector<Vector2D>direcciones_caballo{
        Vector2D(-2,-1),Vector2D(-2,1),Vector2D(2,-1),Vector2D(2,1),
        Vector2D(-1,-2),Vector2D(-1,2),Vector2D(1,-2),Vector2D(1,2)
    }; // direcciones del caballo

    auto posicion_actual = _p.GetPosicion();
    auto posicion_buffer = posicion_actual; // crea una copia de las coordenadas actuales para iterar sobre ellas sin modificarlas
    Vector2D posicion_siguiente; // posici�n siguiente

    /* 
    Fin del camino
    * Si este parámetro es true, se deja de evaluar una dirección
    * Se ha llegado al fin del camino cuando (alguna de las siguientes):
    * - Hay pieza tuya en la casilla siguiente (la descartará)
    * - La posición siguiente se sale del tablero (la descartará)
    * - Hay una pieza rival en la casilla ACTUAL (la guardará y no revisará la siguiente)
    * En caso de que se haya llegado al fin del camino, lo que se hace es NO AÑADIR LA POSICIÓN SIGUIENTE
    * y salirse del bucle (se pasaría a evaluar la DIRECCIÓN siguiente)
    */
    bool fin_del_camino = false;
    
    switch (_p.GetTipo()) {
    case no_hay:break;
    case A: // Alfil
        // el alfil se mueve por las diagonales
        direcciones = { Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        // Itera sobre las direcciones
        for (const auto& p : direcciones) {

            // Itera sobre la MISMA dirección
            do {
                // inicializa la posición siguiente
                siguienteCasilla(p, posicion_buffer, posicion_siguiente);

                // si la posición siguiente es fin del camino, no la añadirá
                fin_del_camino = (
                    omitir_posicion(posicion_siguiente) ||
                    hay_pieza_tuya(posicion_siguiente, _p.GetJugador(), tab) ||
                    hay_pieza_rival(posicion_buffer, _p.GetJugador(), tab)
                    ) ? true : false;
                // si no es fin del camino, la añadirá
                if (!fin_del_camino) posibles_movimientos.push_back(posicion_siguiente);

                // antes de pasar a la dirección siguiente, actualiza las coordenadas para seguir iterando
                posicion_buffer = posicion_siguiente;

            } while (!fin_del_camino); // fin del bucle sobre la dirección
            posicion_buffer = posicion_actual;
        } // fin del bucle sobre todas las direcciones
        break;
    case T: // TORRE
        // la torre se mueve por las filas y columnas
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT };
        // Itera sobre las direcciones
        for (const auto& p : direcciones) {

            // Itera sobre la MISMA direcci�n
            do {
                // inicializa la posici�n siguiente
                siguienteCasilla(p, posicion_buffer, posicion_siguiente);


                fin_del_camino = (
                    omitir_posicion(posicion_siguiente) ||
                    hay_pieza_tuya(posicion_siguiente, _p.GetJugador(), tab) ||
                    hay_pieza_rival(posicion_buffer, _p.GetJugador(), tab)
                    ) ? true : false;

                if (!fin_del_camino) posibles_movimientos.push_back(posicion_siguiente);

                // antes de pasar a la direcci�n siguiente, actualiza las coordenadas para seguir iterando
                posicion_buffer = posicion_siguiente;

            } while (!fin_del_camino);
        }
        break;
    case D: // DAMA
        // la dama se mueve en todas direcciones
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        for (const auto& p : direcciones) {

            // Itera sobre la MISMA direcci�n
            do {
                // inicializa la posici�n siguiente
                siguienteCasilla(p, posicion_buffer, posicion_siguiente);


                fin_del_camino = (
                    omitir_posicion(posicion_siguiente) ||
                    hay_pieza_tuya(posicion_siguiente, _p.GetJugador(), tab) ||
                    hay_pieza_rival(posicion_buffer, _p.GetJugador(), tab)
                    ) ? true : false;

                if (!fin_del_camino) posibles_movimientos.push_back(posicion_siguiente);

                // antes de pasar a la direcci�n siguiente, actualiza las coordenadas para seguir iterando
                posicion_buffer = posicion_siguiente;

            } while (!fin_del_camino);
        }
        break;
    case R: // REY
        // el rey se mueve en todas direcciones, pero s�lo avanza una casilla
        // (no hace falta iterar sobre la misma direcci�n)
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        for (const auto& p : direcciones) {
            siguienteCasilla(p, posicion_buffer, posicion_siguiente);

                        
            if (omitir_posicion(posicion_siguiente) ||
                hay_pieza_tuya(posicion_siguiente, _p.GetJugador(), tab))continue;

            posibles_movimientos.push_back(posicion_siguiente);

        }
        break;
    case C: // CABALLO
        // el caballo sigue sus propias reglas
        for (const auto& p : direcciones_caballo) {

            posicion_siguiente = posicion_buffer + p;
            
            if (omitir_posicion(posicion_siguiente) ||
                hay_pieza_tuya(posicion_siguiente, _p.GetJugador(), tab))continue;

            posibles_movimientos.push_back(posicion_siguiente);

        }
        break;
    case P: // PE�N
        // el pe�n sigue sus propias reglas y encima son rar�simas
        /* AVANCE: El pe�n avanza una fila (o dos, si es su primer movimiento)
        * CAPTURA: Si hay una pieza del color opuesto en la fila siguiente y columna adyacente, puede capturarla (se mover� a la casilla en la que estaba esa pieza)
        * CAPTURA AL PASO: Si hay un pe�n del color opuesto:
        * - En su misma fila
        * - En una columna adyacente
        * - Que ha avanzado dos filas en el turno anterior
        * Puede capturarlo (se mover� a la casilla en la que estar�a ese pe�n si s�lo hubiese avanzado una fila)
        * PROMOCI�N: Si est� en una posici�n en la que no puede avanzar m�s, debe promocionar
        * (esta funci�n no gestiona la promoci�n del pe�n)
        */

        // AVANCE
        
        switch (_p.GetJugador()) {
        case B: //negro
            direcciones.push_back(Dir_t::UP);
            break;
        case W: // blanco
            direcciones.push_back(Dir_t::DOWN);
            break;
        default:break;
        }

        siguienteCasilla(direcciones[0], posicion_buffer, posicion_siguiente);

        // si la posici�n siguiente es v�lida, la a�ade
        if (!(
            omitir_posicion(posicion_siguiente) ||
            hay_pieza_tuya(posicion_siguiente, _p.GetJugador(), tab)
            ))posibles_movimientos.push_back(posicion_siguiente);

        // si es su primer movimiento, el pe�n puede avanzar 2 filas
        if (!_p.ha_movido()) {
            posicion_buffer = posicion_siguiente;
            siguienteCasilla(direcciones[0], posicion_buffer, posicion_siguiente);
            posibles_movimientos.push_back(posicion_siguiente);
            _p.set_ha_movido();
        }


        // CAPTURA
        // (comprobar si hay condiciones de captura)
        // . . .
        if (condiciones_captura_peon(_p, tab)) {

        }

        // CAPTURA AL PASO
        // (comprobar si hay condiciones de captura al paso)
        // . . .
        

        // PROMOCIÓN
        // (si hay condiciones de promoción, es que no se puede mover)
        // . . .

        break;

    default:break;
    }

    return posibles_movimientos;

}
vector<Vector2D>obtener_posibles_movimientos(Vector2D casilla, Tablero tab) {
    vector<Vector2D>posibles_movimientos{}; // aquí almacenará los posibles movimientos
    vector<Dir_t>direcciones{}; // se inicializa según el tipo de pieza (excepto caballo)
    vector<Vector2D>direcciones_caballo{
        Vector2D(-2,-1),Vector2D(-2,1),Vector2D(2,-1),Vector2D(2,1),
        Vector2D(-1,-2),Vector2D(-1,2),Vector2D(1,-2),Vector2D(1,2)
    }; // direcciones del caballo

    auto posicion_actual = casilla; // posición de la pieza - este dato no se modifica
    auto posicion_buffer = posicion_actual; // crea una copia de la posición actual para iterar sobre ella
    Vector2D posicion_siguiente; // posición siguiente

    /*
    * Fin del camino
    * * Si este parámetro es true, se deja de evaluar una dirección
    * Se ha llegado al fin del camino cuando (alguna de las siguientes):
    * - Hay pieza tuya en la casilla siguiente
    * - La posición siguiente se sale del tablero
    * - Hay una pieza rival en la casilla ACTUAL
    * En caso de que se haya llegado al fin del camino, lo que se hace es NO AÑADIR LA POSICIÓN SIGUIENTE
    * y salirse del bucle (se pasa a evaluar la dirección siguiente)
    */
    bool fin_del_camino = false;

    auto tipo_pieza = tab.tablero[casilla.x][casilla.y]->GetTipo();
    auto jugador = tab.tablero[casilla.x][casilla.y]->GetJugador();

    switch (tipo_pieza) {
    case no_hay:break;
    case A:// Alfil
        // el alfil se mueve por las diagonales
        direcciones = { Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        // Itera sobre las direcciones
        for (const auto& p : direcciones) {
            // Itera sobre la MISMA dirección
             do{
                // inicializa la posición siguiente en esa dirección
                siguienteCasilla(p, posicion_buffer, posicion_siguiente);
                // Evalúa si dicha posición es fin del camino
                fin_del_camino = (
                    omitir_posicion(posicion_siguiente) ||
                    hay_pieza_tuya(posicion_siguiente, jugador, tab) ||
                    hay_pieza_rival(posicion_buffer, jugador, tab)
                    ) ? true : false;
                if (!fin_del_camino) posibles_movimientos.push_back(posicion_siguiente);

                posicion_buffer = posicion_siguiente;

             } while (!fin_del_camino); // fin del bucle sobre la misma dirección
             posicion_buffer = posicion_actual;
        } // fin del bucle que itera sobre todas las direcciones
        break;

    case T: // Torre
        // la torre se mueve por las filas y columnas
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT };
        // Itera sobre las direcciones
        for (const auto& p : direcciones) {
            // Itera sobre la MISMA dirección
            do {
                // Inicializa la posición siguiente
                siguienteCasilla(p, posicion_buffer, posicion_siguiente);
                // Evalúa si dicha posición es fin del camino
                fin_del_camino = (
                    omitir_posicion(posicion_siguiente) ||
                    hay_pieza_tuya(posicion_siguiente, jugador, tab) ||
                    hay_pieza_rival(posicion_buffer, jugador, tab)
                    ) ? true : false;

                if (!fin_del_camino)posibles_movimientos.push_back(posicion_siguiente);
                posicion_buffer = posicion_siguiente;
            } while (!fin_del_camino); // fin del bucle sobre la misma dirección
            posicion_buffer = posicion_actual;
        } // fin del bucle sobre todas las direcciones
        break;

    case D: // Dama
        // La dama se mueve en todas las direcciones
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,
            Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        // Itera sobre las direcciones
        for (const auto& p : direcciones) {
            // Itera sobre la MISMA dirección
            do {
                // Inicializa la posición siguiente
                siguienteCasilla(p, posicion_buffer, posicion_siguiente);
                // Evalúa si dicha posición es fin del camino
                fin_del_camino = (
                    omitir_posicion(posicion_siguiente) ||
                    hay_pieza_tuya(posicion_siguiente, jugador, tab) ||
                    hay_pieza_rival(posicion_buffer, jugador, tab)
                    ) ? true : false;

                if (!fin_del_camino)posibles_movimientos.push_back(posicion_siguiente);
                posicion_buffer = posicion_siguiente;
            } while (!fin_del_camino); // fin del bucle sobre la misma dirección
            posicion_buffer = posicion_actual;
        } // fin del bucle sobre las direcciones
        break;

    case R: // Rey
        // El rey se mueve en todas direcciones, pero sólo avanza una casilla
        // (no hace falta iterar sobre la misma dirección)
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,
            Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        // Itera sobre las direcciones
        for (const auto& p : direcciones) {
            // Inicializa la posición siguiente 
            siguienteCasilla(p, posicion_buffer, posicion_siguiente);
            // Si es final del camino, la descarta
            if (omitir_posicion(posicion_siguiente) ||
                hay_pieza_tuya(posicion_siguiente, jugador, tab))
                continue;

            posibles_movimientos.push_back(posicion_siguiente);
        }
        break;

    case C: // Caballo
        // El caballo sigue sus propias reglas

        // Itera sobre SUS direcciones
        for (const auto& p : direcciones_caballo) {
            posicion_siguiente = posicion_buffer + p;
            
            if (omitir_posicion(posicion_siguiente) ||
                hay_pieza_tuya(posicion_siguiente, jugador, tab))
                continue;

            posibles_movimientos.push_back(posicion_siguiente);
        }
        break;

    case P: // Peón
        // El peón sigue sus propias reglas y encima son rarísimas
        /* AVANCE: El peón avanza una fila (o dos, si es su primer movimiento)
        * CAPTURA: Si hay una pieza del color opuesto en la fila siguiente y columna adyacente, puede capturarla (se moverá a la casilla en la que estaba esa pieza)
        * CAPTURA AL PASO: Si hay un peón del color opuesto:
        * - En su misma fila
        * - En una columna adyacente
        * - Que ha avanzado dos filas en el turno anterior
        * Puede capturarlo (se moverá a la casilla en la que estaría ese peón si sólo hubiese avanzado una fila)
        * PROMOCIÓN: Si está en una posición en la que no puede avanzar más, debe promocionar
        * (esta función no gestiona la promoción del peón)
        */

        // PROMOCIÓN
        /* Si puede promocionar, es porque no puede avanzar más.
        * Comprobar esto antes de nada. Si se cumple, salir del bucle
        */

        switch (jugador) {
        case B: //negro
            direcciones.push_back(Dir_t::UP);
            break;
        case W: // blanco
            direcciones.push_back(Dir_t::DOWN);
            break;
        default:break;
        }

        // Inicializa la posición siguiente
        siguienteCasilla(direcciones[0], posicion_buffer, posicion_siguiente);
        

        // CAPTURA AL PASO
        // (comprobar si hay condiciones de captura al paso)
        // . . .


        // CAPTURA
        /*
        * Comprueba si hay pieza rival en las casillas en diagonal.
        * Si hay, las añade. (No se modifica la posición siguiente al evaluar esto)
        */
        if (
            (!omitir_posicion(posicion_siguiente + Vector2D(0, 1))) &&
            hay_pieza_rival(posicion_siguiente + Vector2D(0, 1), jugador, tab)
            ) posibles_movimientos.push_back(posicion_siguiente + Vector2D(0, 1));
        if (
            (!omitir_posicion(posicion_siguiente + Vector2D(0, -1))) &&
            hay_pieza_rival(posicion_siguiente + Vector2D(0, -1), jugador, tab)
            ) posibles_movimientos.push_back(posicion_siguiente + Vector2D(0, -1));


        // AVANCE
        /*
        * Si la casilla siguiente está dentro del tablero y está vacía, la añade
        */
        if (!(
            omitir_posicion(posicion_siguiente) ||
            hay_pieza_tuya(posicion_siguiente, jugador, tab) ||
            hay_pieza_rival(posicion_siguiente, jugador, tab) // tampoco puede haber una pieza rival porque el peón no captura en la misma dirección en que avanza
            ))posibles_movimientos.push_back(posicion_siguiente);


        // PRIMER MOVIMIENTO
        /* Si es su primer movimiento, puede avanzar dos filas.
        * Sabemos que es su primer movimiento porque está en su fila de origen.
        */
        if (
            (posicion_actual.x == 2 && jugador == B) ||
            (posicion_actual.x == 7 && jugador == W)
            ) {
            posicion_buffer = posicion_siguiente;
            siguienteCasilla(direcciones[0], posicion_buffer, posicion_siguiente);

            if (!(
                omitir_posicion(posicion_siguiente) ||
                hay_pieza_tuya(posicion_siguiente, jugador, tab) ||
                hay_pieza_rival(posicion_siguiente, jugador, tab)
                ))posibles_movimientos.push_back(posicion_siguiente);
            
        }

        // PROMOCIÓN
        // Se hace en el mismo turno, justo después de mover

        
        break;

    default:break;
    }

    return posibles_movimientos;

}
void mover_pieza(Vector2D p_ini, Vector2D p_fin, Tablero&tab) {
    auto jugador = tab[p_ini]->GetJugador();
    if (hay_pieza_rival(p_fin, jugador, tab)) tab.activar_captura(p_fin); // sólo activa la captura si hay pieza rival en el destino
    
    tab.mover_pieza(p_ini, p_fin);

    // Aquí se comprueba la promoción del peón
    //if (condiciones_promocion(*tab[p_fin]))tab.activar_promocion(p_fin);
    if (condiciones_promocion(*tab[p_fin])) {
        // elegir nuevo tipo
        Tipo nuevo_tipo;
        char opc;
        do {
            std::cout << "\nPROMOCIÓN\nSelecciona nuevo tipo: "
                << "(torre: t   caballo: c   alfil: a   dama: d)\n";
            std::cin >> opc;
        } while (!
            (opc == 'd' || opc == 'c' || opc == 'a' || opc == 't'));
        switch (opc) {
        case 'd':nuevo_tipo = D; break;
        case 'c':nuevo_tipo = C; break;
        case 'a':nuevo_tipo = A; break;
        case 't':nuevo_tipo = T; break;
        default:nuevo_tipo = C; break;
        }
        // activar promoción
        tab.activar_promocion(p_fin, nuevo_tipo);
    }

}

// INICIALIZAR PIEZAS

static void iniciar(Tipo tipo, Vector2D posicion, Jugador j,Tablero tab)
{

    switch (tipo)
    {
    case D:
        tab.tablero[posicion.x][posicion.y] = new Dama(posicion.x, posicion.y, j);
        break;
    case P:
        tab.tablero[posicion.x][posicion.y] = new Peon(posicion.x, posicion.y, j);
        break;
    case T:
        tab.tablero[posicion.x][posicion.y] = new Torre(posicion.x, posicion.y, j);
        break;
    case C:
        tab.tablero[posicion.x][posicion.y] = new Caballo(posicion.x, posicion.y, j);
        break;
    case R:
        tab.tablero[posicion.x][posicion.y] = new Rey(posicion.x, posicion.y, j);
        break;
    case A:
        tab.tablero[posicion.x][posicion.y] = new Alfil(posicion.x, posicion.y, j);
        break;
    case no_hay:
        tab.tablero[posicion.x][posicion.y] = new No_pieza(posicion.x, posicion.y);
        break;
    default:
        break;
    }

    if (tab.tablero[posicion.x][posicion.y]->GetTipo() != no_hay) {
        switch (tab.tablero[posicion.x][posicion.y]->GetJugador()) {
        case B:tab.piezas_neg.push_back(*tab.tablero[posicion.x][posicion.y]); break;
        case W:tab.piezas_bla.push_back(*tab.tablero[posicion.x][posicion.y]); break;
        default:break;
        }
    }



}

void liberar_memoria(Tablero tab) {

    for (int i = 0; i < FILA; ++i) {
        for (int j = 0; j < COLUMNA; ++j) {
            delete tab.tablero[i][j]; // liberar la memoria de cada pieza
        }
    }
}