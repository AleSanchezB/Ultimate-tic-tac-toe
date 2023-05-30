#include "Juego.h"
#include <SFML/Graphics.hpp>

const int tamanoVentana = 540;
const int tamanoCelda = tamanoVentana / 9;
const int tamanoTableroPequeno = tamanoCelda - 4;
int antX, antY;
bool primeravez;
enum class Jugador { Ninguno, X, O };
sf::RenderWindow ventana(sf::VideoMode(tamanoVentana, tamanoVentana), "Ultimate Tic Tac Toe");
sf::View view(sf::FloatRect(0, 0, 540, 540));

struct Celda
{
	sf::RectangleShape forma;
	Jugador jugador = Jugador::Ninguno;
};

Celda** tableroPrincipal; //este tablero contiene a los jugadores X o O
bool** tableroGrande; //tablero de 3x3 que repsenta el gato mas grande
bool** tableroDisponible; //tablero del mismo tamaño que el principal de 9x9 el cual contiene las posiciones que estan ocupadas
bool EstaLleno(int, int);
int HaGanado(int fila,int columna);
void celdasDisponibles(int fila, int columna);

void celdasDisponibles(int fila, int columna)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((i % 3) != fila % 3 && (j % 3) != columna % 3)
			{
				tableroDisponible[i][j] = (tableroDisponible[i][j]) ? false : true;
				tableroGrande[i / 3][j / 3] = (tableroGrande[i / 3][j / 3]) ? false : true;
			}
		}
	}
}
int HaGanado(int fila, int columna) {
	int JugX = 0, JugO = 0,aux=0;
	//Checa de forma horizontal
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++)
	{
		for (int j = 3 * (columna / 3); j < 3 * (columna / 3) + 3; j++)
		{
			if (tableroPrincipal[i][j].jugador == Jugador::X )JugX++;
			if (tableroPrincipal[i][j].jugador == Jugador::O)JugO++;
		}
		if (JugX == 3) {
			std::cout << "Jugador 1 ha ganado.";
			return 1;
		}
		if (JugO == 3) {
			std::cout << "Jugador 2 ha ganado";
			return 2;
		}
	}
	JugX = 0;
	JugO = 0;
	//Checa de forma vertical
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++)
	{
		for (int j = 3 * (columna / 3); j < 3 * (columna / 3) + 3; j++)
		{
			if (tableroPrincipal[j][i].jugador == Jugador::X)JugX++;
			if (tableroPrincipal[j][i].jugador == Jugador::O)JugO++;
		}
		if (JugX == 3) {
			std::cout << "Jugador 1 ha ganado.";
			return 1;
		}
		if (JugO == 3) {
			std::cout << "Jugador 2 ha ganado";
			return 2;
		}
	}
	JugX = 0;
	JugO = 0;
	//Checa diagonal izquierda
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++) {
		if (tableroPrincipal[i][columna+aux].jugador == Jugador::X)JugX++;
		if (tableroPrincipal[i][columna+aux].jugador == Jugador::O)JugO++;
	}
	if (JugX == 3) {
		std::cout << "Jugador 1 ha ganado.";
		return 1;
	}
	if (JugO == 3) {
		std::cout << "Jugador 2 ha ganado";
		return 2;
	}
	JugX = 0;
	JugO = 0;
	aux = 0;
	//Checa diagonal derecha
	for (int i = 3 * (fila / 3)+2; i >= 3 * (fila / 3); i--) {
		if (tableroPrincipal[i][columna+aux].jugador == Jugador::X)JugX++;
		if (tableroPrincipal[i][columna+aux].jugador == Jugador::O)JugO++;
		aux++;
	}
	if (JugX == 3) {
		std::cout << "Jugador 1 ha ganado.";
		return 1;
	}
	if (JugO == 3) {
		std::cout << "Jugador 2 ha ganado";
		return 2;
	}
	//Si no se encontró ganador, retorna valor NINGUNO
	return 0;
}
bool EstaLleno(int fila, int columna)
{
	int cont = 0;
	for (int i = 3*(fila/3); i < 3*(fila/3) + 3; i++)
	{
		for (int j = 3*(columna/3); j < 3*(columna/3) + 3; j++)
		{
			if (tableroPrincipal[i][j].jugador != Jugador::Ninguno) cont++;
		}
	}
	if (cont == 9) return true;
	return false;
}
bool manejarClick(sf::Vector2i posicionMouse, Jugador jugadorActual)
{
	int columna = posicionMouse.x % 540 / tamanoCelda;
	int fila = posicionMouse.y % 540 / tamanoCelda;

	int xPequeno = (posicionMouse.x % tamanoCelda) / tamanoTableroPequeno;
	int yPequeno = (posicionMouse.y % tamanoCelda) / tamanoTableroPequeno;
	if (tableroPrincipal[fila][columna].jugador == Jugador::Ninguno && tableroPrincipal[fila][columna].forma.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)
		&& (primeravez || (tableroGrande[fila / 3][columna / 3] && !EstaLleno(fila, columna))))
	{
		tableroPrincipal[fila][columna].jugador = jugadorActual;
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
		}
		return true;
	}
	else if (EstaLleno(fila, columna))
	{
		std::cout << "ola\n";
	}
	return false;
}

