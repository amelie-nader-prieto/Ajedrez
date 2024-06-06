 #include "LogicaAjedrez.h"

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
bool condiciones_jaque_mate(Tablero tab, Jugador posible_derrotado) {
    // si tu rey NO está amenazado, no hay mate
    auto posicion_rey = tab.get_rey(posible_derrotado);
    vector<Vector2D>posiciones_amenaza{}; // se inicializa con las posiciones en las que están las piezas que te amenazan

    if (!amenazado(posicion_rey, tab,posiciones_amenaza)) return false;
    
    // Comprueba si puedes salir del jaque...

    // moviéndote a un sitio sin amenaza
    if (sitios_sin_amenaza(posicion_rey, tab).size() != 0) return false;

    // capturando a la pieza que te amenaza    
    if (posiciones_amenaza.size() == 1) { // si sólo te amenaza una pieza...
        auto pieza_que_amenaza = posiciones_amenaza[0];
        // Capturar la pieza que amenaza
        if (amenazado(pieza_que_amenaza, tab)) return false;
        // Bloquear el jaque mediante la colocación de una pieza entre el rey y la pieza mortal del adversario
        
        //if (
        //    tab[posiciones_amenaza[0]]->GetTipo() == T ||
        //    tab[posiciones_amenaza[0]]->GetTipo() == D ||
        //    tab[posiciones_amenaza[0]]->GetTipo() == A
        //    ) {
        //    vector<Vector2D>camino{}; // casillas entre la pieza mortal del adversario y tu rey
        //    Vector2D p_ini = pieza_que_amenaza, p_buffer = p_ini, p_siguiente;
        //    Dir_t direccion_camino;
        //    auto recorrido = posicion_rey - pieza_que_amenaza; // Recorrido de la pieza rival hasta tu rey - es como posición final (rey) - posición inicial (la otra pieza)
        //    // Inicializar la dirección
        //    if (recorrido.x == 0 || recorrido.y == 0) /*el recorrido es horizontal o vertical*/ {
        //        direccion_camino = (recorrido.x == 0 ?
        //            (recorrido.y > 0 ? Dir_t::UP : Dir_t::DOWN) : /* misma columna */
        //            (recorrido.x > 0 ? Dir_t::RIGHT : Dir_t::LEFT) /* misma fila */
        //            );
        //    }
        //    else /*el recorrido es diagonal*/ {
        //        direccion_camino = (recorrido.x > 0 ?
        //            (recorrido.y > 0 ? Dir_t::UPRIGHT : Dir_t::UPLEFT) : /*x positivas: dirección up*/
        //            (recorrido.y > 0 ? Dir_t::RIGHTDOWN : Dir_t::DOWNLEFT) /*x negativas: dirección down*/
        //            );
        //    }
        //    // Inicializar el camino
        //    do {
        //        siguienteCasilla(direccion_camino, p_buffer, p_siguiente);
        //        if (!(p_siguiente == posicion_rey)) camino.push_back(p_siguiente);
        //        p_buffer = p_siguiente;
        //    } while (!(p_siguiente == posicion_rey));
        //    if (camino.size() == 0) return true;
        //    // COMPROBAR SI SE PUEDE BLOQUEAR EL JAQUE
        //    for (const auto& casilla : camino) {
        //        if (casilla_accesible(casilla, posible_derrotado, tab)) { // comprueba si algun de tus piezas puede moverse a alguna de las casillas del camino
        //            return false;
        //        }
        //    }
        //}

    }
    else return true;
}
bool casilla_accesible(Vector2D casilla, Jugador jugador, Tablero tab) {
    auto tus_piezas = (jugador == B ? tab.get_piezas_neg() : tab.get_piezas_bla());
    // Itera sobre todas tus piezas
    for (const auto& p : tus_piezas) {
        // Para cada una de tus piezas, itera sobre sus posibles movimientos
        for (const auto& u : obtener_movimientos_legales(p.GetPosicion(), tab)) {
            if (casilla == u) return true;
        }
    }
    return false;
}
bool ahogado(Jugador jugador, Tablero tab) {
    if(!amenazado(tab.get_rey(jugador),tab)) return false;
    // Comprobar si tiene jugadas legales
    auto tus_piezas = (jugador == B ? tab.get_piezas_neg() : tab.get_piezas_bla());
    for (const auto& p : tus_piezas) {
        // para cada pieza, comprueba sus jugadas legales. Si ALGUNA tiene alguna jugada legal, no hay ahogado
        if (obtener_movimientos_legales(p.GetPosicion(), tab).size() != 0) return false;
    }
    return true;
}
bool condiciones_tablas(Tablero tab) {
    return (ahogado(B, tab) || ahogado(W, tab));
}
bool condiciones_final_de_la_partida(Tablero tab) {
    return (condiciones_jaque_mate(tab, B) || condiciones_jaque_mate(tab, W)||
        condiciones_tablas(tab));
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
vector<Vector2D>obtener_movimientos_legales(Vector2D casilla, Tablero tab) {
    vector<Vector2D>movimientos_legales{};
    auto jugador = tab[casilla]->GetJugador();
    auto tu_rey = tab.get_rey(jugador);
    auto tab_copia = new Tablero; // se usa para hacer una copia del tablero
    *tab_copia = tab;
    // Itera sobre los posibles movimientos de la pieza en cuestión
    for (const auto& p_fin : obtener_posibles_movimientos(casilla, tab)) {
        mover_pieza(casilla, p_fin, *tab_copia);
        if (!amenazado(tu_rey, *tab_copia)) movimientos_legales.push_back(p_fin); // si al mover la pieza no hay jaque, la añade a los movimientos legales
        *tab_copia = tab; // resetea el tablero copiado
    }
    delete tab_copia;
    
    return movimientos_legales;

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
            (!hay_pieza_tuya(posicion_siguiente,jugador,tab))&&
            (!hay_pieza_rival(posicion_siguiente,jugador,tab))&&
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
    //if (condiciones_final_de_la_partida(tab)) return void{}; // si hay jaque mate o tablas, no se realiza la jugada
    if (condiciones_jaque_mate(tab, tab[p_ini]->GetJugador())) return;
    auto jugador = tab[p_ini]->GetJugador();
    if (hay_pieza_rival(p_fin, jugador, tab)) tab.activar_captura(p_fin); // activa la captura si hay pieza rival en el destino
    
    tab.mover_pieza(p_ini, p_fin);

    // Aquí se comprueba la promoción del peón
    if (condiciones_promocion(*tab[p_fin])) {
        // elegir nuevo tipo
        Tipo nuevo_tipo = C;
        /*char opc;
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
        }*/
        // activar promoción
        tab.activar_promocion(p_fin, nuevo_tipo);
    }

}



void liberar_memoria(Tablero tab) {
}
