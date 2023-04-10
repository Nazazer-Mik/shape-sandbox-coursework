#include "Circle.h"

Circle::Circle(sf::Vector2f pos, float rad, sf::Color _fill_col, sf::Color _selected_col)
{
	_crl.setPosition(pos);
	_crl.setRadius(rad);
	_crl.setFillColor(_fill_col);
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

Circle::Circle() : Circle(sf::Vector2f(MARGIN, MARGIN), 30.f) {}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = _crl.getTransform();
	target.draw(_crl);
	target.draw(_track);
}

void Circle::setPosition(sf::Vector2f pos)
{
	_crl.setPosition(pos);
}

void Circle::setSize(sf::Vector2f s)
{
	_crl.setScale(s);
}

void Circle::setFillColor(sf::Color c)
{
	_fill_col = c;
	_crl.setFillColor(c);
}

void Circle::setOutlineThickness(float t)
{
	_crl.setOutlineThickness(t);
}

void Circle::setOutlineColor(sf::Color c)
{
	_crl.setOutlineColor(c);
}

sf::FloatRect Circle::getGlobalBounds()
{
	return _crl.getGlobalBounds();
}

float Circle::getOutlineThickness()
{
	return _crl.getOutlineThickness();
}

sf::Vector2f Circle::getPosition()
{
	return _crl.getPosition();
}

sf::Vector2f Circle::getSize()
{
	return sf::Vector2f(_crl.getRadius()*2, _crl.getRadius()*2);
}

sf::Vector2f Circle::getScale()
{
	return _crl.getScale();
}

bool Circle::containPoint(Cords c)
{
	return getGlobalBounds().contains(c.x, c.y);
}

bool Circle::collides(Figure* f)
{
	return f->getId() != _id_obj && getGlobalBounds().intersects(f->getGlobalBounds());
}

int Circle::getId()
{
	return _id_obj;
}

void Circle::swtchHide()
{

	_crl.setFillColor((_crl.getFillColor() == sf::Color::Transparent) ? _fill_col : sf::Color::Transparent);
}

void Circle::defaultState()
{
	setFillColor(_default_col);
	setSize(_default_scale);
}

Figure* Circle::clone()
{
	return new Circle(*this);
}

std::string Circle::toString()
{
	std::string output = "Circle\n";
	output += std::to_string(_fill_col.toInteger()) + "\n";
	output += std::to_string(getScale().x) + "\n";
	output += std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + "\n";
	return output;
}