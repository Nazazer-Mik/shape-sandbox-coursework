#include "Star.h"

Star::Star(sf::Vector2f pos, float size, sf::Color _fill_col, sf::Color _selected_col)
{
	_star.setPointCount(10);
	int points[] =
	{
		230, 0, 280, 170, 450, 180,
		320, 280, 370, 450, 230, 350,
		90, 450, 135, 280, 0, 180,
		170, 170
	};

	for (int i = 0, j = 0; i < 10; i++, j += 2)
		_star.setPoint(i, sf::Vector2f(points[j] / 4, points[j + 1] / 4));

	_star.setPosition(pos);
	_star.setScale(sf::Vector2f(size, size));
	_star.setFillColor(_fill_col);
	setOutlineColor(BLACK);
	setOutlineThickness(4);
	this->_selected_col = _selected_col;
	this->_fill_col = _fill_col;
	_default_col = _fill_col;
	_default_scale = sf::Vector2f(1.f, 1.f);
	_track.setPrimitiveType(sf::LineStrip);
	_id_obj = _id;
	_id++;
}

Star::Star() : Star(sf::Vector2f(MARGIN, MARGIN), 1.f) {}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = _star.getTransform();
	target.draw(_star);
	target.draw(_track);
}

void Star::setPosition(sf::Vector2f pos)
{
	_star.setPosition(pos);
}

void Star::setSize(sf::Vector2f s)
{
	_star.setScale(s);
}

void Star::setFillColor(sf::Color c)
{
	_fill_col = c;
	_star.setFillColor(c);
}

void Star::setOutlineThickness(float t)
{
	_star.setOutlineThickness(t);
}

void Star::setOutlineColor(sf::Color c)
{
	_star.setOutlineColor(c);
}

sf::FloatRect Star::getGlobalBounds()
{
	return _star.getGlobalBounds();
}

float Star::getOutlineThickness()
{
	return _star.getOutlineThickness();
}

sf::Vector2f Star::getPosition()
{
	return _star.getPosition();
}

sf::Vector2f Star::getSize()
{
	return sf::Vector2f(_star.getLocalBounds().width, _star.getLocalBounds().height);
}

sf::Vector2f Star::getScale()
{
	return _star.getScale();
}

bool Star::containPoint(Cords c)
{
	return getGlobalBounds().contains(c.x, c.y);
}

bool Star::collides(Figure* f)
{
	return f->getId() != _id_obj && getGlobalBounds().intersects(f->getGlobalBounds());
}

int Star::getId()
{
	return _id_obj;
}

void Star::swtchHide()
{
	_star.setFillColor((_star.getFillColor() == sf::Color::Transparent) ? _fill_col : sf::Color::Transparent);
}

void Star::defaultState()
{
	setFillColor(_default_col);
	setSize(_default_scale);
}

Figure* Star::clone()
{
	return new Star(*this);
}

std::string Star::toString()
{
	std::string output = "Star\n";
	output += std::to_string(_fill_col.toInteger()) + "\n";
	output += std::to_string(getScale().x) + "\n";
	output += std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + "\n";
	return output;
}