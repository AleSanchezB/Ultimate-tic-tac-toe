#ifndef MANEJAR_MENUS
#define MANEJAR_MENUS
#include <SFML/Graphics.hpp>
void MostrarInstrucciones(sf::RenderWindow& ventana);
void MostrarCreditos(sf::RenderWindow& ventana);
void MostrarJuego(sf::RenderWindow& ventana);
void MostrarResultado(sf::RenderWindow& ventana, int Ganador);
#endif