#include "Utilidades_MetaGato.h"

void Tablero_I_Lleno(int fila, int columna, Celda** tablero,Jugador **tableroGrande)
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
void Tablero_I_Ganado(int fila, int columna, Celda** tableroPrincipal, Jugador** tableroGanados) {
	int jugX_Ver = 0, jugX_Hor=0,jugX_Diag=0,jugO_Ver = 0,jugO_Hor=0,jugO_Diag=0, aux = 0;
	//Checa de forma horizontal
	for (int i = 3 * (fila / 3); i < 3 * (fila / 3) + 3; i++)
	{
		for (int j = 3 * (columna / 3); j < 3 * (columna / 3) + 3; j++)
		{
			//Lineas horizontales
			if (tableroPrincipal[i][j].jugador == Jugador::X)jugX_Hor++;
			if (tableroPrincipal[i][j].jugador == Jugador::O)jugO_Hor++;
			//Lineas verticales
			if (tableroPrincipal[j][i].jugador == Jugador::X)jugX_Ver++;
			if (tableroPrincipal[j][i].jugador == Jugador::O)jugO_Ver++;
		}
		//Lineas diagonales
		if (tableroPrincipal[i][columna + aux].jugador == Jugador::X) jugX_Diag++;
		if (tableroPrincipal[i][columna + aux].jugador == Jugador::O) jugO_Diag++;
		//Verificar si ganó el jugador de las X
		if (jugX_Ver == 3 || jugX_Hor == 3 || jugX_Diag == 3) {
			std::cout << "Gano jugador 2\n";
			tableroGanados[fila / 3][columna / 3] = Jugador::X;
			return;
		}
		//Verificar si ganó el jugador de las O
		if (jugO_Ver == 3||jugO_Hor==3||jugO_Diag==3) {
			std::cout << "Gano jugador 2\n";
			tableroGanados[fila / 3][columna / 3]= Jugador::O;
			return;
		}
		jugX_Ver = 0;
		jugX_Hor = 0;
		jugO_Hor = 0;
		jugO_Ver = 0;
		aux++;
	}
}