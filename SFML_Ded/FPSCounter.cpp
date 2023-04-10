#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
    arr_fps = new float[FPS_SIZE];
}

FPSCounter::~FPSCounter()
{
    delete arr_fps;
}

void FPSCounter::update()
{
    arr_fps[i_fps++] = clock.getElapsedTime().asSeconds();
    clock.restart();
    if (i_fps < FPS_SIZE)
        return;

    i_fps = 0;
    float avrg = 0;

    for (int i = 0; i < FPS_SIZE; i++)
        avrg += 1 / arr_fps[i];

    avrg_fps = std::round(avrg / FPS_SIZE);
}

int FPSCounter::getFPS()
{
    return avrg_fps;
}