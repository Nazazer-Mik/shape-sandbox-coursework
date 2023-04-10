#include "Background.h"
#include <iostream>

void resizeArray(Snowflake*& arr, const int STAR_COUNT)
{
	delete [] arr;
	arr = new Snowflake[STAR_COUNT]();
}

Background::Background(int height, int width, sf::Color bg_color)
{
	this->_height = height;
	this->_width = width;

	_bg_rec.setFillColor(bg_color);
	_bg_rec.setSize(sf::Vector2f(width, height));
	_bg_rec.setPosition(0, 0);

	_enable_dynamic = true;
	_star_count = 100; // default snowflakes count

	_snowflake = new Snowflake[_star_count]();
}

Background::~Background()
{
	delete[] _snowflake;
}

bool Background::dynamicBackground() const
{
	return _enable_dynamic;
}

void Background::switchDynamicBackground()
{
	_enable_dynamic = !_enable_dynamic;
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_bg_rec);

	if (!dynamicBackground())
		return;

	for (int i = 0; i < _star_count; i++)
		target.draw(_snowflake[i]);
}

void Background::update()
{
	if (!dynamicBackground())
		return;

	for (int i = 0; i < _star_count; i++)
		_snowflake[i].updatePos(_height, _width);
}

void Background::increaseSnowflakes()
{
	_star_count += 100;

	resizeArray(_snowflake, _star_count);
	
}

void Background::decreaseSnowflakes()
{
	if (_star_count <= 0)
		return;

	_star_count -= 100;
	
	resizeArray(_snowflake, _star_count);
}

unsigned int Background::getSnowlakesCount()
{
	return _star_count;
}