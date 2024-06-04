// Oye este código es puro comentario xdxdxdxd

/*

#include "freeglut.h"
#include "ETSIDI.h"
#include "GLTablero.h"

//#include "LogicaAjedrez.h" //¿NECESARIO?

//////////solo estoy comprobando si dibuja el sprite
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


//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
//void OnDraw(void); //esta funcion sera llamada para dibujar
//void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
//void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla


GLTablero scene; //chess global

int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(950,750);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, 950/750.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	//POSIBLE INICIALIZACION
		
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}






/*

void OnDraw(void)
{
	//Borrado de la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(5, 5, 17,  // posicion del ojo
		5.0, 5.0, 0.0,      // hacia que punto mira  (0,0,0)
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)


	pW.dibuja();
	pB.dibuja();
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
	glutTimerFunc(25,OnTimer,0);
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
	if (b == GLUT_RIGHT_BUTTON) {
		button = MOUSE_RIGHT_BUTTON;
		std::cout << "MOUSE_RIGHT_BUTTON" << std::endl;
	}
	int specialKey = glutGetModifiers();
	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;


	scene.MouseButton(x, y, b, down, sKey, ctrlKey);
	glutPostRedisplay();

}
*/
