//
// Created by bit on 1/8/16.
//

#ifndef ATOMAS_GAMEOVERCONTROLLER_H
#define ATOMAS_GAMEOVERCONTROLLER_H

#include <iostream>
#include "Controller.h"
#include "../view/GameOverView.h"

class GameOverController: public Controller{
public:
    GameOverController(GameOverView &view):gov{view}{ }
    virtual int Run(sf::RenderWindow &window){

        while (window.isOpen()){
            sf::Event event;
            gov.setPosition();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return (-1);
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {

                        if(gov.inReplayText(event.mouseButton.x,event.mouseButton.y) && gov.getMode() == 1){
                            return 1;

                        }
                        else if(gov.inBackMenuText(event.mouseButton.x,event.mouseButton.y)){
                            return 0;

                        }
                        else{
                            std::cout << "wrong menu" << std::endl;
                        }
                    }
                }
            }
            gov.draw(window);

        }
        return (-1);
    }
private:
    GameOverView gov;
};
#endif //ATOMAS_GAMEOVERCONTROLLER_H
