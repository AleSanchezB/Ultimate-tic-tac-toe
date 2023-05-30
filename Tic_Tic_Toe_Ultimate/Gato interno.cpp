#include "Gato interno.h"

Gato::Gato() 
{
	celdasJugadas = 0;
	lleno = false;
	ganador = Jugador::Ninguno;
	tablero = new Celda * [3];
	for (int i = 0; i < 3; i++)
	{
		tablero[i] = new Celda[3];
	}
}
/********************************************************************************************/
int Gato::ObtenerCeldasJugadas()
{
	return this->celdasJugadas;
}
/********************************************************************************************/
void Gato::EstablecerCeldasJugadas(int celdasJugadas)
{
	if (this->celdasJugadas == 9) lleno = true;
	else	this->celdasJugadas = celdasJugadas;
}
/********************************************************************************************/
bool Gato::EstaLleno() {
	return lleno;
}
/********************************************************************************************/
void Gato::HaGanado() {
	int JugX = 0, JugO = 0;
	//Checa de forma horizontal
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tablero[i][j].jugador == Jugador::X)JugX++;
			if (tablero[i][j].jugador == Jugador::O)JugO++;
		}
		if (JugX == 3) {
			std::cout << "Jugador 1 ha ganado.";
			ganador = Jugador::X;
		}
		if (JugO == 3) {
			std::cout << "Jugador 2 ha ganado";
			ganador = Jugador::O;
		}
	}
	JugX = 0;
	JugO = 0;
	//Checa de forma vertical
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tablero[j][i].jugador == Jugador::X)JugX++;
			if (tablero[j][i].jugador == Jugador::O)JugO++;
		}
		if (JugX == 3) {
			std::cout << "Jugador 1 ha ganado.";
			ganador = Jugador::X;
		}
		if (JugO == 3) {
			std::cout << "Jugador 2 ha ganado";
			ganador = Jugador::O;
		}
	}
	JugX = 0;
	JugO = 0;
	//Checa diagonal izquierda
	for (int i = 0; i < 3; i++) {
		if (tablero[i][i].jugador == Jugador::X)JugX++;
		if (tablero[i][i].jugador == Jugador::O)JugO++;
	}
	if (JugX == 3) {
		std::cout << "Jugador 1 ha ganado.";
		ganador = Jugador::X;
	}
	if (JugO == 3) {
		std::cout << "Jugador 2 ha ganado";
		ganador = Jugador::O;
	}
	JugX = 0;
	JugO = 0;
	//Checa diagonal derecha
	for (int i = 2; i >= 0; i--) {
		if (tablero[i][i].jugador == Jugador::X)JugX++;
		if (tablero[i][i].jugador == Jugador::O)JugO++;
	}
	if (JugX == 3) {
		std::cout << "Jugador 1 ha ganado.";
		ganador = Jugador::X;
	}
	if (JugO == 3) {
		std::cout << "Jugador 2 ha ganado";
		ganador = Jugador::O;
	}
	//Si no se encontró ganador, retorna valor NINGUNO
	ganador = Jugador::Ninguno;
}
/****************************************************************************************/
Jugador Gato::GanadoPor() {
	return ganador;
}
/****************************************************************************************/
Gato::~Gato()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] tablero[i];
	}

	delete[] tablero;

	tablero = NULL;
}