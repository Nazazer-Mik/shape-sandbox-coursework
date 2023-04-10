#pragma once
#include <SFML/Graphics.hpp>
#include "GUI_Element.h"

namespace ngui 
{
	class Sign : public GUIable, sf::Transformable
	{
		const bool CLICKABLE = false;
		sf::Text _text;
		sf::Font _font;
		std::string _static_text;
		int _number; // Number which update with Update_callback function
	public:
		Sign();
		Sign(sf::Vector2f pos, std::string _text, std::string font_location = "fonts/Roboto-Medium.ttf", int text_size = 18, sf::Color c = BLACK);
		bool isClickable() override;
		void update(sf::RenderWindow& w) override;
		std::function<unsigned int(void)> update_callback = nullptr;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		Cords getDimensions();
	};
}

