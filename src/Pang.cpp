#include "freeglut.h"
#include "LogicaAjedrez.h"

#include "Coordinador.h"

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button, int state, int x, int y); //para eventos del mouse
/////////////////////////////////////////////////////

//Tablero tab;
//GLTablero scene; //Para el dibujo del tablero y casillas
Coordinador coordinador;


//Variables globales para la gestión de los clicks
Vector2D click_inicial{ -1, -1 };
Vector2D click_final{ -1,-1 };
bool seleccionado = true;
//true cuando estamos seleccionando la pieza inicial
//false cuando estamos seleccionando la posicion final



int main(int argc, char* argv[]){
	


//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ajedrez BALBO");

	/**///////habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);


	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);///////////////PRUEBA MOUSE
	//POSIBLE INICIALIZACION
	//coordinador.iniciar();

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


	
	//scene.dibuja(2);
	//El dibujar es llevado por el coordinador
	coordinador.dibuja();
	//Aparecerá la imagen de inicio
	

	
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
//captura los clicks del mouse
//da el control a la escena del tablero 
	bool down = (state == GLUT_DOWN);
	int button;
	if (b == GLUT_LEFT_BUTTON) {
		button = MOUSE_LEFT_BUTTON;
	}

	//scene.MouseButton(x, y, b, down, click_inicial, click_final, seleccionado);
	//El mouseBotton es llevado a acabo por el coordinador
	//coordinador.MouseBottom(x, y, b, down, click_inicial, click_final, seleccionado);
	
	
	glutPostRedisplay();

}
