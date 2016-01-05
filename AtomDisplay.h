//
// Created by bit on 1/3/16.
//

#ifndef ATOMAS_ATOMDISPLAY_H
#define ATOMAS_ATOMDISPLAY_H
#include <SFML/Graphics.hpp>

class AtomDisplay:sf::CircleShape {
public:
    AtomDisplay(int val, float radius): value{val},c{radius}{
        setColor();
    }
    AtomDisplay(const AtomDisplay &a): c{a.c.getRadius()}{
        value = a.value;
        setColor();
    }

    void setPosition(float x, float y){
        c.setPosition(x,y);
        text.setPosition(x+14,y);
    }
    void setColor(){
        if(value == 1){
            c.setFillColor(sf::Color::Red);
        }
        else if(value == 2){
            c.setFillColor(sf::Color::Green);
        }
        else if(value == 3){
            c.setFillColor(sf::Color::Blue);
        }
    }

    const sf::Vector2f& getCirclePosition(){
        return c.getPosition();
    }

    void move(float x, float y){
        c.move(x,y);
        text.setPosition(c.getPosition().x+14,c.getPosition().y);
    }

    void draw1(sf::RenderWindow &w){
        sf::Font font;
        font.loadFromFile("coolvetica rg.ttf");
        text.setFont(font);
        text.setColor(sf::Color::White);
        text.setCharacterSize(30);
        text.setString(std::to_string(value));
        w.draw(c);
        w.draw(text);
    }

    void reset(int val){
        value = val;
        setColor();
    }

//    void draw(sf::RenderTarget& target, sf::RenderStates states){
//
//    }
private:
    int value;
    sf::CircleShape c;
    sf::Text text;
};


#endif //ATOMAS_ATOMDISPLAY_H
