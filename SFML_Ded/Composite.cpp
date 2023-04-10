#include "Composite.h"
#include <iostream>
#include <cmath>
#include "Figure_handler.h"

Composite::Composite(std::list<Figure*>* arr)
{
	Boundaries boundaries;
	_selected_col = BLUE;
	_fill_col = PINK;

	_figures = *arr;

	getGlobalBoundaries(boundaries);

	for (auto i : _figures)
	{
		i->_default_col = i->_fill_col;
		i->_default_scale = i->getScale();
		i->_selected = false;
		setOutlineColor(BLACK);
	}

	_rec.setPosition(sf::Vector2f(boundaries.min_x, boundaries.min_y));
	_rec.setSize(sf::Vector2f(boundaries.max_x - boundaries.min_x, boundaries.max_y - boundaries.min_y));
	_track.setPrimitiveType(sf::LineStrip);
	_id_obj = _id;
	_id++;
}

Composite::~Composite()
{
	for (auto& e : _figures)
		delete e;
}

void Composite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto i : _figures)
		target.draw(*i);
	target.draw(_track);
}

void Composite::setPosition(sf::Vector2f pos)
{
	sf::Vector2f offset(getPosition() - pos);
	_rec.setPosition(pos);

	for (auto i : _figures)
		i->setPosition(i->getPosition() - offset);
}

void Composite::setSize(sf::Vector2f s)
{
	Boundaries boundaries;
	
	for (auto i : _figures)
		i->setSize(s);

	getGlobalBoundaries(boundaries);

	_rec.setSize(sf::Vector2f(boundaries.max_x - boundaries.min_x, boundaries.max_y - boundaries.min_y));
}

void Composite::setFillColor(sf::Color c)
{
	_rec.setFillColor(c);
	for (auto i : _figures)
		i->setFillColor(c);
}

void Composite::setOutlineThickness(float t)
{
	_rec.setOutlineThickness(t);
	for (auto i : _figures)
		i->setOutlineThickness(t);
}

void Composite::setOutlineColor(sf::Color c)
{
	for (auto i : _figures)
		i->setOutlineColor(c);
}

sf::FloatRect Composite::getGlobalBounds()
{
	return _rec.getGlobalBounds();
}

float Composite::getOutlineThickness()
{
	return _rec.getOutlineThickness();
}

sf::Vector2f Composite::getPosition()
{
	return _rec.getPosition();
}

sf::Vector2f Composite::getSize()
{
	return _rec.getSize();
}

sf::Vector2f Composite::getScale()
{
	return _rec.getScale();
}

bool Composite::containPoint(Cords c)
{
	bool res = false;
	for (auto i : _figures)
	{
		if (i->getGlobalBounds().contains(c.x, c.y))
		{
			res = true;
			break;
		}
	}
	return res;
}

bool Composite::collides(Figure* f)
{
	bool res = false;
	for (auto i : _figures)
	{
		if (i->getId() != _id_obj && i->getGlobalBounds().intersects(f->getGlobalBounds()))
		{
			res = true;
			break;
		}
	}
	return res;
}

int Composite::getId()
{
	return _id_obj;
}

void Composite::swtchHide()
{
	setFillColor((_rec.getFillColor() == sf::Color::Transparent) ? _fill_col : sf::Color::Transparent);
}

void Composite::defaultState()
{
	for (auto i : _figures)
		i->defaultState();
}

Figure* Composite::clone()
{
	std::list<Figure*>* arr = new std::list<Figure*>();
	for (auto& i : _figures)
		arr->push_back(i->clone());

	return new Composite(arr);
}

std::string Composite::toString()
{
	std::string output = "Composite\n";
	output += std::to_string(_fill_col.toInteger()) + "\n";
	output += std::to_string(getScale().x) + "\n";
	output += std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + "\n";
	for (auto& i : _figures)
		output += i->toString();
	output += "/Composite\n";
	return output;
}

void Composite::getGlobalBoundaries(Boundaries& boundaries)
{
	for (auto i : _figures)
	{
		if (i->getPosition().x < boundaries.min_x)
			boundaries.min_x = i->getPosition().x;
		if (i->getPosition().y < boundaries.min_y)
			boundaries.min_y = i->getPosition().y;
		if (i->getPosition().x + i->getSize().x * i->getScale().x > boundaries.max_x)
			boundaries.max_x = i->getPosition().x + i->getSize().x;
		if (i->getPosition().y + i->getSize().y * i->getScale().y > boundaries.max_y)
			boundaries.max_y = i->getPosition().y + i->getSize().y;
	}
}