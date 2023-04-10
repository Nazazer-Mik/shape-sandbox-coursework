#pragma once
#include "GUI_Element.h"
#include <iostream>

namespace ngui
{
	class Slider : public GUIable
	{
		const bool CLICKABLE = true;
		sf::RectangleShape _line, _rec;
		sf::Color _col_not_click, _col_click;
		float _min_value, _max_value, _cur_value;
		float _drag_offset_x = 0;
		bool _clicked = false;
	public:
		Slider();
		Slider(sf::Vector2f size, sf::Vector2f pos, sf::Color main_color = MINT, sf::Color pressed_color = BLUE, Cords boundaries = {0.5f, 2.f}, float default_val = 1.f);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		inline bool isTriggered(Cords c) { return _rec.getGlobalBounds().contains(c.x, c.y); }
		void processClick(Cords c) override;
		void processDeclick(Cords c) override;
		void update(sf::RenderWindow& w) override;
		std::function<void(float)> callback;
		bool isClickable() override;
	};
}
