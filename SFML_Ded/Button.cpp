#include "Button.h"

void textSetting(sf::Vector2f& pos, sf::Vector2f& size, sf::Text& text, sf::Font& font, std::string inner_text, int text_size)
{
	text.setFont(font);
	text.setString(inner_text);
	text.setCharacterSize(text_size);
	text.setFillColor(BLACK);
	float text_x = pos.x + (size.x - text.getLocalBounds().width) / 2;
	float text_y = pos.y + (size.y - text.getLocalBounds().height) / 2 - MARGIN / 4;
	text.setPosition(sf::Vector2f(text_x, text_y));
}

void buttonBgSetting(sf::RectangleShape& rec, sf::Vector2f& pos, sf::Vector2f& size, sf::Color& main_color)
{
	rec.setSize(size);
	rec.setPosition(pos);
	rec.setFillColor(main_color);
	rec.setOutlineThickness(OUTLINE_THICKNESS);
	rec.setOutlineColor(main_color);
}

namespace ngui
{
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_rec, states);
		target.draw(_text, states);
	}
	
	Button::Button(sf::Vector2f size, sf::Vector2f pos, 
				   sf::Color main_color, sf::Color pressed_color, 
				   std::string _text, std::string font_location, int text_size)
	{
		buttonBgSetting(this->_rec, pos, size, main_color);
		_col_not_click = main_color;
		_col_click = pressed_color;
		if (!_font.loadFromFile(font_location))
			std::cout << "Error! Font was not loaded!!!\n";
		textSetting(pos, size, this->_text, this->_font, _text, text_size);
	}

	Button::Button() : Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(0, 0), MINT, BLUE, std::string("Default")) {}

	Button::Button(sf::Vector2f pos,
		sf::Color main_color, sf::Color pressed_color,
		std::string _text, std::string font_location, int text_size) : 
		Button(sf::Vector2f(0.f, 0.f), pos, main_color, pressed_color, _text, font_location, text_size)
	{
		float size_x = this->_text.getLocalBounds().width + MARGIN*2, size_y = text_size * 2;
		_rec.setSize(sf::Vector2f(size_x, size_y));
		float text_x = pos.x + (size_x - this->_text.getLocalBounds().width) / 2;
		float text_y = pos.y + (size_y - this->_text.getLocalBounds().height) / 2 - MARGIN / 4;
		this->_text.setPosition(sf::Vector2f(text_x, text_y));
	}


	void Button::processClick(Cords c)
	{
		if (isTriggered(c))
		{
			_clicked = true;
			_rec.setFillColor(_col_click);
			callback();
		}
	}

	void Button::processDeclick(Cords c)
	{
		if (_clicked)
		{
			_clicked = false;
			_rec.setFillColor(_col_not_click);
		}
	}

	bool Button::isClickable()
	{
		return CLICKABLE;
	}

	void Button::update(sf::RenderWindow& w)
	{
		if (update_callback != nullptr)
			update_callback(this);
	}

	void Button::setPosition(Cords c)
	{
		_rec.setPosition(sf::Vector2f(c.x, c.y));
		_text.setPosition(sf::Vector2f(c.x + (_rec.getGlobalBounds().width - this->_text.getLocalBounds().width) / 2 - 2.5, c.y + (_rec.getGlobalBounds().height - this->_text.getLocalBounds().height) / 2 - MARGIN / 4 - 4.f));
	}
}