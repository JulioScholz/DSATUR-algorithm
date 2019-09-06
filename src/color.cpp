#include "color.h"

color::color()
{
	cor = -1;
	ativo = false;
}

color::color(const int c, const int at) {
	this->cor = c;
	this->ativo = at;
}


color::~color()
{
}
