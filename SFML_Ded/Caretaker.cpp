#include "Caretaker.h"
#include <iostream>
#include <sstream>
#include <fstream>

void SimpleFigures(std::ifstream& fin, Figure** f);

void Caretaker::saveScene(const Figure_handler& f)
{
	std::string output;

	f.getMemento(_memento);

	std::ofstream fout("saves/save.txt");
	
	if (!fout)
	{
		std::cout << "Error! File was not opened! Source: Caretaker.cpp, line 14.\n";
		return;
	}

	std::cout << "Saving...\n";
	
	for (auto& e : _memento._figures)
		output += e->toString();

	fout << output;

	std::cout << "Saved!\n";

	fout.close();
}

void Caretaker::loadScene(Figure_handler& f)
{
	_memento._figures.clear();

	std::ifstream fin("saves/save.txt");

	if (!fin)
	{
		std::cout << "Error! File was not opened! Source: Caretaker.cpp, line 43.\n";
		return;
	}

	std::cout << "Loading...\n";

	while (!fin.eof())
	{
		Figure* f = nullptr;

		SimpleFigures(fin, &f);

		if (f == nullptr)
			break;
		
		_memento._figures.push_back(f);
	}

	std::cout << "Loaded!\n";

	fin.close();

	f.setMemento(_memento);
}

void SimpleFigures(std::ifstream& fin, Figure** f)
{
	std::string option;
	fin >> option;

	if (!(option == "Rectangle" || option == "Triangle" || option == "Star" || option == "Circle" || option == "Composite"))
		return;
	
	float x, y, size;
	unsigned int col;
	x = y = col = size = 0;
	std::string s_x, s_y, s_col, s_size;

	fin >> s_col;
	fin >> s_size;
	fin >> s_x >> s_y;

	x = std::stof(s_x);
	y = std::stof(s_y);
	size = std::stof(s_size);
	col = std::stoul(s_col);

	if (option == "Rectangle")
	{
		*f = new Rectangle(sf::Vector2f(x, y), sf::Vector2f(150.f, 60.f), sf::Color(col), MINT);
		(*f)->setSize(sf::Vector2f(size, size));
	}
	else if (option == "Triangle")
	{
		*f = new Triangle(sf::Vector2f(x, y), 30.f, sf::Color(col), MINT);
		(*f)->setSize(sf::Vector2f(size, size));
	}
	else if (option == "Star")
	{
		*f = new Star(sf::Vector2f(x, y), size, sf::Color(col), MINT);
	}
	else if (option == "Circle")
	{
		*f = new Circle(sf::Vector2f(x, y), 30.f, sf::Color(col), MINT);
		(*f)->setSize(sf::Vector2f(size, size));
	}
	else if (option == "Composite")
	{
		std::list<Figure*>* elems = new std::list<Figure*>;

		while (1)
		{
			Figure* inside = nullptr;
			SimpleFigures(fin, &inside);
			if (inside == nullptr)
				break;
			
			elems->push_back(inside);
		}
		
		*f = new Composite(elems);
	}
}