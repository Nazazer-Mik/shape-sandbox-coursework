#pragma once
#include "Memento.h"
#include "Figure_handler.h"

class Caretaker
{
	Memento _memento;
public:
	void saveScene(const Figure_handler& f);
	void loadScene(Figure_handler& f);
};

