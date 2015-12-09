//#include <iostream>
//#include <SFML>
//#include "AtomRing.h"
//
//using namespace std;
//
//int main() {
//    AtomRing ring = AtomRing();
//
//    ring.addAtom(2);
//    ring.addAtom(1);
//    ring.addAtom(1);
//    ring.addAtom(1);
//    ring.addAtom(1);
//    ring.addAtom(1);
//
//    ring.addAtom(2);
//
//    ring.addAtom(-2);
//
//    ring.processPlus();
//
//    Atom *atom = ring.getAtom();
//
//
//
//    cout << atom->index ;
//
//    return 0;
//}

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}