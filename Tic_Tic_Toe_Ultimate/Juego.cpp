#include "Juego.h"

void MostrarInstrucciones(sf::RenderWindow& ventana)
{
	sf::Event evento;
	int Pagina = 0;
	sf::Texture imgInstrucciones[6];
	sf::Sprite Instrucciones[6];

	const int FPS = 60;
	sf::Clock reloj;
	sf::Time tiempo;

	imgInstrucciones[0].loadFromFile("Assets/Menus/ins/0.png");
	imgInstrucciones[1].loadFromFile("Assets/Menus/ins/1.png");
	imgInstrucciones[2].loadFromFile("Assets/Menus/ins/2.png");
	imgInstrucciones[3].loadFromFile("Assets/Menus/ins/3.png");
	imgInstrucciones[4].loadFromFile("Assets/Menus/ins/4.png");
	imgInstrucciones[5].loadFromFile("Assets/Menus/ins/5.png");

	Instrucciones[0] = sf::Sprite(imgInstrucciones[0]);
	Instrucciones[1] = sf::Sprite(imgInstrucciones[1]);
	Instrucciones[2] = sf::Sprite(imgInstrucciones[2]);
	Instrucciones[3] = sf::Sprite(imgInstrucciones[3]);
	Instrucciones[4] = sf::Sprite(imgInstrucciones[4]);
	Instrucciones[5] = sf::Sprite(imgInstrucciones[5]);

	while (ventana.isOpen())
	{
		tiempo = reloj.getElapsedTime();
		if (ventana.pollEvent(evento) && tiempo.asSeconds() > 1 / FPS)
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (Pagina > 0) Pagina--;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (Pagina == 5) break;
				Pagina++;
			}
		}
		ventana.clear(sf::Color::Black);
		ventana.draw(Instrucciones[Pagina]);
		ventana.display();
	}
}
void MostrarCreditos(sf::RenderWindow& ventana)
{
	sf::Event evento;
	sf::Texture imgCreditos;
	sf::Sprite Creditos;
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return;
	}
	imgCreditos.loadFromFile("Assets/Menus/CREDITOS NEON.png");
	Creditos = sf::Sprite(imgCreditos);

	while (ventana.isOpen())
	{
		if (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				break;
			}
		}

		ventana.clear(sf::Color::Black);
		ventana.draw(Creditos);
		sf::Text texto;
		texto.setFont(fuente);
		texto.setCharacterSize(30);
		texto.setString("Presiona backspace para salir...");
		texto.setFillColor(sf::Color::White);
		texto.setPosition(700, 660);
		ventana.draw(texto);
		ventana.display();
	}
}
void MostrarJuego(sf::RenderWindow& ventana)
{
	sf::Clock Reloj;
	sf::Time tiempo;
	sf::View view(sf::FloatRect(0, 0, 540, 540));
	sf::Texture fondotexture;
	sf::Sprite Fondo;
	sf::Texture imgFlecha;
	sf::Sprite flecha;
	const int FPS = 60;
	imgFlecha.loadFromFile("Assets/Menus/Flecha.png");
	flecha = sf::Sprite(imgFlecha);
	fondotexture.loadFromFile("Assets/Menus/Fondo.png");

	Fondo = sf::Sprite(fondotexture);

	Celda** tableroMinis = nullptr; //este tablero contiene a los jugadores X o O
	bool** casillasDisponibles = nullptr; //tablero de 3x3 que repsenta d�nde se puede jugar 
	Jugador** tableroGrande = nullptr; //tablero de 3x3 que simula al MetaGato como un gato normal
	sf::Event evento;
	//inicializacion de todo lo necesario para representar al metagato
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

	flecha.setPosition(560, 126);
	Jugador jugadorActual = Jugador::X;
	bool salir = false;
	int Ganador = 2;
	while (ventana.isOpen() && !salir)
	{
		tiempo = Reloj.getElapsedTime();
		if (ventana.pollEvent(evento) && tiempo.asSeconds() > 1 / FPS)
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			else if (evento.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i posicionMouse = sf::Mouse::getPosition(ventana);
				if (evento.mouseButton.button == sf::Mouse::Left && ValidarClick(posicionMouse, tableroMinis, casillasDisponibles, tableroGrande))
				{
					GestionJugada(posicionMouse, jugadorActual, tableroMinis, casillasDisponibles, tableroGrande);
					if (HaGanado(tableroGrande, jugadorActual)) {
						std::cout << "Un jugador ha ganado\n";
						//Aquí irían las gestiones de que alguien ganó
						Ganador = (jugadorActual == Jugador::X) ? 0 : 1;
						salir = true;
						break;
					}
					if (EstaLleno(tableroGrande)) {
						//Aquí irían las gestiones del empate
						Ganador = 2;
						salir = true;
						break;
					}
					if (jugadorActual == Jugador::X)
					{
						jugadorActual = Jugador::O;
						flecha.setPosition(560, 254);
					}
					else
					{
						jugadorActual = Jugador::X;
						flecha.setPosition(560, 126);
					}
				}
			}
		}
		ventana.clear(sf::Color::Black);
		ventana.draw(Fondo);
		dibujarReloj(ventana, Reloj);
		dibujarTablero(ventana, tableroMinis, casillasDisponibles, tableroGrande);
		ventana.draw(flecha);
		ventana.display();
	}
	LiberarMemoria(tableroMinis, tableroGrande, casillasDisponibles);
	MostrarResultado(ventana, Ganador);
}
void MostrarResultado(sf::RenderWindow& ventana, int Ganador)
{
	sf::Event evento;
	bool salir = false;
	sf::Texture imgResultado[3];
	sf::Sprite Resultado[3];

	imgResultado[0].loadFromFile("Assets/Menus/0.png");
	imgResultado[1].loadFromFile("Assets/Menus/1.png");
	imgResultado[2].loadFromFile("Assets/Menus/2.png");

	Resultado[0] = sf::Sprite(imgResultado[0]);
	Resultado[1] = sf::Sprite(imgResultado[1]);
	Resultado[2] = sf::Sprite(imgResultado[2]);
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return;
	}
	while (ventana.isOpen() && !salir)
	{
		while (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				salir = true;
				break;
			}
		}

		ventana.clear(sf::Color::Black);
		ventana.draw(Resultado[Ganador]);
		sf::Text texto;
		texto.setFont(fuente);
		texto.setCharacterSize(30);
		texto.setString("Presiona espacio para continuar...");
		texto.setFillColor(sf::Color::White);
		texto.setPosition(700, 660);
		ventana.draw(texto);
		ventana.display();
	}
}