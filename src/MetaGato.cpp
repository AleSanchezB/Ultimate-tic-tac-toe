#include "MetaGato.h"
bool HaGanado(Jugador** tableroGanados, Jugador quienJugo) {
	int jugVer = 0, jugHor = 0, jugDiagIzq = 0, jugDiagDer = 0;
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
		if (tableroGanados[i][2 - i] == quienJugo) jugDiagDer++;
		//Verifica ganador, si lo hay
		if (jugVer == 3 || jugHor == 3) {
			return true;
		}
		jugVer = 0;
		jugHor = 0;
	}
	//Verifica ganador, si lo hay. Se hace afuera porque las diagonales se verifican hasta el final del ciclo externo
	if (jugDiagIzq == 3 || jugDiagDer == 3) {
		return true;
	}
	return false;
}
/****************************************************************************************************/

void InicializarTablero(Celda**& tableroMinis, bool**& casillaJugable, Jugador**& tableroGrande)
{
	tableroMinis = new Celda * [9];
	casillaJugable = new bool* [3];
	tableroGrande = new Jugador * [3];
	//Asigna memoria dinamica al tablero de casillas jugables y al de ganadores del MetaGato
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
		//Asignacion de memoria al tablero global
		tableroMinis[i] = new Celda[9];
		for (int j = 0; j < 9; ++j)
		{
			//Inicializacion de la imagen del tablero global
			sf::RectangleShape& forma = tableroMinis[i][j].forma;
			forma.setSize(sf::Vector2f(TAM_TAB_PEQ, TAM_TAB_PEQ));
			forma.setPosition((float)(j * TAM_CELDA + 10), (float)(i * TAM_CELDA + 5));
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
	sf::RectangleShape cuadrado;
	cuadrado.setSize(sf::Vector2f(TAM_CELDA * 3 - 5, TAM_CELDA * 3 - 5));
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			//Dibuja las celdas correspondientes dependiendo de lo que haya en el tablero global
			const Celda& celda = tableroMinis[i][j];
			ventana.draw(celda.forma);

			sf::Texture textura;
			sf::Sprite simbolo;
			//Dibuja el simbolo correspondiente al jugador que acaba de tomar su turno en el tablero global
			if (celda.jugador == Jugador::X)
			{
				textura.loadFromFile("Assets/X.png");
				simbolo = sf::Sprite(textura);
				simbolo.setScale(50.f / simbolo.getTexture()->getSize().x, 50.f / simbolo.getTexture()->getSize().y);
			}
			else if (celda.jugador == Jugador::O)
			{
				textura.loadFromFile("Assets/O.png");
				simbolo = sf::Sprite(textura);
				simbolo.setScale(50.f / simbolo.getTexture()->getSize().x, 50.f / simbolo.getTexture()->getSize().y);
			}
			else
				continue;

			sf::FloatRect limitesSimbolo = simbolo.getLocalBounds();
			simbolo.setOrigin(limitesSimbolo.left + limitesSimbolo.width / 2, limitesSimbolo.top + limitesSimbolo.height / 2);
			simbolo.setPosition(celda.forma.getPosition().x + TAM_TAB_PEQ / 2, celda.forma.getPosition().y + TAM_TAB_PEQ / 2);

			ventana.draw(simbolo);
		}
	}

	sf::RectangleShape simbNadie;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sf::Texture textura;
			sf::Sprite simbolo;

			cuadrado.setPosition((float)(TAM_CELDA * j * 3 + 10), (float)(TAM_CELDA * i * 3 + 5));
			if (!casillasDisponibles[i][j] || tableroGrande[i][j] != Jugador::INDETERMINADO)
			{
				cuadrado.setOutlineThickness(0.0f);
				cuadrado.setFillColor(sf::Color(0, 0, 0, 170));
			}
			else 
			{
				cuadrado.setFillColor(sf::Color(255, 255, 255, 15));
				cuadrado.setOutlineThickness(5.0f);
				cuadrado.setOutlineColor(sf::Color(255,211,0));
			}

			ventana.draw(cuadrado);
			//Dibuja los simbolos correspondientes a cada estado de los tableros locales (Ganado por X, por O o empatado)
			if (tableroGrande[i][j] == Jugador::X)
			{
				textura.loadFromFile("Assets/X.png");
				simbolo = sf::Sprite(textura);
				simbolo.setPosition((float)(TAM_CELDA * j * 3 + 10), (float)(TAM_CELDA * i * 3 + 5));
				simbolo.setScale(180.f / simbolo.getTexture()->getSize().x, 180.f / simbolo.getTexture()->getSize().y);
				ventana.draw(simbolo);
			}
			else if (tableroGrande[i][j] == Jugador::O)
			{
				textura.loadFromFile("Assets/O.png");
				simbolo = sf::Sprite(textura);
				simbolo.setPosition((float)(TAM_CELDA * j * 3 + 10), (float)(TAM_CELDA * i * 3 + 5));
				simbolo.setScale(180.f / simbolo.getTexture()->getSize().x, 180.f / simbolo.getTexture()->getSize().y);
				ventana.draw(simbolo);
			}
			else if (tableroGrande[i][j] == Jugador::NADIE)
			{
				textura.loadFromFile("Assets/Menus/Empate.png");
				simbolo = sf::Sprite(textura);
				simbolo.setPosition((float)(TAM_CELDA * j * 3 + 10), (float)(TAM_CELDA * i * 3 + 5));
				simbolo.setScale(180.f / simbolo.getTexture()->getSize().x, 180.f / simbolo.getTexture()->getSize().y);
				ventana.draw(simbolo);
			}
		}
	}
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

void GestionJugada(sf::Vector2i posicionMouse, Jugador jugadorActual, Celda** tableroMinis, bool** casillasJugables, Jugador** tableroGrande)
{
	int columna = posicionMouse.x % 540 / TAM_CELDA;
	int fila = posicionMouse.y % 540 / TAM_CELDA;
	tableroMinis[fila][columna].jugador = jugadorActual;

	//Verificar si se lleno
	Tablero_I_Lleno(fila, columna, tableroMinis, tableroGrande, casillasJugables);

	//Verificar si se gano
	Tablero_I_Ganado(fila, columna, tableroMinis, tableroGrande, casillasJugables, jugadorActual);

	if (tableroGrande[fila % 3][columna % 3] != Jugador::INDETERMINADO) TodasLibres(casillasJugables);
	else CasillaJugable(casillasJugables, fila % 3, columna % 3);
}
/****************************************************************************************************/
bool ValidarClick(sf::Vector2i posicionMouse, Celda** tableroMinis, bool** casillasJugables, Jugador** tableroGrande) {
	int columna = posicionMouse.x % 540 / TAM_CELDA;
	int fila = posicionMouse.y % 540 / TAM_CELDA;
	if (columna < 9 && fila < 9  && tableroMinis[fila][columna].jugador == Jugador::INDETERMINADO && casillasJugables[fila / 3][columna / 3]
		&& tableroMinis[fila][columna].forma.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y)
		&& tableroGrande[fila / 3][columna / 3] == Jugador::INDETERMINADO)
		return true;
	return false;
}
/****************************************************************************************************/
bool EstaLleno(Jugador** tableroGrande) {
	int contador = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tableroGrande[i][j] != Jugador::INDETERMINADO) contador++;
		}
	}
	if (contador == 9) return true;
	return false;
}
