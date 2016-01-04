#include <iostream>
#include "AtomRing.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "GameScreen.h"
#include "MenuScreen.h"

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(1001, 769), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    GameScreen game;
    MenuScreen menu;

    vector <Screen*> screen;
    screen.push_back(&menu);
    screen.push_back(&game);
    int running = 0;
    while (running >=0) {
        running = screen[running]->Run(window);
    }
    return 0;
}

//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}