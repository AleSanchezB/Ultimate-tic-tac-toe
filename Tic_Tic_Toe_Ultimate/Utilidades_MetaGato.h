#ifndef UTILIDADES_METAGATO_H
#define UTILIDADES_METAGATO_H
 #include <SFML/Graphics.hpp>

enum class Jugador { INDETERMINADO, X, O,NADIE };
struct Celda
{
	sf::RectangleShape forma;
	Jugador jugador = Jugador::INDETERMINADO;
};

bool Tablero_I_Lleno(int fila, int columna, Celda** tablero);
void Tablero_I_Ganado(int fila, int columna, Celda** tableroPrincipal, Jugador** tableroGanados);

#endif // !UTILIDADES_METAGATO_H
