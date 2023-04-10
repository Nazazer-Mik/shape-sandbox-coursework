#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>

namespace ngui
{
	class GUIable : public sf::Drawable
	{
	public:
		virtual bool isClickable() = 0;
		virtual void processClick(Cords c) {};
		virtual void processDeclick(Cords c) {};
		virtual void update(sf::RenderWindow& w) {};
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}