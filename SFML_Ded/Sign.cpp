#include "Sign.h"

namespace ngui
{
	bool Sign::isClickable()
	{
		return CLICKABLE;
	}

	void Sign::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_text, states);
	}

	Sign::Sign(sf::Vector2f pos, std::string _text, std::string font_location, int text_size, sf::Color c)
	{
		_font.loadFromFile(font_location);
		_static_text = _text;
		this->_text.setFont(_font);
		this->_text.setString(_text);
		this->_text.setCharacterSize(text_size);
		this->_text.setFillColor(c);
		this->_text.setPosition(pos);
	}

	Sign::Sign() : Sign(sf::Vector2f(0, 0), "Default") {}

	void Sign::update(sf::RenderWindow& w)
	{
		if (update_callback == nullptr)
			return;
		_number = update_callback();
		_text.setString(_static_text + " " + std::to_string(_number));
	}

	Cords Sign::getDimensions()
	{
		return {_text.getLocalBounds().width, _text.getLocalBounds().height};
	}
}