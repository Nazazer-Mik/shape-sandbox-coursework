#pragma once
#include "constants.h"

class Figure : public sf::Drawable
{
protected:
	sf::VertexArray _track;
	sf::Color _fill_col, _selected_col, _default_col;
	sf::Vector2f _default_scale;
	bool _drag_drop = false;
	bool _selected = false;
	float _drag_offset_x = 0, _drag_offset_y = 0;
	static int _id;
	int _id_obj;
public:
	virtual void setPosition(sf::Vector2f pos) = 0;
	virtual void setSize(sf::Vector2f s) = 0;
	virtual void setFillColor(sf::Color c) = 0;
	virtual void setOutlineThickness(float t) = 0;
	virtual void setOutlineColor(sf::Color c) = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	virtual float getOutlineThickness() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual sf::Vector2f getSize() = 0;
	virtual sf::Vector2f getScale() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual bool containPoint(Cords c) = 0;
	virtual bool collides(Figure* f) = 0;
	virtual int getId() = 0;
	virtual void swtchHide() = 0;
	virtual void defaultState() = 0;
	virtual Figure* clone() = 0;
	virtual std::string toString() = 0;
	friend class Figure_handler;
	friend class Composite;
};