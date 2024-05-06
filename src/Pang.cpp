#include <iostream>
#include "LogicaAjedrez.h"

#define FILA 10
#define COLUMNA 11

///////SOLO ES UNA PRUEBA (¿EN DÓNDE VA EL MAIN?)/////////////////////7
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
///////////7SOLO ES UNA PRUEBA DE MOUSE////////////Ç
void OnMouseClick(int button, int state, int x, int y);
/////////////////////////////////////////////////////



//Esta función hace que cuando se quiera iniciar una pieza se manda el tipo y dirección 
void iniciar(Tipo tipo, Vector2D posicion,Jugador j)
{
	switch (tipo)
	{
	case D:
		Tablero[posicion.x][posicion.y] = new Dama(posicion.x, posicion.y,j); 
		break;
	case P:
		Tablero[posicion.x][posicion.y] = new Peon(posicion.x, posicion.y, j); //Tablero[posicion.x][posicion.y].dibuja();
		break;
	case T:
		Tablero[posicion.x][posicion.y] = new Torre(posicion.x, posicion.y,j);
		break;
	case C:
		Tablero[posicion.x][posicion.y] = new Caballo(posicion.x, posicion.y,j);
		break;
	case R:
		Tablero[posicion.x][posicion.y] = new Rey(posicion.x, posicion.y,j);
		break;
	case A:
		Tablero[posicion.x][posicion.y] = new Alfil(posicion.x, posicion.y,j);
		break;
	case no_hay:
		Tablero[posicion.x][posicion.y] = new No_pieza(posicion.x, posicion.y);
		break;
	default:
		break;
	}
}

//En esta función se mandará la pieza y se dará la dirección final 
void cambio_casilla(Pieza& pieza, Vector2D final) {

	// No permite acceder a casillas que se salgan del tablero o del rombo
	if (no_se_usa(final.x, final.y) ||
		(final.x < 0 || final.y < 0 || final.x >= COLUMNA || final.y >= FILA)) {
		return void{};
	}

	bool movimiento_posible = false;

	// No permite acceder a casillas que no estén entre los movimientos permitidos de la pieza
	for (const auto& p : obtener_posibles_movimientos(pieza)) {
		if (final.x == p.row && final.y == p.col) {
			movimiento_posible = true;
			break;
		}
	}

	if (!movimiento_posible)return void{};

	Vector2D inicio = pieza.GetPosicion();

	// la casilla en la que estabas se queda vacía
	iniciar(no_hay, { inicio },B);
	// vuelve a crear la pieza en la posición final
	iniciar(pieza.GetTipo(), { final },pieza.GetJugador());

}

// BUCLE PARA DIBUJAR EL TABLERO
void dibujar_tablero() {
	/*for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			if (Tablero[i][j])
				std::cout << "[" << Tablero[i][j]->GetTipo() << "]";

			else
				std::cout << "   ";
		}
		std::cout << std::endl;
	}*/

	
	for (auto i = 0; i < FILA; i++) {
		for (auto j = 0; j < COLUMNA; j++) {
			if (Tablero[i][j])
				std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
			else
				std::cout << "   ";
		}
		std::cout << ' ' << FILA - i << std::endl;
	}

	std::cout << " a  b  c  d  e  f  g  h  i  j  k" << std::endl;

}

// Dibujar según el color
void dibujar_tablero(Jugador color) {

	for (auto i = 0; i < FILA; i++) {
		for (auto j = 0; j < COLUMNA; j++) {
			if (Tablero[i][j]) {
				if (Tablero[i][j]->GetJugador() == color)
					std::cout << "[" << Tablero[i][j]->GetTipo() << "]";
				else std::cout << "[ ]";
			}
			else
				std::cout << "   ";
		}
		std::cout << '\n';
	}

}

int main(int argc, char* argv[])
{

	//Colocar los espacios donde puede haber piezas
	//Espacio_tablero(Tablero[FILA][COLUMNA]);
	for (auto i = 9; i >= 0; i--)
	{
		for (auto j = 10; j >= 0; j--)
		{
			// CASILLAS EN LAS QUE INICIALMENTE NO HAY PIEZAS
			if (
				((j == 10 || j == 0) && (i == 4 || i == 5)) ||
				((j == 9 || j == 1) && (i == 4 || i == 5 || i == 3 || i == 6)) ||
				((j == 8 || j == 2) && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7)) ||
				((j == 7 || j == 3) && (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8)) ||
				(j == 4 || j == 5 || j == 6) )
			{
				Tablero[i][j] = new No_pieza(i, j);
			}

		}
	}

	
		//Establecer piezas en el tablero
	// Peones
		for (int i = 2; i <= 8;i++)
		{
			iniciar(P, { 2,i },B);//creación peones (negro)
			iniciar(P, { 7,i },W);//creación peones (blanco)
		}
		//Creación de las fichas de la fila intermedia
		// T C A C T
		vector<Tipo>tipos_fila_2{ T,C,A,C,T };
		int j = 3;
		for (const auto& p : tipos_fila_2) {
			iniciar(p, { 1,j },B); // creación fichas (negro)
			iniciar(p, { 8,j },W); // creación fichas (blanco)
			j++;
		}
		//Creación de las fichas de la fila del fondo
		//  R  A  D
		vector<Tipo>tipos_fila_3{ R,A,D };
		j = 4;
		for (const auto& p : tipos_fila_3) {
			iniciar(p, { 0,j }, B); // creación fichas (negro)
			iniciar(p, { 9,j }, W); // creación fichas (blanco)
			j++;
		}


		// verificamos si se han inicializado los colores
		//std::cout << "\n\n\n";
		//std::cout << " blanco\n";
		//dibujar_tablero(W);
		//std::cout << "\n\n\n";
		//std::cout << "negro\n";
		//dibujar_tablero(B);
		//std::cout << "\n\n\n";


		// dibujamos el tablero
		dibujar_tablero();
		std::cout << "\n\n\n";

		//Prueba de cambio de casilla
		// movemos el peón
		cambio_casilla(*Tablero[2][4], {3,4});
		dibujar_tablero();
		std::cout << "\n\n\n";

		// probamos a mover más piezas
		cambio_casilla(*Tablero[2][5], {
			obtener_posibles_movimientos(*Tablero[2][5])[0].row,
			obtener_posibles_movimientos(*Tablero[2][5])[0].col
			});
		dibujar_tablero();
		std::cout << "\n\n\n";

		cambio_casilla(*Tablero[1][5], {
			obtener_posibles_movimientos(*Tablero[1][5])[2].row,
			obtener_posibles_movimientos(*Tablero[1][5])[2].col
			});
		dibujar_tablero();
		std::cout << "\n\n\n";


	// Liberar la memoria al final del programa
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 11; ++j) {
			delete Tablero[i][j]; // Liberar la memoria de cada pieza
		}
	}



	/////////////SOLO ES UNA PRUEBA////////////////////

	//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ajedrez BALBO");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//scene.init(); //reempleza a (habilitar luces, cuando ya se defina en donde va el main;

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);///////////////PRUEBA MOUSE
	//POSIBLE INICIALIZACION

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

