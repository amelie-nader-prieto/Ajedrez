#include "freeglut.h"
#include "LogicaAjedrez.h"
//#include "GLTablero.h"
#include "Coordinador.h"
#include "IA.h"

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button, int state, int x, int y); //para eventos del mouse


Tablero tab; //Para la gestión de la lógica

//Creamos el coordinador que gestionará los tableros y piezas
Coordinador coordinador;
//GLTablero scene; //Para el dibujo del tablero, casillas y piezas
//int EstadoSkin = 2;

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

	coordinador.iniciar();

	/*int i = 1;
	unsigned char key;
	while (i == 1) {
		coordinador.dibuja();

		std::cin >> key;
		coordinador.tecla(key);
	}
	*/

	return 0;


}

void lista_posibles_movimientos(Pieza p,Tablero tab, vector<Vector2D>& lista) {
	//auto movimientos = obtener_posibles_movimientos(*(tab.tablero[5][5]), tab);
	auto movimientos = obtener_posibles_movimientos(p.GetPosicion(), tab);
	int indice = 1;
	cout << "\n------------"<< p <<"------------\n";
	cout << "---------puede moverse a:-------\n";
	if (movimientos.size() == 0)cout << "...ningún sitio xd";
	else for (const auto& p : movimientos) {
		cout << indice << ". ";
		cout << p << '\t';
		indice++;
	}
	cout << "\n-----------------------------\n\n";
	//cout << "\n\n";
	lista = movimientos;
}

void imprime_info_tablero(Tablero tab) {
	tab.dibujar();
	tab.mostrar_lista_de_piezas();
}

void imprime_info_tablero_completa(Tablero tab) {
	
	imprime_info_tablero(tab);

	
	coordinador.iniciar();//Inicia el estado y la escena
	//scene.init(); //reempleza a (habilitar luces)


	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);//PRUEBA MOUSE funciona

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

}
void imprime_movimientos_pieza(Pieza p, Tablero tab, vector<Vector2D>& lista) {

	//vector<Vector2D>v{};
	Vector2D posicion_pieza = p.GetPosicion();
	Vector2D posicion_actual;
	auto movimientos = obtener_posibles_movimientos(posicion_pieza, tab);
	bool posible_movimiento = false;

}

/////////TODO LO DE PRINCIPAL.CPP//////////////////////////////
void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//funciones de dibujo
	//gluLookAt(scene.x_ojo, scene.y_ojo, scene.z_ojo,  // posicion del ojo
	gluLookAt( 5, 5, 16.25,
	5.0, 5.0, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)  


//	scene.dibuja(3);
//	scene.drawPieces(tab, 3);
	coordinador.dibuja(tab);


	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	coordinador.tecla(key);
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
	//captura los clicks del mouse
	//da el control a la escena del tablero 
	bool down = (state == GLUT_DOWN);
	int button;
	if (b == GLUT_LEFT_BUTTON) {
		button = MOUSE_LEFT_BUTTON;
	}

	//scene.MouseButton(x, y, b, down, click_inicial, click_final, seleccionado);
	//coordinador.MouseBottom(x, y, b, down, click_inicial, click_final, seleccionado);
	coordinador.MouseBottom(x, y, b, down, tab, click_inicial, click_final, seleccionado);

	Pieza seleccionada; // se inicializará con la pieza que hay en la posición que seleccionemos con el mouse

	// Comprobar que la casilla seleccionada con el mouse sea válida
	// si es válida, se inicializa el objeto pieza seleccionada
	/*
	* La casilla es válida si:
	* - está dentro del tablero
	* - hay una pieza en la casilla
	* - dicha pieza se puede mover
	*/
	if (tab[click_inicial]->GetTipo() == no_hay) cout << " CABRÓN AHÍ NO HAY NADA \n";
	if ((tab[click_inicial] != nullptr) &&
		tab[click_inicial]->GetTipo() != no_hay &&
		obtener_movimientos_legales(click_inicial, tab).size() > 0) {

		seleccionada = *tab[click_inicial];
		cout << "  (pieza seleccionada: " << seleccionada << ")   \n";

		for (auto p : obtener_movimientos_legales(click_inicial, tab)) {
			if (p == click_final) { // simplemente verificamos que el sitio en el que has hecho click está entre los posibles movimientos

				// mover pieza al lugar seleccionado
				mover_pieza(click_inicial, click_final, tab);
				tab.dibujar();
				cout << '\n';
				tab.mostrar_lista_de_piezas();
				cout << '\n';

				if (amenazado(tab.get_rey(B), tab)) cout << "   (Rn está amenazado)\n";
				if (amenazado(tab.get_rey(W), tab))cout << "   (Rb está amenazado)\n";

				if (condiciones_final_de_la_partida(tab)) {
					cout << "\nFIN DE LA PARTIDA\n";
					return void{};
				}

			}
		}



		glutPostRedisplay();

	}
}