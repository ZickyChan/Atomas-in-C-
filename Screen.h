//
// Created by bit on 1/4/16.
//

#ifndef ATOMAS_SCREEN_H
#define ATOMAS_SCREEN_H

#include <SFML/Graphics.hpp>

class Screen{
public :
    virtual int Run (sf::RenderWindow &window) = 0;
};
#endif //ATOMAS_SCREEN_H
