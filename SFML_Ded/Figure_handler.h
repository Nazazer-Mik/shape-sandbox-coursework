#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Star.h"
#include "Composite.h"
#include "Caretaker.h"
#include <cmath>
#include <list>

class Figure_handler : public sf::Drawable
{
	Figure_handler() {};
	~Figure_handler();
	std::list<Figure*> _figures;
	Options _op;
public:
	static Figure_handler* getInstance();
	void addToHandler(Figure* f);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::RenderWindow& w);
	void processClick(Cords c);
	void processDeclick(Cords c);
	void swtchMove();
	void chngObjColor();
	void chngScale(float s);
	std::list<Figure*>* formSelectedList();
	int countSelectedElements() const;
	void swtchHide();
	void swtchTrack();
	void defaultState();
	void clone();
	Cords getActiveFigureCords();
	void getMemento(Memento& m) const;
	void setMemento(const Memento& m);
	void checkCollision(std::list<Figure*>& figures, Figure* one);
};

