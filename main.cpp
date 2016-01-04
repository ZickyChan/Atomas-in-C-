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