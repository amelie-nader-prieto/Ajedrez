#include "freeglut.h"
#include "ETSIDI.h"
#include "GLTablero.h"
#include "LogicaAjedrez.h"

//////////Comprobación de cómo se dibujan las piezas, se sintentizará más adelante
#include "peon.h"

int S=2;
Peon pW4(3, 3, Jugador::W);
Peon pW3(3, 4, Jugador::W);
Peon pW2(3, 5, Jugador::W);
Peon pW(3, 6, Jugador::W);
Peon pW5(3, 7, Jugador::W);
Peon pW6(3, 8, Jugador::W);
Peon pW7(3, 9, Jugador::W);

Peon pB(8, 3, Jugador::B);
Peon pB2(8, 4, Jugador::B);
Peon pB3(8, 5, Jugador::B);
Peon pB4(8, 6, Jugador::B);
Peon pB5(8, 7, Jugador::B);
Peon pB6(8, 8, Jugador::B);
Peon pB7(8, 9, Jugador::B);

Alfil AW(2, 6, Jugador::W);
Alfil AW1(1, 6, Jugador::W);
Alfil AB(10, 6, Jugador::B);
Alfil AB1(9, 6, Jugador::B);

Rey RW(1, 5, Jugador::W);
Rey RB(10, 5, Jugador::B);

Dama DW(1, 7, Jugador::W);
Dama DB(10, 7, Jugador::B);

Caballo CW(2, 5, Jugador::W);
Caballo CW1(2, 7, Jugador::W);
Caballo CB(9, 5, Jugador::B);
Caballo CB1(9, 7, Jugador::B);

Torre TW(2, 4, Jugador::W);
Torre TW1(2, 8, Jugador::W);
Torre TB(9, 4, Jugador::B);
Torre TB1(9, 8, Jugador::B);



//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	

//////////PRUEBA MOUSE//////////77
//void OnMouseClick(int button, int state, int x, int y);


GLTablero scene; //chess

/*

int main(int argc,char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ajedrez BALBO");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, 800/600.0f, 0.1, 150);

	//scene.init(); //Cundo ya e defina el main

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	//POSIBLE INICIALIZACION
		
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}
*/

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


	pW.dibuja(S);
	pW2.dibuja(S);
	pW3.dibuja(S);
	pW4.dibuja(S);
	pW5.dibuja(S);
	pW6.dibuja(S);
	pW7.dibuja(S);
	pB.dibuja(S);
	pB2.dibuja(S);
	pB3.dibuja(S);
	pB4.dibuja(S);
	pB5.dibuja(S);
	pB6.dibuja(S);
	pB7.dibuja(S);

	AW.dibuja(S);
	AW1.dibuja(S);
	
	AB.dibuja(S);
	AB1.dibuja(S);

	RW.dibuja(S);
	RB.dibuja(S);

	DW.dibuja(S);
	DB.dibuja(S);

	CW.dibuja(S);
	CW1.dibuja(S);
	CB.dibuja(S);
	CB1.dibuja(S);

	TW.dibuja(S);
	TW1.dibuja(S);
	TB.dibuja(S);
	TB1.dibuja(S);

	scene.dibuja(S);

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