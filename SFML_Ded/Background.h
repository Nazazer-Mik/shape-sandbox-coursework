#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Snowflake.h"

class Background : public sf::Drawable
{
	int _height, _width;
	sf::RectangleShape _bg_rec;
	bool _enable_dynamic;		// Dynamic background handle
	unsigned int _star_count;
	Snowflake* _snowflake;
public:
	Background(int height, int width, sf::Color bg_color);
	~Background();
	bool dynamicBackground() const;
	void switchDynamicBackground();
	void increaseSnowflakes();
	void decreaseSnowflakes();
	unsigned int getSnowlakesCount();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

