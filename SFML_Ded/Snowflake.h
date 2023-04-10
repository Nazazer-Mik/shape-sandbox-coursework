#pragma once
#include <SFML/Graphics.hpp>

class Snowflake : public sf::Drawable, public sf::Transformable
{
	float _x, _y;
	float _coef_sin, _coef_speed, _speed, _x_sin, _y_sin;
	float _sign_sin_incr, _sign_cos_incr;
	static sf::ConvexShape _convex;
public:
	Snowflake();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updatePos(const int height, const int width);
};

