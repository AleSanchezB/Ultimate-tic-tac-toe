#include "MetaGato.h"

Jugador HaGanado(Jugador** tableroGanados, Jugador quienJugo) {
	int  jugVer = 0, jugHor = 0, jugDiagIzq = 0, jugDiagDer = 0;
	//Checa líneas verticales y horizontales
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//Lineas verticales
			if (tableroGanados[i][j] == quienJugo)jugVer++;
			//Lineas horizontales
			if (tableroGanados[j][i] == quienJugo)jugHor++;
		}
		//Diagonales izquierdas
		if (tableroGanados[i][i] == quienJugo)  jugDiagIzq++;
		//Diagonales derechas
		if (tableroGanados[2 - i][2 - i] == quienJugo) jugDiagDer++;
		//Verifica ganador, si lo hay
		if (jugVer == 3 || jugHor == 3) {
			return quienJugo;
		}
		jugVer = 0;
		jugHor = 0;
	}
	if (jugDiagIzq == 3 || jugDiagDer == 3) {
		return quienJugo;
	}
	return Jugador::INDETERMINADO;
}
/****************************************************************************************************/

void InicializarTablero(Celda**& tableroMinis, bool**& casillaJugable, Jugador**& tableroGrande)
{
	tableroMinis = new Celda * [9];
	casillaJugable = new bool* [3];
	tableroGrande = new Jugador * [3];

	for (int i = 0; i < 3; i++)
	{
		casillaJugable[i] = new bool[3];
		tableroGrande[i] = new Jugador[3];
		for (int j = 0; j < 3; j++) {
			casillaJugable[i][j] = true;
			tableroGrande[i][j] = Jugador::INDETERMINADO;
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		tableroMinis[i] = new Celda[9];
		for (int j = 0; j < 9; ++j)
		{
			sf::RectangleShape& forma = tableroMinis[i][j].forma;
			forma.setSize(sf::Vector2f(TAM_TAB_PEQ, TAM_TAB_PEQ));
			//forma.setPosition(j * TAM_CELDA + 2, i * TAM_CELDA + 2);
			//forma.setPosition(j * TAM_CELDA + (1280 - 720) + 2, i * TAM_CELDA + 2);
			forma.setPosition(j * TAM_CELDA + 10, i * TAM_CELDA + 20);
			forma.setOutlineThickness(4);
			forma.setOutlineColor(sf::Color(208, 0, 152));

			if ((i / 3) % 2 == 0 && (j / 3) % 2 == 0)
			{
				forma.setFillColor(sf::Color(0, 9, 138));
			}
			else if ((i / 3) % 2 == 1 && (j / 3) % 2 == 1)
			{
				forma.setFillColor(sf::Color(99, 0, 135));
			}
			else
			{
				forma.setFillColor(sf::Color::Black);
			}
		}
	}
}
/****************************************************************************************************/

void dibujarTablero(sf::RenderWindow& ventana, Celda** tableroMinis, bool** casillasDisponibles, Jugador** tableroGrande)
{
	sf::Font fuente;
	if (!fuente.loadFromFile("minecraft.ttf"))
	{
		return;
	}
	sf::RectangleShape cuadrado;
	cuadrado.setSize(sf::Vector2f(TAM_CELDA * 3 + 4, TAM_CELDA * 3 + 4));
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			const Celda& celda = tableroMinis[i][j];
			ventana.draw(celda.forma);

			sf::Text simbolo;
			simbolo.setFont(fuente);
			simbolo.setCharacterSize(40);

			if (celda.jugador == Jugador::X)
			{
				simbolo.setString("X");
				simbolo.setFillColor(sf::Color::Magenta);
			}
			else if (celda.jugador == Jugador::O)
			{
				simbolo.setString("O");
				simbolo.setFillColor(sf::Color::Cyan);
			}
			else
				continue;

			sf::FloatRect limitesSimbolo = simbolo.getLocalBounds();
			simbolo.setOrigin(limitesSimbolo.left + limitesSimbolo.width / 2, limitesSimbolo.top + limitesSimbolo.height / 2);
			simbolo.setPosition(celda.forma.getPosition().x + TAM_TAB_PEQ / 2, celda.forma.getPosition().y + TAM_TAB_PEQ / 2);

			ventana.draw(simbolo);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cuadrado.setPosition(TAM_CELDA * j * 3 + 6, TAM_CELDA * i * 3 + 16); // Posición del cuadrado en la esquina superior izquierda
			if (!casillasDisponibles[i][j] || tableroGrande[i][j] != Jugador::INDETERMINADO)
			{
				cuadrado.setFillColor(sf::Color(0, 0, 0, 150)); // Color rojo transparente (128 de opacidad)
			}
			else cuadrado.setFillColor(sf::Color(255, 255, 255, 15)); // Color azul transparente (128 de opacidad)
			ventana.draw(cuadrado);
		}
	}
	sf::Text texto;
	texto.setFont(fuente);
	texto.setCharacterSize(20);
	texto.setString("Tiempo de Juego");
	texto.setFillColor(sf::Color::White);
	texto.setPosition(50, ventana.getSize().y - 110);
	ventana.draw(texto);
}

/****************************************************************************************************/

void TodasLibres(bool** casillasDisponibles) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			casillasDisponibles[i][j] = true;
		}
	}
}
/****************************************************************************************************/

void CasillaJugable(bool** casillasDisponibles, int fila, int columna) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == fila && j == columna)casillasDisponibles[i][j] = true;
			else casillasDisponibles[i][j] = false;
		}
	}
}
/****************************************************************************************************/

bool ManejarClick(sf::Vector2i posicionMouse, Jugador jugadorActual, Celda** tableroMinis, bool** casillasJugables, Jugador** tableroGrande)
{
	int columna = posicionMouse.x % 540 / TAM_CELDA;
	int fila = posicionMouse.y % 540 / TAM_CELDA;
	std::cout << (tableroMinis[fila][columna].jugador == Jugador::INDETERMINADO);
	std::cout << '\n' << (tableroMinis[fila][columna].forma.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y));
	std::cout << '\n' << (casillasJugables[fila / 3][columna / 3]);
	std::cout << '\n' << (tableroGrande[fila / 3][columna / 3] == Jugador::INDETERMINADO) << "\n---------\n";
	if (tableroMinis[fila][columna].jugador == Jugador::INDETERMINADO && casillasJugables[fila / 3][columna / 3]
		&& tableroMinis[fila][columna].forma.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)
		&& tableroGrande[fila / 3][columna / 3] == Jugador::INDETERMINADO)
	{
		tableroMinis[fila][columna].jugador = jugadorActual;
		//Verificar si se llenó
		Tablero_I_Lleno(fila, columna, tableroMinis, tableroGrande, casillasJugables);
		//Verificar si se ganó
		Tablero_I_Ganado(fila, columna, tableroMinis, tableroGrande, casillasJugables, jugadorActual);
		if (tableroGrande[fila % 3][columna % 3] != Jugador::INDETERMINADO) TodasLibres(casillasJugables);
		else CasillaJugable(casillasJugables, fila % 3, columna % 3);
		return true;
	}
	return false;
}