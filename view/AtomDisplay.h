//
// Created by bit on 1/3/16.
//

#ifndef ATOMAS_ATOMDISPLAY_H
#define ATOMAS_ATOMDISPLAY_H
#include <SFML/Graphics.hpp>
using namespace std;

class AtomDisplay:sf::CircleShape {
public:
    AtomDisplay(int val, float radius): value{val},c{radius}{

        setColor();
    }
    AtomDisplay(const AtomDisplay &a): c{a.c.getRadius()}{
        value = a.value;
        setColor();
    }

    void setPosition(float x, float y) {
        c.setPosition(x, y);
        if (c.getRadius() == 20) {
            if (value == 0) {
                text.setPosition(x + 12, y);
            }
            else if (value == -1) {
                text.setPosition(x + 16, y);
            }
            else if (value > 10){
                text.setPosition(x + 10, y);
            }
            else{
                text.setPosition(x + 14, y);
            }
        }
    }
    void setColor(){
        setColorArray();
        if(value > 0){
            c.setFillColor(color[value%color.size()]);
        }
        else if(value == 0){
            c.setFillColor(sf::Color::Red);
        }
        else{
            c.setFillColor(sf::Color::Blue);
        }
        text.setColor(sf::Color::White);
    }
    void setDisappear(){
        c.setFillColor(sf::Color::Transparent);
        text.setColor(sf::Color::Transparent);
    }

    const sf::Vector2f& getCirclePosition(){
        return c.getPosition();
    }

    void move(float x, float y){
        c.move(x,y);

        if (c.getRadius() == 20) {
            if (value == 0)
                text.setPosition(c.getPosition().x + 12, c.getPosition().y);
            else if(value == -1)
                text.setPosition(c.getPosition().x + 16, c.getPosition().y);
            else
                text.setPosition(c.getPosition().x + 14, c.getPosition().y);
        }
    }

    void draw1(sf::RenderWindow &w){
        sf::Font font;
        font.loadFromFile("coolvetica rg.ttf");
        text.setFont(font);

        //cout << "AAAAA: \t" << value << endl;

        if(c.getRadius() == 20) {
            text.setCharacterSize(30);
        }
        if(value > 0) {
            text.setString(std::to_string(value));
        }
        else if(value == 0){
            text.setString("+");
        }
        else if(value == -1){
            text.setString("-");
        }

        w.draw(c);
        w.draw(text);
    }
    void draw(sf::RenderWindow &w,sf::Transform t){
        sf::Font font;
        font.loadFromFile("coolvetica rg.ttf");
        text.setFont(font);
        if(c.getRadius() == 20) {
            text.setCharacterSize(30);
        }
        if(value > 0) {
            text.setString(std::to_string(value));
        }
        else if(value == 0){
            text.setString("+");
        }
        else if(value == -1){
            text.setString("-");
        }
        w.draw(c,t);
        w.draw(text,t);
    }

    float getCircleRadius(){
        return c.getRadius();
    }


    void reset(int val){
        value = val;
        setColor();
    }

    int getValue(){
        return value;
    }
    std::string getText(){
        return std::string(text.getString());
    }

    void setColorArray(){
        color.push_back(sf::Color(9,217,242));
        color.push_back(sf::Color(0,255,0));
        color.push_back(sf::Color(242,9,228));
        color.push_back(sf::Color(232,83,9));
        color.push_back(sf::Color(139,75,255));
        color.push_back(sf::Color(82,99,127));
        color.push_back(sf::Color(255,10,87));
        color.push_back(sf::Color(22,38,64));

    }

//    void draw(sf::RenderTarget& target, sf::RenderStates states){
//
//    }
private:
    int value;
    sf::CircleShape c;
    sf::Text text;
    vector <sf::Color> color;
};


#endif //ATOMAS_ATOMDISPLAY_H
