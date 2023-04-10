#include "Slider.h"

void buttonBgSetting(sf::RectangleShape& rec, sf::Vector2f& pos, sf::Vector2f size, sf::Color main_color)
{
	rec.setSize(size);
	rec.setPosition(pos);
	rec.setFillColor(main_color);
	rec.setOutlineThickness(OUTLINE_THICKNESS);
	rec.setOutlineColor(main_color);
}

namespace ngui
{
	Slider::Slider(sf::Vector2f size, sf::Vector2f pos, sf::Color main_color, sf::Color pressed_color, Cords boundaries, float default_val)
	{
		_min_value = boundaries.x;
		_max_value = boundaries.y;
		_cur_value = default_val;

		_line.setSize(sf::Vector2f(size.x, 5.f));
		_line.setPosition(sf::Vector2f(pos.x, pos.y + (size.y - _line.getSize().y)/2));
		_line.setFillColor(BLACK);

		sf::Vector2f button_position = sf::Vector2f(pos.x + (size.x * ((default_val - _min_value) / (_max_value - _min_value))), pos.y);
		sf::Vector2f button_size = sf::Vector2f(15.f, size.y);
		buttonBgSetting(_rec, button_position, button_size, main_color);
		
		_col_not_click = main_color;
		_col_click = pressed_color;
		callback = nullptr;
	}

	Slider::Slider() : Slider(sf::Vector2f(200.f, 50.f), sf::Vector2f()) {}
	
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_line, states);
		target.draw(_rec, states);
	}

	void Slider::processClick(Cords c)
	{
		if (isTriggered(c))
		{
			_clicked = true;
			_rec.setFillColor(_col_click);
			_drag_offset_x = _rec.getPosition().x - c.x;
		}
	}

	void Slider::processDeclick(Cords c)
	{
		if (_clicked)
		{
			_clicked = false;
			_rec.setFillColor(_col_not_click);
		}
	}

	void Slider::update(sf::RenderWindow& w)
	{
		if (!_clicked)
			return;
		float offset = 0;
		if (sf::Mouse::getPosition(w).x > _line.getPosition().x && sf::Mouse::getPosition(w).x < _line.getPosition().x + _line.getSize().x)
			offset = sf::Mouse::getPosition(w).x - _line.getPosition().x;
		else if (sf::Mouse::getPosition(w).x > _line.getPosition().x)
			offset = _line.getSize().x;

		offset += _line.getPosition().x;
		_rec.setPosition(offset + _drag_offset_x, _rec.getPosition().y);
		if (callback != nullptr)
			callback((_rec.getPosition().x - _line.getPosition().x) / (_line.getSize().x) * (_max_value - _min_value) + _min_value);
	}
	
	bool Slider::isClickable()
	{
		return CLICKABLE;
	}
}