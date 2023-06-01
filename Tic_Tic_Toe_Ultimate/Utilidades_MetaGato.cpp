#include "Utilidades_MetaGato.h"

void Tablero_I_Lleno(int fila, int columna, Celda** tablero, Jugador** tableroGrande, bool** casillasJugables)
{
	int cont = 0;
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++)
	{
		for (int j = 3 * (columna / 3); j < 3 * (columna / 3) + 3; j++)
		{
			if (tablero[i][j].jugador != Jugador::INDETERMINADO) cont++;
		}
	}
	if (cont == 9) {
		std::cout << "Se lleno\n";
		tableroGrande[fila / 3][columna / 3] = Jugador::NADIE;
	}
}
/********************************************************************************/
void Tablero_I_Ganado(int fila, int columna, Celda** tableroPrincipal, Jugador** tableroGanados,bool** casillasJugables, Jugador quienJugo)
{
    int jugVer = 0, jugHor = 0, jugDiagIzq = 0, jugDiagDer = 0;
    int filaInterna = 0, colInterna = 0;
    filaInterna = 3 * (fila / 3);
    colInterna = 3 * (columna / 3);
    //Checa de forma horizontal
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
            std::cout << "Gano jugador ";
            tableroGanados[fila / 3][columna / 3] = quienJugo;
            return;
        }
        jugVer = 0;
        jugHor = 0;
    }
    if (jugDiagIzq == 3 || jugDiagDer == 3) {
        std::cout << "Gano jugador\n";
        tableroGanados[fila / 3][columna / 3] = quienJugo;
        return;
    }
}