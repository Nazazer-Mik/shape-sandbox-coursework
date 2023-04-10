#pragma once
#include <list>
#include "constants.h"
#include "Figure.h"

class Memento
{
	std::list<Figure*> _figures;
	friend class Figure_handler;
	friend class Caretaker;
};

