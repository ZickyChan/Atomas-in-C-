#include <iostream>
#include "AtomRing.h"
#include "Game.h"

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