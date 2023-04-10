#include "Triangle.h"

Triangle::Triangle(sf::Vector2f pos, float rad, sf::Color _fill_col, sf::Color _selected_col)
{
	_trg.setPointCount(3);
	_trg.setPosition(pos);
	_trg.setRadius(rad);
	_trg.setFillColor(_fill_col);
	setOutlineThickness(4);
	setOutlineColor(BLACK);
	this->_selected_col = _selected_col;
	this->_fill_col = _fill_col;
	_default_col = _fill_col;
	_default_scale = sf::Vector2f(1.f, 1.f);
	_track.setPrimitiveType(sf::LineStrip);
	_id_obj = _id;
	_id++;
}

Triangle::Triangle() : Triangle(sf::Vector2f(MARGIN, MARGIN), 30.f) {}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = _trg.getTransform();
	target.draw(_trg);
	target.draw(_track);
}

void Triangle::setPosition(sf::Vector2f pos)
{
	_trg.setPosition(pos);
}

void Triangle::setSize(sf::Vector2f s)
{
	_trg.setScale(s);
}

void Triangle::setFillColor(sf::Color c)
{
	_fill_col = c;
	_trg.setFillColor(c);
}

void Triangle::setOutlineThickness(float t)
{
	_trg.setOutlineThickness(t);
}

void Triangle::setOutlineColor(sf::Color c)
{
	_trg.setOutlineColor(c);
}

sf::FloatRect Triangle::getGlobalBounds()
{
	return _trg.getGlobalBounds();
}

float Triangle::getOutlineThickness()
{
	return _trg.getOutlineThickness();
}

sf::Vector2f Triangle::getPosition()
{
	return _trg.getPosition();
}

sf::Vector2f Triangle::getSize()
{
	return sf::Vector2f(_trg.getRadius() * 2, _trg.getRadius() * 2);
}

sf::Vector2f Triangle::getScale()
{
	return _trg.getScale();
}

bool Triangle::containPoint(Cords c)
{
	return getGlobalBounds().contains(c.x, c.y);
}

bool Triangle::collides(Figure* f)
{
	return f->getId() != _id_obj && getGlobalBounds().intersects(f->getGlobalBounds());
}

int Triangle::getId()
{
	return _id_obj;
}

void Triangle::swtchHide()
{
	_trg.setFillColor((_trg.getFillColor() == sf::Color::Transparent) ? _fill_col : sf::Color::Transparent);
}

void Triangle::defaultState()
{
	setFillColor(_default_col);
	setSize(_default_scale);
}

Figure* Triangle::clone()
{
	return new Triangle(*this);
}

std::string Triangle::toString()
{
	std::string output = "Triangle\n";
	output += std::to_string(_fill_col.toInteger()) + "\n";
	output += std::to_string(getScale().x) + "\n";
	output += std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + "\n";
	return output;
}