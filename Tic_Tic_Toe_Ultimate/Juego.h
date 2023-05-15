#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Juego
{
public:
	Juego(int resolutionX, int resolutionY, std::string titulo, int fps = 60);
	~Juego();
	void dibujar();
	void GameLoop();
private:
	sf::RenderWindow* ventana;
	int fps;
	bool run;
	sf::Texture* textura;
	sf::Sprite* sprite;
	sf::View view;
};



