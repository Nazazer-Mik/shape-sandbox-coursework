#pragma once
#include "Figure.h"
#include <list>

struct Boundaries
{
	float min_x = WIDTH;
	float max_x = 0;
	float min_y = HEIGHT;
	float max_y = 0;
};

class Composite : public Figure
{
	std::list<Figure*> _figures;
	sf::RectangleShape _rec;
public:
	~Composite();
	Composite(std::list<Figure*>* arr);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f pos) override;
	void setSize(sf::Vector2f s) override;
	void setFillColor(sf::Color c) override;
	void setOutlineThickness(float t) override;
	void setOutlineColor(sf::Color c) override;
	sf::FloatRect getGlobalBounds() override;
	float getOutlineThickness() override;
	sf::Vector2f getPosition() override;
	sf::Vector2f getSize() override;
	sf::Vector2f getScale() override;
	bool containPoint(Cords c) override;
	bool collides(Figure* f) override;
	int getId() override;
	void swtchHide() override;
	void defaultState() override;
	Figure* clone() override;
	std::string toString() override;
	void getGlobalBoundaries(Boundaries& boundaries);
};

