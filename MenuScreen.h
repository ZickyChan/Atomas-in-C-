//
// Created by bit on 1/4/16.
//

#ifndef ATOMAS_MENUSCREEN_H
#define ATOMAS_MENUSCREEN_H

#include "Screen.h"

class MenuScreen: public Screen{
public:
    MenuScreen():scr_width{1001},scr_height{769}{ }
    virtual int Run(sf::RenderWindow &window){
        font1.loadFromFile("kenyan coffee rg it.ttf");
        font2.loadFromFile("libelsuit.ttf");

        title.setFont(font1);
        title.setCharacterSize(80);
        title.setColor(sf::Color::White);
        title.setString("Welcome to Atomas!");

        //center Title
        sf::FloatRect textRect = title.getLocalBounds();
        title.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
        title.setPosition(sf::Vector2f(scr_width/2.0f,scr_height/2.0f - 150));

        player_1.setFont(font2);
        player_1.setCharacterSize(40);
        player_1.setColor(sf::Color::White);
        player_1.setString("1 Player");

        //center player 1 text
        textRect = player_1.getLocalBounds();
        player_1.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        player_1.setPosition(sf::Vector2f(scr_width/2.0f,scr_height/2.0f - 20));


        player_2.setFont(font2);
        player_2.setCharacterSize(40);
        player_2.setColor(sf::Color::White);
        player_2.setString("2 Player");

        //center player 2 text
        textRect = player_2.getLocalBounds();
        player_2.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
        player_2.setPosition(sf::Vector2f(scr_width/2.0f,scr_height/2.0f + 60));


        while (window.isOpen()){
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return (-1);
                }
                sf::FloatRect player1Rect = player_1.getLocalBounds();
                sf::FloatRect player2Rect = player_2.getLocalBounds();
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        cout<< "mouse position x: " << event.mouseButton.x << " mouse position y: " <<event.mouseButton.y <<endl;
                        cout<< "text position x: " << (player_1.getPosition().x - player1Rect.width/2.0f) << " text position y: " <<player_1.getPosition().y <<endl;
                        cout << "end point position x: " << player_1.getPosition().x + player1Rect.width/2.0f <<"  end point position y: "<< player_1.getPosition().y + player1Rect.height <<endl;


                        if((event.mouseButton.x >= (player_1.getPosition().x - player1Rect.width/2.0f)) && (event.mouseButton.x <= (player_1.getPosition().x + player1Rect.width/2.0f))
                                && (event.mouseButton.y >= player_1.getPosition().y - player1Rect.height/2.0f) && (event.mouseButton.y <= (player_1.getPosition().y + player1Rect.height/2.0f))){
                            return 1;

                        }
                        else{
                            cout << "wrong menu" << endl;
                        }
                    }
                }
            }

            window.clear();
            window.draw(title);
            window.draw(player_1);
            window.draw(player_2);
            window.display();
        }

        return -1;
    }
private:
    int scr_width;
    int scr_height;
    sf::Text title;
    sf::Text player_1;
    sf::Text player_2;
    sf::Text setting;
    sf::Font font1;
    sf::Font font2;
};

#endif //ATOMAS_MENUSCREEN_H
