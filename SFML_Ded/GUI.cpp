#include "GUI.h"

namespace ngui
{
	GUI* GUI::getInstance()
	{
		static GUI gui;
		return &gui;
	}

	void GUI::addToHandler(GUIable& elem)
	{
		_elements.push_back(&elem);
	}

	void GUI::processClick(Cords c)
	{
		for (auto i : _elements)
			if (i->isClickable())
				i->processClick(c);
	}

	void GUI::processDeclick(Cords c)
	{
		for (auto i : _elements)
			if (i->isClickable())
				i->processDeclick(c);
	}

	void GUI::update(sf::RenderWindow& w)
	{
		for (auto i : _elements)
			i->update(w);
	}

	void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto i : _elements)
			target.draw(*i);
	}
}