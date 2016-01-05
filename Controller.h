//
// Created by bit on 1/5/16.
//

#ifndef ATOMAS_CONTROLLER_H
#define ATOMAS_CONTROLLER_H

#include <SFML/Graphics/RenderWindow.hpp>

class Controller{
public :
    virtual int Run (sf::RenderWindow &window) = 0;
};

#endif //ATOMAS_CONTROLLER_H
