#include "Figure_handler.h"
#include <iostream>

Figure_handler::~Figure_handler()
{
	for (auto& e : _figures)
		delete e;

	_figures.clear();
}

void Figure_handler::checkCollision(std::list<Figure*>& figures, Figure* one)
{
	for (auto j : figures)
	{
		if (one->_id_obj != j->_id_obj && one->collides(j))
		{
			one->_selected = false;
			one->setOutlineColor(BLACK);
			one->setSize((one->getScale().x > 0.5f) ? (one->getScale() - sf::Vector2f(0.1, 0.1)) : sf::Vector2f(0.5f, 0.5f));
			break;
		}
	}
}

Figure_handler* Figure_handler::getInstance()
{
	static Figure_handler instance;
	return &instance;
}

void Figure_handler::addToHandler(Figure* f)
{
	_figures.push_back(f);
}

void Figure_handler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto i : _figures)
		target.draw(*i);
}

void Figure_handler::update(sf::RenderWindow& w)
{
	for (auto i : _figures)
	{
		if (i->getGlobalBounds().left >= WIDTH)
			i->setPosition(sf::Vector2f(- i->getGlobalBounds().width, i->getPosition().y));
		if (i->_drag_drop)
			i->setPosition(sf::Vector2f(abs(sf::Mouse::getPosition(w).x % WIDTH) + i->_drag_offset_x, abs(sf::Mouse::getPosition(w).y % (int)PANEL_Y) + i->_drag_offset_y));
		if (_op.move && i->_selected)
		{
			i->setPosition(sf::Vector2f(i->getPosition().x + 3, i->getPosition().y));
			checkCollision(_figures, i);
		}
		if (_op.chng_col && i->_selected)
			i->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		if (_op.enable__track && i->_selected)
			if (i->_drag_drop || _op.move)
			{
				sf::Vertex v = sf::Vertex(i->getPosition());
				v.color = BLUE;
				i->_track.append(v);
			}
		if (!_op.enable__track)
			i->_track.clear();
	}

	if (_op.chng_col)
		_op.chng_col = false;
}

void Figure_handler::processClick(Cords c)
{
	for (auto i : _figures) {
		if (!i->containPoint(c))
			continue;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			i->_drag_drop = true;
			i->setOutlineColor(i->_selected_col);
			i->_drag_offset_x = i->getPosition().x - c.x;
			i->_drag_offset_y = i->getPosition().y - c.y;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			i->_selected = !i->_selected;
			i->setOutlineColor(i->_selected ? i->_selected_col : BLACK);
		}
		break;
	}
}

void Figure_handler::processDeclick(Cords c)
{
	for (auto i : _figures)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && i->_drag_drop)
		{
			i->_drag_drop = false;
			if (!i->_selected)
				i->setOutlineColor(BLACK);
		}
	}
}

std::list<Figure*>* Figure_handler::formSelectedList()
{
	std::list<Figure*>* l = new std::list<Figure*>();
	std::list<Figure*>::iterator it;
	for (it = _figures.begin(); it != _figures.end(); ++it)
		if ((*it)->_selected)
		{
			l->push_back(*it);
			_figures.erase(it);
		}

	return l;
}

void Figure_handler::swtchMove()
{
	_op.move = !_op.move;
}

void Figure_handler::chngObjColor()
{
	_op.chng_col = true;
}

void Figure_handler::chngScale(float s)
{
	for (auto i : _figures)
		if (i->_selected)
			i->setSize(sf::Vector2f(s, s));
}

int Figure_handler::countSelectedElements() const
{
	int count = 0;
	for (auto i : _figures)
		if (i->_selected)
			count++;
	return count;
}

void Figure_handler::swtchHide()
{
	for (auto i : _figures)
		if (i->_selected)
			i->swtchHide();
}

void Figure_handler::defaultState()
{
	for (auto i : _figures)
		if (i->_selected)
			i->defaultState();
}

void Figure_handler::swtchTrack()
{
	_op.enable__track = !_op.enable__track;
}

Cords Figure_handler::getActiveFigureCords()
{
	Cords c = {-100.f, -100.f};
	for (auto i : _figures)
		if (i->_selected)
		{
			c.x = i->getPosition().x;
			c.y = i->getPosition().y;
		}
	return c;
}

void Figure_handler::clone()
{
	for (auto& i : _figures)
		if (i->_selected)
		{
			i->_selected = false;
			i->setOutlineColor(BLACK);
			_figures.push_back(i->clone());
		}
}

void Figure_handler::getMemento(Memento& m) const
{
	m._figures.clear();
	m._figures = _figures;
}

void Figure_handler::setMemento(const Memento& m)
{
	for (auto& e : _figures)
		delete e;

	_figures.clear();
	_figures = m._figures;
}