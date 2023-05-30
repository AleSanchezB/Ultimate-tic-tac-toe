#include "FuncionesMouse.h"

bool manejarClick(sf::Vector2i posicionMouse, Jugador jugadorActual, Gatote& gatote)
{
	int columna = posicionMouse.x % 540 / 60;
	int fila = posicionMouse.y % 540 / 60;

	/*if (tableroPrincipal[fila][columna].jugador == Jugador::Ninguno && tableroPrincipal[fila][columna].forma.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)
		&& (primeravez || (tableroGrande[fila / 3][columna / 3] && !EstaLleno(fila, columna))))
	{*/
	if (gatote.tablerote[fila / 3][columna / 3].tablero[fila / 3][columna / 3].jugador == Jugador::Ninguno && 
		gatote.tablerote[fila / 3][columna / 3].tablero[fila / 3][columna / 3].forma.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
	{
		/*tableroPrincipal[fila][columna].jugador = jugadorActual;
		tableroDisponible[fila][columna] = false;
		tableroGrande[antY][antX] = false;

		tableroGrande[fila % 3][columna % 3] = true;
		std::cout << HaGanado(fila, columna);
		antX = columna % 3;
		antY = fila % 3;
		primeravez = false;
		if (EstaLleno(fila, columna))
		{
			std::cout << "esta lleno";
			celdasDisponibles(fila, columna);
		}*/
		gatote.tablerote[fila / 3][columna / 3].tablero[fila / 3][columna / 3].jugador = jugadorActual;
		gatote.tablerote[fila / 3][columna / 3].EstablecerCeldasJugadas(gatote.tablerote[fila / 3][columna / 3].ObtenerCeldasJugadas() + 1);
		return true;
	}
	else if (gatote.tablerote[fila / 3][columna / 3].EstaLleno())
	{
		std::cout << "ola\n";
	}
	return false;
}