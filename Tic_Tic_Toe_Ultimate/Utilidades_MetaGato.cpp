#include "Utilidades_MetaGato.h"
#include <sstream>
#include <iomanip>
void Tablero_I_Lleno(int fila, int columna, Celda** tablero, Jugador** tableroGrande, bool** casillasJugables)
{
	int cont = 0;
    int filaInterna = 0, colInterna = 0;
    filaInterna = 3 * (fila / 3);
    colInterna = 3 * (columna / 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j <  3; j++)
		{
			if (tablero[filaInterna+i][colInterna+j].jugador != Jugador::INDETERMINADO) cont++;
		}
	}
	if (cont == 9) tableroGrande[fila / 3][columna / 3] = Jugador::NADIE;
}
/********************************************************************************/
void Tablero_I_Ganado(int fila, int columna, Celda** tableroPrincipal, Jugador** tableroGanados,bool** casillasJugables, Jugador quienJugo)
{
    int jugVer = 0, jugHor = 0, jugDiagIzq = 0, jugDiagDer = 0;
    int filaInterna = 0, colInterna = 0;
    filaInterna = 3 * (fila / 3);
    colInterna = 3 * (columna / 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //Lineas horizontales
            if (tableroPrincipal[filaInterna + i][colInterna + j].jugador == quienJugo)jugHor++;
            //Lineas verticales
            if (tableroPrincipal[filaInterna + j][colInterna + i].jugador == quienJugo)jugVer++;
        }
        //Diagonal izquierda
        if (tableroPrincipal[filaInterna + i][colInterna + i].jugador == quienJugo) jugDiagIzq++;
        //Diagonal derecha
        if (tableroPrincipal[filaInterna + 2 - i][colInterna + i].jugador == quienJugo) jugDiagDer++;
        //Verificar si gan� el jugador de las X
        if (jugVer == 3 || jugHor == 3) {
            tableroGanados[fila / 3][columna / 3] = quienJugo;
            return;
        }
        jugVer = 0;
        jugHor = 0;
    }
    if (jugDiagIzq == 3 || jugDiagDer == 3) {
        tableroGanados[fila / 3][columna / 3] = quienJugo;
        return;
    }
}

void LiberarMemoria(Celda** tableroMinis, Jugador** tableroGrande, bool** casillasDisponibles)
{
    for (int i = 0; i < 9; i++)
    {
        delete[] tableroMinis[i];
    }
    for (int i = 0; i < 3; i++)
    {
        delete[] tableroGrande[i];
        delete[] casillasDisponibles[i];
    }

    delete[] tableroMinis;
    delete[] casillasDisponibles;
    delete[] tableroGrande;

    tableroMinis = nullptr;
    casillasDisponibles = nullptr;
    tableroGrande = nullptr;
}

void dibujarReloj(sf::RenderWindow& ventana, sf::Clock& reloj)
{
    // Obtener el tiempo transcurrido desde el inicio del reloj
    sf::Time tiempoTranscurrido = reloj.getElapsedTime();

    // Obtener la duracion total en segundos
    int segundos = tiempoTranscurrido.asSeconds();

    // Calcular horas, minutos y segundos
    int horas = segundos / 3600;
    int minutos = (segundos % 3600) / 60;
    segundos = segundos % 60;

    // Crear una cadena de texto para mostrar el tiempo en formato HH:MM:SS
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << horas << ":"
        << std::setfill('0') << std::setw(2) << minutos << ":"
        << std::setfill('0') << std::setw(2) << segundos;

    // Dibujar el texto del reloj debajo del tablero
    sf::Font fuente;
    if (!fuente.loadFromFile("Minecraft.ttf"))
    {
        return;
    }

    sf::Text textoReloj;
    textoReloj.setFont(fuente);
    textoReloj.setCharacterSize(30);
    textoReloj.setString(ss.str());
    textoReloj.setFillColor(sf::Color::White);
    textoReloj.setPosition(55, ventana.getSize().y - 60);

    sf::Text texto;
    sf::Text texto2;
    texto.setFont(fuente);
    texto2.setFont(fuente);
    texto.setCharacterSize(30);
    texto2.setCharacterSize(30);
    texto.setString("Tiempo de Juego");
    texto.setFillColor(sf::Color::White);
    texto.setPosition(50, ventana.getSize().y - 110);


    texto2.setString("Haga click en la casilla que desea jugar...");
    texto2.setFillColor(sf::Color(255, 255, 255, 120));
    texto2.setPosition(620, 350);

    ventana.draw(texto);
    ventana.draw(texto2);
    ventana.draw(textoReloj);
}