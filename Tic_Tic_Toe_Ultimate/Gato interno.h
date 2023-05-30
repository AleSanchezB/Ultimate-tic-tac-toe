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

class Gato 
{
public:
	Gato();
	int ObtenerCeldasJugadas();
	void EstablecerCeldasJugadas(int celdasJugadas);
	bool EstaLleno();
	void HaGanado();
	Jugador GanadoPor();
	~Gato();
	Celda** tablero;
private:
	int celdasJugadas;
	bool lleno;
	Jugador ganador;
};
#endif // !GATO_INTERNO_H