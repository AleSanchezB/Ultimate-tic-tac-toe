#include "Juego.h"
#include <SFML/Graphics.hpp>
#include "FuncionesMouse.h"

const int tamanoVentana = 540;
const int tamanoCelda = tamanoVentana / 9;
const int tamanoTableroPequeno = tamanoCelda - 4;
int antX, antY;
bool primeravez;
sf::RenderWindow ventana(sf::VideoMode(tamanoVentana, tamanoVentana), "Ultimate Tic Tac Toe");
sf::View view(sf::FloatRect(0, 0, 540, 540));

Gatote gatote;

Celda** tableroPrincipal; //este tablero contiene a los jugadores X o O
bool** tableroGrande; //tablero de 3x3 que repsenta el gato mas grande
bool** tableroDisponible; //tablero del mismo tamaño que el principal de 9x9 el cual contiene las posiciones que estan ocupadas
bool EstaLleno(int, int);
int HaGanado(int fila, int columna);
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
	int JugX = 0, JugO = 0;
	//Checa de forma horizontal
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++)
	{
		for (int j = 3 * (columna / 3); j < 3 * (columna / 3) + 3; j++)
		{
			if (tableroPrincipal[i][j].jugador == Jugador::X)JugX++;
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
		if (tableroPrincipal[i][columna].jugador == Jugador::X)JugX++;
		if (tableroPrincipal[i][columna].jugador == Jugador::O)JugO++;
		columna++;
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
	//Checa diagonal derecha
	for (int i = 3 * (fila / 3) + 2; i >= 3 * (fila / 3); i--) {
		if (tableroPrincipal[i][columna].jugador == Jugador::X)JugX++;
		if (tableroPrincipal[i][columna].jugador == Jugador::O)JugO++;
		columna++;
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
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++)
	{
		for (int j = 3 * (columna / 3); j < 3 * (columna / 3) + 3; j++)
		{
			if (tableroPrincipal[i][j].jugador != Jugador::Ninguno) cont++;
		}
	}
	if (cont == 9) return true;
	return false;
}


void dibujarTablero(sf::RenderWindow& ventana)
{
	sf::Font fuente;
	if (!fuente.loadFromFile("Minecraft.ttf"))
	{
		return;
	}
	std::cout << "Dibujando tablero\n";
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				for (int u = 0; u < 3; ++u)
				{
					const Celda& celda = gatote.tablerote[i][j].tablero[k][u];
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
	}
}

void inicializarTablero()
{
	std::cout << "Iniciando tablero\n";
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				for (int u = 0; u < 3; ++u)
				{
					std::cout << "i: " << i << " j: " << j << " k: " << k << " u: " << u << "\n";
					sf::RectangleShape& forma = gatote.tablerote[i][j].tablero[k][u].forma;
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
	}
}


int main()
{
	gatote = Gatote();
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
					if (manejarClick(posicionMouse, jugadorActual, gatote))
						jugadorActual = (jugadorActual == Jugador::X) ? Jugador::O : Jugador::X;
				}
			}
		}

		ventana.clear(sf::Color::White);
		dibujarTablero(ventana);
		ventana.display();
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gatote.tablerote[i][j].~Gato();
		}
	}


	gatote.~Gatote();
	return 0;
}