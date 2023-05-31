#ifndef UTILIDADES_METAGATO_H
#define UTILIDADES_METAGATO_H
 #include <SFML/Graphics.hpp>
#include <iostream>
enum class Jugador { INDETERMINADO, X, O,NADIE };
struct Celda
{
	sf::RectangleShape forma;
	Jugador jugador = Jugador::INDETERMINADO;
};

void Tablero_I_Lleno(int fila, int columna, Celda** tablero, Jugador** tableroGrande);
void Tablero_I_Ganado(int fila, int columna, Celda** tableroPrincipal, Jugador** tableroGanados);

#endif // !UTILIDADES_METAGATO_H