void dibujarTablero(sf::RenderWindow& ventana)
{
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return;
	}

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			const Celda& celda = tableroPrincipal[i][j];
			ventana.draw(celda.forma);

			sf::Text simbolo;
			simbolo.setFont(fuente);
			simbolo.setCharacterSize(40);

			if (celda.jugador == Jugador::X)
			{
				simbolo.setString("X");
				simbolo.setFillColor(sf::Color::Blue);
			}
			else if (celda.jugador == Jugador::O)
			{
				simbolo.setString("O");
				simbolo.setFillColor(sf::Color::Red);
			}
			else
				continue;

			sf::FloatRect limitesSimbolo = simbolo.getLocalBounds();
			simbolo.setOrigin(limitesSimbolo.left + limitesSimbolo.width / 2, limitesSimbolo.top + limitesSimbolo.height / 2);
			simbolo.setPosition(celda.forma.getPosition().x + tamanoTableroPequeno / 2, celda.forma.getPosition().y + tamanoTableroPequeno / 2);

			ventana.draw(simbolo);
		}
	}
}

void inicializarTablero()
{
	tableroPrincipal = new Celda * [9];
	tableroGrande = new bool* [3];
	tableroDisponible = new bool* [9];

	for (int i = 0; i < 9; i++)
	{
		tableroPrincipal[i] = new Celda[9];
		tableroDisponible[i] = new bool[9];
	}


	for (int i = 0; i < 3; i++)
	{
		tableroGrande[i] = new bool[3];
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tableroDisponible[i][j] = false;
			tableroGrande[i % 3][j % 3] = false;
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			sf::RectangleShape& forma = tableroPrincipal[i][j].forma;
			forma.setSize(sf::Vector2f(tamanoTableroPequeno, tamanoTableroPequeno));
			forma.setPosition(j * tamanoCelda + 2, i * tamanoCelda + 2);
			forma.setOutlineThickness(2);
			forma.setOutlineColor(sf::Color::Black);

			if ((i / 3) % 2 == 0 && (j / 3) % 2 == 0)
			{
				forma.setFillColor(sf::Color(255, 255, 0));
			}
			else if ((i / 3) % 2 == 1 && (j / 3) % 2 == 1)
			{
				forma.setFillColor(sf::Color(0, 255, 255));
			}
			else
			{
				forma.setFillColor(sf::Color::White);
			}
		}
	}
}


int main()
{
	sf::Event evento;
	inicializarTablero();
	Jugador jugadorActual = Jugador::X;
	primeravez = true;
	antX = 0;
	antY = 0;
	ventana.setView(view);
	while (ventana.isOpen())
	{
		while (ventana.pollEvent(evento))
		{
			sf::Vector2u windowSize = ventana.getSize();

			if (windowSize.x != view.getSize().x || windowSize.y != view.getSize().y)
			{
				view.setSize(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
				ventana.setView(view);
			}
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			else if (evento.type == sf::Event::MouseButtonPressed)
			{
				if (evento.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i posicionMouse = sf::Mouse::getPosition(ventana);
					if (manejarClick(posicionMouse, jugadorActual))
						jugadorActual = (jugadorActual == Jugador::X) ? Jugador::O : Jugador::X;
				}
			}
		}

		ventana.clear(sf::Color::White);
		dibujarTablero(ventana);
		ventana.display();
	}
	for (int i = 0; i < 9; i++)
	{
		delete[] tableroPrincipal[i];
		delete[] tableroDisponible[i];
	}
	for (int i = 0; i < 3; i++)
	{
		delete[] tableroGrande[i];
	}

	delete[] tableroDisponible;
	delete[] tableroPrincipal;
	delete[] tableroGrande;

	tableroDisponible = NULL;
	tableroPrincipal = NULL;
	tableroGrande = NULL;

	return 0;
}