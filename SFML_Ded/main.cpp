#include <iostream>
#include <map>
#include "FPSCounter.h"
#include "Background.h"
#include "GUI.h"
#include "constants.h"
#include "Figure_handler.h"

typedef ngui::Button But;
typedef ngui::Sign Sgn;

void signsInit(std::map<std::string, ngui::Sign*>& signs, Background& bg, FPSCounter& fps);
void buttonsInit(std::map<std::string, ngui::Button*>& buts, Background& bg, std::map<std::string, ngui::Sign*>& signs, Figure_handler& figures, Caretaker& caretaker);
void clearGUIMemory(std::map<std::string, ngui::Button*>& buts, std::map<std::string, ngui::Sign*>& signs, ngui::Slider* s);

using namespace sf;

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "week", Style::Titlebar | Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    // ------- Init objects ------- 
    float panel_height = HEIGHT - PANEL_Y;
    Background bg(HEIGHT, WIDTH, BLACK);
    RectangleShape panel(Vector2f(WIDTH, panel_height)); // Bottom panel for GUI
    panel.setPosition(Vector2f(0, PANEL_Y));
    panel.setFillColor(GREY);

    FPSCounter fps;

    Caretaker caretaker;

    Figure_handler* figures = Figure_handler::getInstance();
    ngui::GUI* gui = ngui::GUI::getInstance();

    // ------- Creating text for GUI ----------

    std::map<std::string, ngui::Sign*> signs;
    signsInit(signs, bg, fps);

    // ------- Creating buttons for GUI -------

    std::map<std::string, ngui::Button*> buttons;
    buttonsInit(buttons, bg, signs, *figures, caretaker);

    // ------- Creating slider for GUI --------

    ngui::Slider* scaling = new ngui::Slider(sf::Vector2f(180.f + MARGIN, 40.f),
        sf::Vector2f(5 * MARGIN + signs["crt_sign"]->getDimensions().x + 240.f, PANEL_Y + MARGIN * 2.f + 40.f + MARGIN));

    scaling->callback = [figures](float s) { figures->chngScale(s); };

    // ------- Adding GUI objects to controller -------
    
    for (auto& e : signs)
        gui->addToHandler(*(e.second));

    for (auto& e : buttons)
        gui->addToHandler(*(e.second));

    gui->addToHandler(*scaling);

    // ------- Update loop -------

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
            {
                Cords c = { (float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y };
                gui->processClick({ (float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y });
                figures->processClick(c);
                break;
            }
            case Event::MouseButtonReleased:
            {
                Cords c = { (float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y };
                gui->processDeclick({ (float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y });
                figures->processDeclick(c);
                break;
            }
            }
        }

        // ------- Update section ------- 

        // - FPS counter -

        fps.update();

        // - ---------- -

        bg.update();
        gui->update(window);
        figures->update(window);

        // ------- -------------- ------- 

        window.clear();

        // ------- Draw section --------- 

        window.draw(bg);
        window.draw(*figures);
        window.draw(panel);
        window.draw(*gui);
        
        // ------- ------------ --------- 

        window.display();
    }
    
    clearGUIMemory(buttons, signs, scaling);

    return 0;
}

void signsInit(std::map<std::string, ngui::Sign*> &signs, Background& bg, FPSCounter& fps)
{
    signs.emplace("snowflakes_counter", new Sgn(sf::Vector2f(WIDTH - 2 * MARGIN - 120.f, PANEL_Y + MARGIN / 2), "Snowflakes: "));
    signs["snowflakes_counter"]->update_callback = [&bg]() { return bg.getSnowlakesCount(); };

    signs.emplace("fps_counter", new Sgn(sf::Vector2f(WIDTH - 65.f, MARGIN / 4), "FPS:", "fonts/Roboto-Medium.ttf", 16, BLUE));
    signs["fps_counter"]->update_callback = [&fps]() {return fps.getFPS(); };

    signs.emplace("crt_sign", new Sgn(sf::Vector2f(200.f, PANEL_Y + MARGIN / 2), "Creating"));

    signs.emplace("inter", new Sgn(sf::Vector2f(450.f, PANEL_Y + MARGIN / 2), "Interaction"));

    signs.emplace("cmpst", new Sgn(sf::Vector2f(MARGIN / 4, PANEL_Y + MARGIN / 2), "Composite"));
}

