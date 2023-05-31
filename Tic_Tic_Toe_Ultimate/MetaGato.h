#ifndef METAGATO_H
#define METAGATO_H

#include "Utilidades_MetaGato.h"
#include <iostream>
#define  TAM_VENTANA  540
#define TAM_CELDA  60
#define TAM_TAB_PEQ  56

Jugador HaGanado(Jugador** tableroGanados);
void InicializarTablero(Celda**& tableroMinis, bool**& casillaJugable, Jugador**& tableroGrande);
bool ManejarClick(sf::Vector2i posicionMouse, Jugador jugadorActual, Celda** tableroMinis, bool** casillasJugables, Jugador** tableroGrande);
void dibujarTablero(sf::RenderWindow& ventana, Celda** tableroMinis);
void TodasLibres(bool** casillasDisponibles);
void CasillaJugable(bool** casillasDisponibles, int fila, int columna);
#endif //METAGATO_H