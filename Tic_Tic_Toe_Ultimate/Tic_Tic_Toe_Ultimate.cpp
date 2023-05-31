#include "Juego.h"
#include "MetaGato.h"

using std::cout;
int main()
{

	sf::RenderWindow ventana(sf::VideoMode(TAM_VENTANA, TAM_VENTANA), "Ultimate Tic Tac Toe");
	sf::View view(sf::FloatRect(0, 0, 540, 540));
	Celda** tableroMinis=nullptr; //este tablero contiene a los jugadores X o O
	bool** casillasDisponibles=nullptr; //tablero de 3x3 que repsenta dónde se puede jugar 
	Jugador** tableroGrande=nullptr; //tablero de 3x3 que simula al MetaGato como un gato normal
	sf::Event evento;
	//inicialización de todo lo necesario para representar al metagato
	try {
		InicializarTablero(tableroMinis, casillasDisponibles, tableroGrande);
	}
	catch (const std::bad_alloc&) {
		cout << "Error en la asignaci\xA2n de memoria. Saliendo del programa...";
		return 0;
	}
	catch (...) {
		cout << "Error inesperado. Saliendo del programa...";
		return 0;
	}

	Jugador jugadorActual = Jugador::X;
	while (ventana.isOpen())
	{
		while (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			else if (evento.type == sf::Event::MouseButtonPressed)
			{
				if (evento.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i posicionMouse = sf::Mouse::getPosition(ventana);
					if (ManejarClick(posicionMouse, jugadorActual, tableroMinis, casillasDisponibles, tableroGrande));
						jugadorActual = (jugadorActual == Jugador::X) ? Jugador::O : Jugador::X;
				}
			}
		}

		ventana.clear(sf::Color::White);
		dibujarTablero(ventana,tableroMinis);
		ventana.display();
	}
	for (int i = 0; i < 9; i++)
	{
		delete[] tableroMinis[i];
	}
	for (int i = 0; i < 3; i++)
	{
		delete[] tableroGrande[i];
		delete[] casillasDisponibles[i];
	}

	delete[] tableroMinis;
	delete[] casillasDisponibles;
	delete[] tableroGrande;

	tableroMinis = nullptr;
	casillasDisponibles = nullptr;
	tableroGrande = nullptr;

	return 0;
}