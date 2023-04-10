#include "Rectangle.h"
#include <iostream>

int Rectangle::_id = 0;

Rectangle::Rectangle(sf::Vector2f pos, sf::Vector2f size, sf::Color _fill_col, sf::Color _selected_col)
{
	_rec.setSize(sf::Vector2f(100.f, 50.f));
	setPosition(pos);
	setSize(size);
	setFillColor(_fill_col);
	setOutlineThickness(4);
	setOutlineColor(BLACK);
	_rec.setScale(1.f, 1.f);
	this->_selected_col = _selected_col;
	this->_fill_col = _fill_col;
	_default_col = _fill_col;
	_default_scale = sf::Vector2f(1.f, 1.f);
	_track.setPrimitiveType(sf::LineStrip);
	_id_obj = _id;
	_id++;
}

Rectangle::Rectangle() : Rectangle(sf::Vector2f(MARGIN, MARGIN), sf::Vector2f(150.f, 60.f)) {}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = _rec.getTransform();
	target.draw(_rec);
	target.draw(_track);
}

void Rectangle::setPosition(sf::Vector2f pos)
{
	_rec.setPosition(pos);
}

void Rectangle::setSize(sf::Vector2f s)
{
	_rec.setScale(s);
}

void Rectangle::setFillColor(sf::Color c)
{
	_fill_col = c;
	_rec.setFillColor(c);
}

void Rectangle::setOutlineThickness(float t)
{
	_rec.setOutlineThickness(t);
}

void Rectangle::setOutlineColor(sf::Color c)
{
	_rec.setOutlineColor(c);
}

sf::FloatRect Rectangle::getGlobalBounds()
{
	return _rec.getGlobalBounds();
}

float Rectangle::getOutlineThickness()
{
	return _rec.getOutlineThickness();
}

sf::Vector2f Rectangle::getPosition()
{
	return _rec.getPosition();
}

sf::Vector2f Rectangle::getSize()
{
	return _rec.getSize();
}

sf::Vector2f Rectangle::getScale()
{
	return _rec.getScale();
}

bool Rectangle::containPoint(Cords c)
{
	return getGlobalBounds().contains(c.x, c.y);
}

bool Rectangle::collides(Figure* f)
{
	return f->getId() != _id_obj && getGlobalBounds().intersects(f->getGlobalBounds());
}

int Rectangle::getId()
{
	return _id_obj;
}

void Rectangle::swtchHide()
{

	_rec.setFillColor((_rec.getFillColor() == sf::Color::Transparent) ? _fill_col : sf::Color::Transparent);
}

void Rectangle::defaultState()
{
	setFillColor(_default_col);
	setSize(_default_scale);
}

Figure* Rectangle::clone()
{
	return new Rectangle(*this);
}

std::string Rectangle::toString()
{
	std::string output = "Rectangle\n";
	output += std::to_string(_fill_col.toInteger()) + "\n";
	output += std::to_string(getScale().x) + "\n";
	output += std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + "\n";
	return output;
}