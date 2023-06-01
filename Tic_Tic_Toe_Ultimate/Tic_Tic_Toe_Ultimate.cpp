#include "Juego.h"
#include "MetaGato.h"
#include <sstream>
#include <iomanip>

using std::cout;
void dibujarReloj(sf::RenderWindow& ventana, sf::Clock& reloj)
{
	// Obtener el tiempo transcurrido desde el inicio del reloj
	sf::Time tiempoTranscurrido = reloj.getElapsedTime();

	// Obtener la duración total en segundos
	int segundos = tiempoTranscurrido.asSeconds();

	// Calcular horas, minutos y segundos
	int horas = segundos / 3600;
	int minutos = (segundos % 3600) / 60;
	segundos = segundos % 60;

	// Crear una cadena de texto para mostrar el tiempo en formato HH:MM:SS
	std::ostringstream ss;
	ss << std::setfill('0') << std::setw(2) << horas << ":"
		<< std::setfill('0') << std::setw(2) << minutos << ":"
		<< std::setfill('0') << std::setw(2) << segundos;

	// Dibujar el texto del reloj debajo del tablero
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return;
	}

	sf::Text textoReloj;
	textoReloj.setFont(fuente);
	textoReloj.setCharacterSize(20);
	textoReloj.setString(ss.str());
	textoReloj.setFillColor(sf::Color::White);
	textoReloj.setPosition(50, ventana.getSize().y - 60);
	ventana.draw(textoReloj);
}

int main()
{
	sf::Clock Reloj;
	sf::Time tiempo;
	sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Ultimate Tic Tac Toe");
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
		dibujarReloj(ventana, Reloj);
		dibujarTablero(ventana,tableroMinis,casillasDisponibles,tableroGrande);
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