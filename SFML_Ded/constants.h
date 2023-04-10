#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//#define PRINT

// ----------- GUI OPTIONS -----------

#define OUTLINE_THICKNESS 3.f           // Outline of buttons
#define MARGIN 20.f                     // Margin between blocks and buttons

// ----------- Colors -----------

#ifdef PRINT

	#define BLACK sf::Color(255, 255, 255)
	#define MINT sf::Color(251, 177, 60)
	#define BLUE sf::Color(126, 162, 170)
	#define GREY sf::Color(222, 226, 234)
	#define PINK sf::Color(244, 91, 105)

#else

	#define BLACK sf::Color(48, 54, 51)
	#define MINT sf::Color(139, 232, 203)
	#define BLUE sf::Color(255, 255, 255)
	#define GREY sf::Color(136, 141, 167)
	#define PINK sf::Color(156, 122, 151)

#endif // PRINT

#define MAX_SCALE 2.f
#define MIN_SCALE 0.3f

// ----------- ------ -----------

struct Cords
{
    float x, y;
};

struct Options
{
	bool move = false;
	bool chng_col = false;
	bool enable__track = false;
};

// ----------- parametres -----------
const int WIDTH = 800;
const int HEIGHT = 800;
const float PANEL_Y = 3 * HEIGHT / 4;
// ----------- ---------- -----------