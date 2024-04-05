#include "Casilla.h"

Casilla::Casilla(Color c) {
	color = c;
	hay_pieza = false;
	hay_rey = false;
}

void Casilla::print_color() {
	switch (color) {
	case Color::W:std::cout << "blanco"; break;
	case Color::B:std::cout << "negro"; break;
	}
}