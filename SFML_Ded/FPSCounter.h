#pragma once
#include "constants.h"


class FPSCounter
{

    const int FPS_SIZE = 5; // FPS Accuracy
    int avrg_fps = 60, i_fps = 0;
    float* arr_fps;

    sf::Clock clock;
    sf::Time fps_time;

public:
    FPSCounter();

    ~FPSCounter();

    void update();

    int getFPS();
};
