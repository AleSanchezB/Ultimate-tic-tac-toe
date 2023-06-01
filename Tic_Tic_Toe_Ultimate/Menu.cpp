#include "Menu.h"
#include "MetaGato.h"
#include <Windows.h>

void MostrarInstrucciones(sf::RenderWindow& ventana)
{
	sf::Event evento;
	sf::Texture imgInstrucciones[6]; //Texturas de los distintas imagenes de instrucciones
	sf::Sprite Instrucciones[6]; //Creacion de los objetos
	sf::Clock reloj;
	sf::Time tiempo;

	int Pagina = 0;
	const int FPS = 60;

	//Cargo las texturas de las instrucciones
	imgInstrucciones[0].loadFromFile("Assets/Menus/ins/0.png");
	imgInstrucciones[1].loadFromFile("Assets/Menus/ins/1.png");
	imgInstrucciones[2].loadFromFile("Assets/Menus/ins/2.png");
	imgInstrucciones[3].loadFromFile("Assets/Menus/ins/3.png");
	imgInstrucciones[4].loadFromFile("Assets/Menus/ins/4.png");
	imgInstrucciones[5].loadFromFile("Assets/Menus/ins/5.png");
	//Le agrego a los spirtes las texturas
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
			//Verifica si se ha presionado la flecha izquierda para regresar una presentacion
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (Pagina == 0) break;
				Pagina--;
			}
			//Verifica si se ha presionado la flecha derecha para avanzaar una presentacion
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (Pagina == 5) break;		//	Cuando la presentacion se terminaba, se regresa al menu principal
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		//	Se regresa al menu principal
			{
				break;
			}
		}

		ventana.clear(sf::Color::Black);
		ventana.draw(Creditos);
		ventana.display();
	}
}
void MostrarJuego(sf::RenderWindow& ventana)
{
	const int FPS = 60;

	sf::Clock Reloj;
	sf::Time tiempo;
	sf::Texture fondotexture;
	sf::Sprite Fondo;
	sf::Texture imgFlecha;
	sf::Sprite flecha;
	sf::Event evento;

	Jugador jugadorActual = Jugador::X;
	bool salir = false;
	int Ganador = 2;

	imgFlecha.loadFromFile("Assets/Menus/Flecha.png");
	flecha = sf::Sprite(imgFlecha);
	flecha.setPosition(560, 126);

	fondotexture.loadFromFile("Assets/Menus/Fondo.png");
	Fondo = sf::Sprite(fondotexture);


	Celda** tableroMinis = nullptr; //este tablero contiene a los jugadores X o O
	bool** casillasDisponibles = nullptr; //tablero de 3x3 que repsenta d�nde se puede jugar 
	Jugador** tableroGrande = nullptr; //tablero de 3x3 que simula al MetaGato como un gato normal

	InicializarTablero(tableroMinis, casillasDisponibles, tableroGrande);			//	Inicializacion de todo lo necesario para representar al metagato


	while (ventana.isOpen() && !salir)
	{
		tiempo = Reloj.getElapsedTime();
		while (ventana.pollEvent(evento) && tiempo.asSeconds() > 1 / FPS)
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
						Ganador = (jugadorActual == Jugador::X) ? 0 : 1;

						salir = true;
						break;
					}
					if (EstaLleno(tableroGrande)) {
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
	Sleep(1500);
	MostrarResultado(ventana, Ganador);
}
void MostrarResultado(sf::RenderWindow& ventana, int Ganador)
{
	sf::Event evento;
	sf::Text texto;
	sf::Text texto2;
	bool salir = false;
	sf::Texture imgResultado[3];
	sf::Sprite Resultado[3];

	//Cargo las texturas de los resultados
	imgResultado[0].loadFromFile("Assets/Menus/0.png");
	imgResultado[1].loadFromFile("Assets/Menus/1.png");
	imgResultado[2].loadFromFile("Assets/Menus/2.png");

	//Agrego las texturas al sprite
	Resultado[0] = sf::Sprite(imgResultado[0]);
	Resultado[1] = sf::Sprite(imgResultado[1]);
	Resultado[2] = sf::Sprite(imgResultado[2]);
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return;
	}
	texto.setFont(fuente);
	texto2.setFont(fuente);
	texto.setCharacterSize(20);
	texto2.setCharacterSize(20);
	while (ventana.isOpen() && !salir)
	{
		while (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))	//	Se espera a que el jugador presione espacio para volver al menu
			{
				salir = true;
				return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))	//	Se espera a que el jugador presione espacio para volver al menu
			{
				salir = true;
				MostrarJuego(ventana);
				return;
			}
		}
		//Borro y actualizo la pantalla
		ventana.clear(sf::Color::Black);
		ventana.draw(Resultado[Ganador]);

		texto.setString("Presiona espacio para volver al menu...");
		texto.setFillColor(sf::Color::White);
		texto.setPosition(790, 660);

		texto2.setString("Presiona backspace para jugar de nuevo...");
		texto2.setFillColor(sf::Color::White);
		texto2.setPosition(790, 690);

		ventana.draw(texto);
		ventana.draw(texto2);

		ventana.display();
	}
}
