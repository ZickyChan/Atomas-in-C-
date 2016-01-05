//
// Created by bit on 1/6/16.
//

#ifndef ATOMAS_MENUVIEW_H
#define ATOMAS_MENUVIEW_H

#include <SFML/Graphics.hpp>

class MenuView{
public:
    MenuView(int width, int height):scr_width{width},scr_height{height}{ }
    MenuView(MenuView &mv){
        scr_height = mv.scr_height;
        scr_width = mv.scr_width;
        title = mv.title;
        player_1 = mv.player_1;
        player_2 = mv.player_2;
        setting = mv.setting;
        font1 = mv.font1;
        font2 = mv.font2;
    }
    void setPosition(){
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

    }
    bool inPlayer1Text(int x, int y){
        bool result;
        sf::FloatRect player1Rect = player_1.getLocalBounds();
        result = ((x >= (player_1.getPosition().x - player1Rect.width/2.0f)) && (x <= (player_1.getPosition().x + player1Rect.width/2.0f))
                  && y >= player_1.getPosition().y - player1Rect.height/2.0f) && (y <= (player_1.getPosition().y + player1Rect.height/2.0f));
        return result;
    }

    bool inPlayer2Text(int x, int y){
        bool result;
        sf::FloatRect player2Rect = player_2.getLocalBounds();
        result = ((x >= (player_2.getPosition().x - player2Rect.width/2.0f)) && (x <= (player_2.getPosition().x + player2Rect.width/2.0f))
                  && y >= player_2.getPosition().y - player2Rect.height/2.0f) && (y <= (player_2.getPosition().y + player2Rect.height/2.0f));
        return result;
    }

    void draw(sf::RenderWindow &window){
        window.clear();
        window.draw(title);
        window.draw(player_1);
        window.draw(player_2);
        window.display();
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

#endif //ATOMAS_MENUVIEW_H
