#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

#include "view/GameView.h"
#include "model/GameModel.h"
#include "controller/GameController.h"
#include "view/MenuView.h"
#include "controller/MenuController.h"
#include "view/EnterIPVIew.h"
#include "controller/EnterIPController.h"

using namespace std;

int main() {

    /*sf::RenderWindow window(sf::VideoMode(1001, 769), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    GameScreen game;
    MenuScreen menu;

    vector <Screen*> screen;
    screen.push_back(&menu);
    screen.push_back(&game);
    int running = 0;
    while (running >=0) {
        running = screen[running]->Run(window);
    }*/
    sf::RenderWindow window(sf::VideoMode(1001, 769), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

    GameModel game_model;
    GameView game_view{game_model.getCenterValue(),game_model.getAtomRingSize(),20,180,150};

    GameController game_controller{game_view,game_model};

    MenuView mv{1001,769};
    MenuController mc{mv};

    EnterIPView eipv{1001,769};
    EnterIPController eipc{eipv};

    vector <Controller*> controller;
    controller.push_back(&mc);
    controller.push_back(&game_controller);
    controller.push_back(&eipc);

    int mode = 0;

    while (mode >=0) {
        mode = controller[mode]->Run(window);
    }

    /*cout << "value: " << game_model.getCenterValue() << " size: " << game_model.getAtomRingSize() << endl;

    for (int i=0;i<game_model.getAtomRingSize();i++){
        cout << "value at point " << i << " : " << game_model.getAtomValue(i);
    }*/
    return 0;
}
