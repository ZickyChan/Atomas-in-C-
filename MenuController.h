//
// Created by bit on 1/6/16.
//

#ifndef ATOMAS_MENUCONTROLLER_H
#define ATOMAS_MENUCONTROLLER_H

#include "Controller.h"
#include "MenuView.h"
#include <iostream>

using namespace std;

class MenuController:public Controller{
public:
    MenuController(MenuView &menu):mv{menu}{ }
    virtual int Run(sf::RenderWindow &window){

        while (window.isOpen()){
            sf::Event event;
            mv.setPosition();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return (-1);
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        cout<< "mouse position x: " << event.mouseButton.x << " mouse position y: " <<event.mouseButton.y <<endl;



                        if(mv.inPlayer1Text(event.mouseButton.x,event.mouseButton.y)){
                            return 1;

                        }
                        else{
                            cout << "wrong menu" << endl;
                        }
                    }
                }
            }
            mv.draw(window);

        }
        return (-1);
    }
private:
    MenuView mv;

};

#endif //ATOMAS_MENUCONTROLLER_H
