#include <iostream>
#include "Tablero.h"
#include "freeglut.h"

using namespace std;





int main(){
	// codigo de prueba para ver si la clase se inicializa bien y tal
	Tablero mi_tab;
	cout << "hay " << mi_tab.size_rows() << " filas"
		<< " y " << mi_tab.size_columns() << " columnas\n\n";
	cout << "los colores son: \n";
	for (int i = 0; i < mi_tab.size_rows(); i++) {
		for (int j = 0; j < mi_tab.size_columns(); j++) {
			mi_tab.getCasilla(i, j).print_color();
			cout << ' ';
		}
		cout << '\n';
	}
}