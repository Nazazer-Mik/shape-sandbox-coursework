#include "Snowflake.h"
#include "constants.h"
#include <cmath>

sf::ConvexShape Snowflake::_convex;

void Snowflake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_convex, states);
}

void Snowflake::updatePos(const int height, const int width)
{
	if (_x == -1000 || _y > height + 50)
	{
		_x = rand() % width;
		_y = -40*(rand()%20);
	}

	_x += _coef_sin*sin(_x_sin);
	_y += sin(_y_sin) + _speed*_coef_speed;
	setPosition(sf::Vector2f(_x, _y));
	_x_sin += _sign_sin_incr;
	_y_sin += _sign_cos_incr;

	if (_x_sin <= 0 || _x_sin >= 6.28)
		_sign_sin_incr *= -1;
	if (_y_sin >= 3.4 || _y_sin <= 0)
		_sign_cos_incr *= -1;
}

Snowflake::Snowflake() 
{
	int arr[] = {
		30, 30, 50, 20, 60, 20, 60, 40, 50, 40,
		30, 30, 40, 50, 40, 60, 20, 60, 20, 50,
		30, 30, 10, 40, 0, 40, 0, 20, 10, 20,
		30, 30, 20, 10, 20, 0, 40, 0, 40, 10, 30, 30
	};

	_convex.setPointCount(20);
	for (int i = 0, j = 0; i < 20; i++, j += 2)
			_convex.setPoint(i, sf::Vector2f(arr[j]/6, arr[j+1]/6));

	_convex.setFillColor(BLUE);
	_x = -1000;
	_y = 0;
	_coef_sin = abs((rand() % 100) / 100.f);
	_coef_speed = abs((rand() % 10) / 10.f);
	_speed = 0.7 + abs(rand() % 5)/10.f;
	_x_sin = _y_sin = abs((rand() % 628) / 100.f);
	_sign_sin_incr = abs(rand() % 4) / 100.f + 0.01f;
	_sign_cos_incr = abs(rand() % 4) / 100.f + 0.01f;
}