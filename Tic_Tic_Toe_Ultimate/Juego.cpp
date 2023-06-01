#include "Juego.h"

void MostrarInstrucciones(sf::RenderWindow& ventana)
{
	sf::Texture instrucciones[5];
	sf::Event evento;
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

				}
			}
		}

		ventana.clear(sf::Color::Black);

		ventana.display();
	}
}
void MostrarCreditos(sf::RenderWindow& ventana)
{
	sf::Event evento;
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

				}
			}
		}

		ventana.clear(sf::Color::Black);

		ventana.display();
	}
}
void MostrarJuego(sf::RenderWindow& ventana)
{
	sf::Clock Reloj;
	sf::Time tiempo;
	sf::View view(sf::FloatRect(0, 0, 540, 540));
	Celda** tableroMinis = nullptr; //este tablero contiene a los jugadores X o O
	bool** casillasDisponibles = nullptr; //tablero de 3x3 que repsenta d�nde se puede jugar 
	Jugador** tableroGrande = nullptr; //tablero de 3x3 que simula al MetaGato como un gato normal
	sf::Event evento;
	//inicializaci�n de todo lo necesario para representar al metagato
	try {
		InicializarTablero(tableroMinis, casillasDisponibles, tableroGrande);
	}
	catch (const std::bad_alloc&) {
		std::cout << "Error en la asignaci\xA2n de memoria. Saliendo del programa...";
		return;
	}
	catch (...) {
		std::cout << "Error inesperado. Saliendo del programa...";
		return;
	}

	Jugador jugadorActual = Jugador::X;
	while (ventana.isOpen())
	{
		tiempo = Reloj.getElapsedTime();
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
					if (ManejarClick(posicionMouse, jugadorActual, tableroMinis, casillasDisponibles, tableroGrande))
						jugadorActual = (jugadorActual == Jugador::X) ? Jugador::O : Jugador::X;
				}
			}
		}
		ventana.clear(sf::Color::Black);
		//dibujarReloj(ventana, Reloj);
		dibujarTablero(ventana, tableroMinis, casillasDisponibles, tableroGrande);
		ventana.display();
	}
}
void MostrarResultado(sf::RenderWindow& ventana)
{
	sf::Event evento;
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

				}
			}
		}

		ventana.clear(sf::Color::Black);

		ventana.display();
	}
}