#pragma once
#include <SFML/Graphics.hpp>
#include "Sign.h"
#include "Button.h"
#include "Slider.h"
#include <list>

namespace ngui
{
	class GUI : public sf::Drawable
	{
		GUI() {};
		std::list<GUIable*> _elements;
	public:
		static GUI* getInstance();
		void addToHandler(GUIable& elem);
		void processClick(Cords c);
		void processDeclick(Cords c);
		void update(sf::RenderWindow& w);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}