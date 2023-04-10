#pragma once
#include <SFML/Graphics.hpp>
#include "GUI_Element.h"
#include <iostream>

namespace ngui
{
	class Button : public GUIable, sf::Transformable
	{
		const bool CLICKABLE = true;
		sf::RectangleShape _rec;
		sf::Color _col_not_click, _col_click;
		sf::Font _font;
		sf::Text _text;
		bool _clicked = false;
		bool _movable = false;
	public:
		Button();
		Button(sf::Vector2f size, sf::Vector2f pos,
			   sf::Color main_color, sf::Color pressed_color,
			   std::string _text, std::string font_location = "fonts/Roboto-Medium.ttf", int text_size = 24);
		Button(sf::Vector2f pos,
			sf::Color main_color, sf::Color pressed_color,
			std::string _text, std::string font_location = "fonts/Roboto-Medium.ttf", int text_size = 24);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		inline bool isTriggered(Cords c) { return _rec.getGlobalBounds().contains(c.x, c.y); }
		void processClick(Cords c) override;
		void processDeclick(Cords c) override;
		void update(sf::RenderWindow& w) override;
		std::function<void(void)> callback;
		std::function<void(ngui::Button*)> update_callback = nullptr;
		bool isClickable() override;
		void setPosition(Cords c);
	};
}