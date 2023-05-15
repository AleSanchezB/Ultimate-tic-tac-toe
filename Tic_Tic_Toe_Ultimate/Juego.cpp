#include "Juego.h"

Juego::Juego(int resolutionX, int resolutionY, std::string titulo, int fps)
{
	this->ventana = new sf::RenderWindow(sf::VideoMode(resolutionX, resolutionY), titulo);
	this->fps = fps;
	this->run = false;
	this->ventana->setFramerateLimit(fps);

	this->textura = new sf::Texture;
	this->sprite = new sf::Sprite;

	this->textura->loadFromFile("1.png");
	this->sprite->setTexture(*this->textura);

	this->view.setSize(this->ventana->getSize().x, this->ventana->getSize().y);
	this->ventana->setView(view);
	GameLoop();
}

Juego::~Juego()
{
	delete sprite;
	delete textura;
	delete ventana;
}

void Juego::GameLoop()
{
	while (ventana->isOpen())
	{
		dibujar();

		sf::Event event;
		if (ventana->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				ventana->close();
			default:
				break;
			}
		}
		view.setSize(ventana->getSize().x, ventana->getSize().y);
		ventana->setView(view);
	}
}
void Juego::dibujar()
{
	this->ventana->clear(sf::Color::Blue);
	this->ventana->draw(*this->sprite);
	this->ventana->display();
}