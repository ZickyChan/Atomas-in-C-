#include <iostream>
#include "AtomRing.h"
#include "Game.h"

<<<<<<< HEAD
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
=======
using namespace std;

int main() {
    Game *game = new Game(4);
    AtomRing *ring = new AtomRing();
    Atom *atom = randomAtom(-1, 10);

    game->addAtoms(4);
    game->printGame();

    while (true) {
        char input;
        cin >> input;
        if (input == 'a')
            game->back();
        else if (input == 'd')
            game->forward();
        else if (input == 's')
            game->playerToRing();
        else
            break;
        game->printGame();
    }
>>>>>>> 3c299188f0080fd1a11e9ea81d997cddfd562db4

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