void buttonsInit(std::map<std::string, ngui::Button*>& buts, Background& bg, std::map<std::string, ngui::Sign*>& signs, Figure_handler& figures, Caretaker& caretaker)
{
    // Right side

    buts.emplace("b_incr_snowflakes", new But(sf::Vector2f(40.f, 40.f), Vector2f(WIDTH - MARGIN - 40.f, PANEL_Y + 2.f * MARGIN), MINT, BLUE, "+"));
    buts["b_incr_snowflakes"]->callback = [&bg]() {bg.increaseSnowflakes(); };   // + button;

    buts.emplace("b_dcrs_snowflakes", new But(sf::Vector2f(40.f, 40.f), Vector2f(WIDTH - MARGIN - 40.f, PANEL_Y + 3.f * MARGIN + 40.f), MINT, BLUE, "-"));
    buts["b_dcrs_snowflakes"]->callback = [&bg]() { bg.decreaseSnowflakes(); };// - button;

    buts.emplace("menu", new But(sf::Vector2f(80.f, 80.f + MARGIN), Vector2f(WIDTH - 2 * MARGIN - 120.f, PANEL_Y + 2 * MARGIN), MINT, BLUE, "on/off"));
    buts["menu"]->callback = [&bg]() { bg.switchDynamicBackground(); };       // Switch dynamic background 

    // Main part

    const float up_button_y = PANEL_Y + MARGIN * 2.f, down_button_y = PANEL_Y + MARGIN * 3.f + 40.f;
    buts.emplace("rect", new But(sf::Vector2f(120.f, 40.f), sf::Vector2f(2 * MARGIN + signs["crt_sign"]->getDimensions().x, up_button_y), MINT, BLUE, "Rectangle"));
    buts["rect"]->callback = [&figures]() {figures.addToHandler(new Rectangle()); }; //new Rectangle()

    buts.emplace("circle", new But(sf::Vector2f(120.f, 40.f), sf::Vector2f(2 * MARGIN + signs["crt_sign"]->getDimensions().x, down_button_y), MINT, BLUE, "Circle"));
    buts["circle"]->callback = [&figures]() {figures.addToHandler(new Circle()); }; //new Circle()

    buts.emplace("triangle", new But(sf::Vector2f(120.f, 40.f), sf::Vector2f(3 * MARGIN + signs["crt_sign"]->getDimensions().x + 120.f, up_button_y), MINT, BLUE, "Triangle"));
    buts["triangle"]->callback = [&figures]() {figures.addToHandler(new Triangle()); }; //new Triangle()

    buts.emplace("star", new But(sf::Vector2f(120.f, 40.f), sf::Vector2f(3 * MARGIN + signs["crt_sign"]->getDimensions().x + 120.f, down_button_y), MINT, BLUE, "Star"));
    buts["star"]->callback = [&figures]() {figures.addToHandler(new Star()); }; //new Star()

    buts.emplace("hide", new But(sf::Vector2f(24.f, 40.f), sf::Vector2f(MARGIN / 4, down_button_y), MINT, BLUE, "H"));
    buts["hide"]->callback = [&figures]() {figures.swtchHide(); };

    buts.emplace("defaultState", new But(sf::Vector2f(24.f, 40.f), sf::Vector2f(24.f + 3 * MARGIN / 4, down_button_y), MINT, BLUE, "D"));
    buts["defaultState"]->callback = [&figures]() {figures.defaultState(); };

    buts.emplace("_track", new But(sf::Vector2f(24.f, 40.f), sf::Vector2f(48.f + 5 * MARGIN / 4, down_button_y), MINT, BLUE, "T"));
    buts["_track"]->callback = [&figures]() { figures.swtchTrack(); };

    // ------ Interacting with figures --------

    buts.emplace("mov", new But(sf::Vector2f(100, 40.f), sf::Vector2f(4 * MARGIN + signs["crt_sign"]->getDimensions().x + 240.f, up_button_y), MINT, BLUE, "Move"));
    buts["mov"]->callback = [&figures]() {figures.swtchMove(); };

    buts.emplace("chng_col", new But(sf::Vector2f(120.f, 40.f), sf::Vector2f(5 * MARGIN + signs["crt_sign"]->getDimensions().x + 340.f, up_button_y), MINT, BLUE, "Chng Color"));
    buts["chng_col"]->callback = [&figures]() {figures.chngObjColor(); };

    // ------ Composite button ----------------

    buts.emplace("cmpst_but", new But(sf::Vector2f(90.f, 40.f), sf::Vector2f(MARGIN / 3, up_button_y), MINT, BLUE, "CMPST"));
    buts["cmpst_but"]->callback = [&figures]()
    {
        if (figures.countSelectedElements() > 1)
            figures.addToHandler(new Composite(figures.formSelectedList()));
    };//new Composite()

    // ------ Footer ------

    buts.emplace("save", new But(sf::Vector2f(5 * MARGIN + signs["crt_sign"]->getDimensions().x + 195.f, 40.f),
        sf::Vector2f(MARGIN / 4, down_button_y + 50.f), MINT, BLUE, "Save"));
    buts["save"]->callback = [&figures, &caretaker]() { caretaker.saveScene(figures); };

    buts.emplace("load", new But(sf::Vector2f(5 * MARGIN + signs["crt_sign"]->getDimensions().x + 222.f, 40.f),
        sf::Vector2f(5 * MARGIN + signs["crt_sign"]->getDimensions().x + 220.f, down_button_y + 50.f), MINT, BLUE, "Load"));
    buts["load"]->callback = [&figures, &caretaker]() { caretaker.loadScene(figures); };

    // ------ Floating Clone button ------

    buts.emplace("clone", new But(sf::Vector2f(24.f, 30.f), sf::Vector2f(-40.f, 0), MINT, BLUE, "C"));
    buts["clone"]->callback = [&figures]() { figures.clone(); };
    buts["clone"]->update_callback = [&figures](ngui::Button* b) 
    { b->setPosition({ figures.getActiveFigureCords().x - 35.f, figures.getActiveFigureCords().y - 20.f}); };
}

void clearGUIMemory(std::map<std::string, ngui::Button*>& buts, std::map<std::string, ngui::Sign*>& signs, ngui::Slider* s)
{
    for (auto& e : buts)
        delete e.second;

    for (auto& e : signs)
        delete e.second;

    delete s;
}