#ifndef GATO_INTERNO_H
#define GATO_INTERNO_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
enum class Jugador { Ninguno, X, O };
struct Celda
{
	sf::RectangleShape forma;
	Jugador jugador = Jugador::Ninguno;
	bool disponible = true;
};

class Gato {
public:
	Gato();
	bool EstaLleno();
	void HaGanado();
	Jugador GanadoPor();
	~Gato();
private: 
	int celdasJugadas;
	bool lleno;
	Jugador ganador;
	Celda **tablero;
};
#endif // !GATO_INTERNO_H
