#include "Coordinador.h"


void Coordinador::dibuja(Tablero tab)
{
	string skin;
	switch (estado) {
	case MENU1://Imprimir el menu inicial
		imagen = "Menu/1.png";
		//	cout << "Pulsa S para jugar" << endl;
		//	cout << "Pulsa E para salir" << endl;
		break;
	case MENU2://
		imagen = "Menu/2.png";
		//cout << "Pulsa 1 para jugar contra jugador" << endl;
		//cout << "Pulsa 2 para jugar contra m�quina" << endl;
		break;
	case EXPLICACION:

		switch (graficas_tablero)
		{
		case 2: //StarWars
			imagen= "Menu/5.png";
				break;
		case 3: //AnimalCrossing
			imagen = "Menu/4.png";
			break;
		}
		//cout << "Se explican las fichas de " << graficas_tablero << endl;
		//cout << "Pulsa C para continuar" << endl;

		break;

	case PAUSA:
		imagen = "Menu/6.png";
		//cout << "Pulsa C para volver a jugar" << endl;
		//cout << "Pulsa E para volver a menu inicial" << endl;
		//cout << "Pulsa V para poner volumen en ON" << endl;
		//cout << "Pulsa S para poner volumen en OFF" << endl;
		break;

	case GRAFICOS:
		imagen = "Menu/3.png";
		//cout << "PULSE LA TECLA -1- PARA JUEGO MODO B�SICO" << endl;
		//cout << "PULSE LA TECLA -2- PARA JUAGO MODO STAR WORS" << endl;
		//cout << "PULSE LA TECLA -3- PARA JUAGO MODO ANIMAL CROSSING" << endl;
		//cout << "PULSE LA TECLA -E- PARA VOLVER" << endl;
		break;
		;
	case JUEGO:
		//musica();
		//cout << "Se esta jugando al: " << graficas_tablero << endl;
		//cout << "Pulsa M para ir a pausa" << endl;
		std::string skin = "default";
		std::string direccion = "";

		switch (graficas_tablero)
		{
		case 1: //Default
			skin = "default";
			break;
		case 2: //StarWars
			skin = "StarWars";
			break;
		case 3: //AnimalCrossing
			skin = "AnimalCrossing";
			break;
		}
		imagen =  skin + "/Fondo.png";

		///////////////////M�SICA///////////////////////////

		std::string direccionM = "";
		direccionM = "bin/sonidos/" + skin + "/Fondo.WAV";
		const char* rutaM = direccionM.c_str();

		if (volumen == ON) {
			ETSIDI::play(rutaM);
		}
		///////////////////////////////////////////////////
		mundo_grafico.dibuja_casillas(graficas_tablero);
		mundo_grafico.drawPieces(tab, graficas_tablero);

		break;
	}
	string direccion = "bin/imagenes/" + imagen;
	const char* ruta = direccion.c_str();
	imagenes(ruta);
}




void Coordinador::tecla(unsigned char key)
{
	switch (estado) {
	case MENU1:
		if (key == 'e') exit(0);
		if (key == 's')
		{
			estado = MENU2;
		}
		break;

	case MENU2:
		if (key == '1') //Modelidad contra m�quina
			modalidad = jugadores;
		if (key == '2')//Modalidad contra 2 jugadores
			modalidad = maquina;
		estado = GRAFICOS;
		break;

	case GRAFICOS:
		if (key == 'e') {
			estado = MENU1; //Se ir� al menu inicial
			break;
		}
		if (key == '1') {
			graficas_tablero = classic;
			estado = JUEGO;//Se ir� al tablero tipo1
			break;
		}
		if (key == '2') graficas_tablero = starwors;//Se ir� al tablero tipo2
		if (key == '3') graficas_tablero = animal;//Se ir� al tablero tipo3

		//mundo_grafico.init();//Se inicia la grafica del tablero deseado
		estado = EXPLICACION;
		break;

	case EXPLICACION:
		if (key == 'c')
			estado = JUEGO;
		break;
	case JUEGO:
		if (key == 'm') estado = PAUSA;
		//mundo_grafico.tecla(key);
		break;
	case PAUSA:
		if (key == 'c')
			estado = JUEGO;
		if (key == 'e')
			estado = MENU1;
		if (key == 'v')
			volumen = ON;
		if (key == 's')
			volumen = OFF;
		break;
	case GAMEOVER:
		if (key == 'r')
			estado = MENU2;
		if (key == 'e')
			estado = FIN;
		break;
	case FIN:
		exit(0);
		break;
	}
}

void Coordinador::imagenes(const char* ruta) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3d(-3.33, -1.2,-1);
	glTexCoord2d(1, 1); glVertex3d(13.24, -1.2, -1);
	glTexCoord2d(1, 0); glVertex3d(13.24, 11.18, -1);
	glTexCoord2d(0, 0); glVertex3d(-3.33, 11.18, -1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

}

/*
void Coordinador::tecla_especial(unsigned char key)
{
	if (estado == JUEGO)
		mundo_grafico.tecla_especial(key);
}
void Coordinador::mueve()
{
	if (estado == JUEGO)
		mundo_grafico.mueve();
}
*/

void Coordinador::MouseBottom(int x, int y, int button, bool down, Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado)
{
	if (estado == JUEGO)
	{
		mundo_grafico.MouseButton(x, y, button, down, click_inicial, click_final, seleccionado);
	}
}


void Coordinador::iniciar()
{
	estado = MENU1;
	mundo_grafico.init();
}

//Coordinador::~Coordinador() {}


void Coordinador::musica() {
	switch (graficas_tablero)
	{
	case classic:
		ETSIDI::play("bin/sonidos/Classic.WAV");
		break;
	case starwors:
		ETSIDI::play("bin/sonidos/Star_Wars.WAV");
		break;
	case animal:
		ETSIDI::play("bin/sonidos/Animal_Crossing.WAV");
		break;
	default:
		break;
	}
}