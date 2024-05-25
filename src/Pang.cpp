#include "freeglut.h"
#include "LogicaAjedrez.h"
#include "GLTablero.h"

//solo estoy comprobando si dibuja el sprite despues
//eliminar estas lineas 
#include "peon.h"
#include "torre.h"
#include "alfil.h"
#include "rey.h"
#include "dama.h"
#include "caballo.h"
Peon pW(3, 4, Jugador::W);
Alfil aW(3, 5, Jugador::W);
Torre tW(3, 6, Jugador::W);
Dama dW(4, 8, Jugador::W);
Caballo cW(4, 9, Jugador::W);
Rey rW(4, 10, Jugador::W);

Peon pB(8, 6, Jugador::B);
Alfil aB(9, 5, Jugador::B);
Torre tB(9, 6, Jugador::B);
Dama dB(9, 8, Jugador::B);
Caballo cB(9, 9, Jugador::B);
Rey rB(9, 10, Jugador::B);


void pruebaMovimeinto(); //solo compruebo el movimiento, despues eliminar

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button, int state, int x, int y); //para eventos del mouse
/////////////////////////////////////////////////////

Tablero tab;
GLTablero scene; //Para el dibujo del tablero y casillas

int main(int argc, char* argv[]){
	// vamos a crear un tablero para ver si funciona bien


	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			// vamos a comprobar si est�n bien las posiciones de memoria
			if (tab.tablero[i][j])
			{
				cout << (tab.tablero[i][j]->GetPosicion()) << ":\t";
				cout << tab.tablero[i][j] << '\n';
			}
		}
		cout << '\n';
	}

	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			// comprobamos si se han creado las piezas correctamente
			if (tab.tablero[i][j]) {
				if (tab.tablero[i][j]->GetTipo() != no_hay){
					cout << "(" << i << ',' << j << ")" << '\t';
					cout << (*tab.tablero[i][j]) << '\n';
				}
			}
		}
	}

	// por favor enlazador no me traiciones
	std::cout << "Estado inicial del tablero" << std::endl;
	dibujar(tab); 

	pruebaMovimeinto();


//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ajedrez BALBO");

	scene.init(); //reempleza a (habilitar luces, cuando ya se defina en donde va el main;

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




/////////////////////////////////////////////////////////////////
/////////TODO LO DE PRINCIPAL.CPP//////////////////////////////
void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//funciones de dibujo

	gluLookAt(5, 5, 17,  // posicion del ojo
		5.0, 5.0, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)  


	//pW.dibuja();
	//pB.dibuja();
	//aW.dibuja();
	//aB.dibuja();
	//tB.dibuja();
	//tW.dibuja();
	//cB.dibuja();
	//cW.dibuja();
	//rB.dibuja();
	//rW.dibuja();
	//dW.dibuja();
	//dB.dibuja();
	scene.dibuja();

	tab.dibujaPiezas();
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado

	glutPostRedisplay();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion


		//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y) {
	//////////////
//captures clicks with mouse with or without special keys (CTRL or SHIFT)
//gives control to board scene
	bool down = (state == GLUT_DOWN);
	int button;
	if (b == GLUT_LEFT_BUTTON) {
		button = MOUSE_LEFT_BUTTON;
	}

	scene.MouseButton(x, y, b, down);
	glutPostRedisplay();

}

void pruebaMovimeinto() {
	// Intentar mover una pieza Blanco
	std::cout << "Mover peon blanco de (2, 2) a (3, 2):" << std::endl;
	tab.mover_pieza(Vector2D(2, 2), Vector2D(3, 2));
	dibujar(tab);
}