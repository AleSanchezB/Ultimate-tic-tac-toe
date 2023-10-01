#include <SFML/Graphics.hpp>
#include "Juego.h"

void VerificarSeleccion(sf::RenderWindow& ventana,int posicionY);
enum {JUGAR = 285, INSTRUCCIONES = 377, CREDITOS = 469, SALIR = 561};
int main()
{
	sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Ultimate Tic Tac Toe");
	sf::View view(sf::FloatRect(0, 0, 540, 540));
	sf::Event evento;

	sf::Texture imgDelMenu;
	sf::Texture imgFlecha;
	sf::Sprite menu;
	sf::Sprite flecha;

	imgDelMenu.loadFromFile("Assets/Menus/MENU NEON.png");
	imgFlecha.loadFromFile("Assets/Menus/Flecha.png");

	menu = sf::Sprite(imgDelMenu);
	flecha = sf::Sprite(imgFlecha);

	flecha.setPosition(217, 285);
	//inicializacion de todo lo necesario para representar al metagato
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return 0;
	}
	while (ventana.isOpen())
	{
		if (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (flecha.getPosition().y > 285)
					flecha.setPosition(217, flecha.getPosition().y - 2*46);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (flecha.getPosition().y < 561)
					flecha.setPosition(217, flecha.getPosition().y + 2*46);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				VerificarSeleccion(ventana, flecha.getPosition().y);
			}
		}
		ventana.clear(sf::Color::Black);
		ventana.draw(menu);
		ventana.draw(flecha);
		sf::Text texto;
		texto.setFont(fuente);
		texto.setCharacterSize(30);
		texto.setString("\"Utilice las flechas para moverse\"");
		texto.setFillColor(sf::Color::White);
		texto.setPosition(750, 680);
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
