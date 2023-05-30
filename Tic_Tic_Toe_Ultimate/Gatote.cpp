#include "Gatote.h"

Gatote::Gatote()
{
	tablerote = new Gato * [3];
	for (int i = 0; i < 3; i++)
	{
		tablerote[i] = new Gato[3];
	}
}
Gatote::~Gatote()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] tablerote[i];
	}

	delete[] tablerote;

	tablerote = NULL;
}