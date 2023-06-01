#include <iostream>
#include "Menu.h"
#include "MetaGato.h"

void VerificarSeleccion(sf::RenderWindow& ventana, int posicionY);
enum { JUGAR = 285, INSTRUCCIONES = 377, CREDITOS = 469, SALIR = 561 };

int main()
{
	//Se crea una ventana de dimensiones 1280x720, nombre de la ventana y que no sea redimensionable
	sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Ultimate Tic Tac Toe", sf::Style::Close);
	sf::Event evento; //Variable que almacena cola de eventos

	//Se almacenan las texturas del menu y de la flecha
	sf::Texture imgDelMenu;
	sf::Texture imgFlecha;
	//Se crea los objetos, menu y flecha.
	sf::Sprite menu;
	sf::Sprite flecha;

	//Cargo las texturas
	imgDelMenu.loadFromFile("Assets/Menus/MENU NEON.png");
	imgFlecha.loadFromFile("Assets/Menus/Flecha.png");

	//Se agrega la texturas al objeto
	menu = sf::Sprite(imgDelMenu);
	flecha = sf::Sprite(imgFlecha);

	//Inicializo la posicion de le flecha.
	flecha.setPosition(217, 285);
	sf::Text texto;
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return 0;
	}
	//Bucle principal del programa.
	while (ventana.isOpen())
	{
		//Verifica si la cola de eventos contiene eventos
		if (ventana.pollEvent(evento))
		{
			//Verifica si la ventana a sido cerrada.
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			//Maneja la flecha del menu principal
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (flecha.getPosition().y > 285)
					flecha.setPosition(217, flecha.getPosition().y - 2 * 46);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (flecha.getPosition().y < 561)
					flecha.setPosition(217, flecha.getPosition().y + 2 * 46);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				try {
					VerificarSeleccion(ventana, flecha.getPosition().y); //Verifica en que opcion se encuentra la flecha y actua acorde
				}
				catch (const std::bad_alloc&) {
					std::cout << "Error en la asignaci\xA2n de memoria. Saliendo del programa...\n";
					return 0;
				}
				catch (...) {
					std::cout << "Error inesperado. Saliendo del programa...\n";
					return 0;
				}
			}
		}
		texto.setFont(fuente);
		texto.setCharacterSize(30);
		texto.setString("\"Utilice las flechas para moverse\"");
		texto.setFillColor(sf::Color::White);
		texto.setPosition(750, 680);
		
		//Borra y actuliza la ventana.
		ventana.clear(sf::Color::Black);
		ventana.draw(menu);
		ventana.draw(flecha);
		ventana.draw(texto);
		ventana.display();
	}
	return 0;
}

void VerificarSeleccion(sf::RenderWindow& ventana, int posicionY)
{
	switch (posicionY)
	{
	case JUGAR:
		MostrarJuego(ventana);
		break;
	case INSTRUCCIONES:
		MostrarInstrucciones(ventana);
		break;
	case CREDITOS:
		MostrarCreditos(ventana);
		break;
	case SALIR:
		ventana.close();
		break;
	default:
		break;
	}
}
