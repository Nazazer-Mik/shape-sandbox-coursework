#pragma once
#include "Figure.h"

class Circle : public Figure
{
	sf::CircleShape _crl;
public:
	Circle();
	Circle(sf::Vector2f pos, float rad, sf::Color _fill_col = PINK, sf::Color _selected_col = MINT);
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
};

