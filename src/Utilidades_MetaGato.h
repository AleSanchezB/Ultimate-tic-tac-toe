#ifndef UTILIDADES_METAGATO_H
#define UTILIDADES_METAGATO_H
#include <SFML/Graphics.hpp>
enum class Jugador { INDETERMINADO, X, O,NADIE };
struct Celda
{
	sf::RectangleShape forma;
	Jugador jugador = Jugador::INDETERMINADO;
};

void Tablero_I_Lleno(int fila, int columna, Celda** tablero, Jugador** tableroGrande, bool**);
void Tablero_I_Ganado(int fila, int columna, Celda** tableroPrincipal, Jugador** tableroGanados, bool**, Jugador);
void LiberarMemoria(Celda**, Jugador**, bool**);
void dibujarReloj(sf::RenderWindow& ventana, sf::Clock& reloj);
#endif // !UTILIDADES_METAGATO_H
