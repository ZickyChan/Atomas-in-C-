//
// Created by bit on 1/9/16.
//

#ifndef ATOMAS_ENTERIPVIEW_H
#define ATOMAS_ENTERIPVIEW_H

#include <SFML/Graphics.hpp>


class EnterIPView{
public:
    EnterIPView(int w, int h):scr_width{w},scr_height{h}{}
    EnterIPView(EnterIPView &v){
        scr_height = v.scr_height;
        scr_width = v.scr_width;
        ipLabel = v.ipLabel;
        ipInput = v.ipInput;
        portInput = v.portInput;
        portLabel = v.portLabel;
        introTitle = v.introTitle;
        ok = v.ok;
    }
    void setPosition(){
        font1.loadFromFile("libelsuit.ttf");

        introTitle.setFont(font1);
        introTitle.setCharacterSize(60);
        introTitle.setColor(sf::Color::White);
        introTitle.setString("Enter server IP & Port");

        //set the position for the intro title
        sf::FloatRect textRect = introTitle.getLocalBounds();
        introTitle.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        introTitle.setPosition(sf::Vector2f(200,scr_height/2.0f - 200));


        //Format the ip label
        ipLabel.setFont(font1);
        ipLabel.setCharacterSize(40);
        ipLabel.setColor(sf::Color::White);
        ipLabel.setString("IP   : ");

        //set Position for ip label
        textRect = ipLabel.getLocalBounds();
        ipLabel.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
        ipLabel.setPosition(sf::Vector2f(200,scr_height/2.0f - 100));

        //Format the port label
        portLabel.setFont(font1);
        portLabel.setCharacterSize(40);
        portLabel.setColor(sf::Color::White);
        portLabel.setString("Port : ");

        //Set position for the port label
        textRect = portLabel.getLocalBounds();
        portLabel.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
        portLabel.setPosition(sf::Vector2f(200,scr_height/2.0f));

        //Format the port input and ip input
        portInput.setFont(font1);
        portInput.setCharacterSize(40);
        portInput.setColor(sf::Color::White);

        ipInput.setFont(font1);
        ipInput.setCharacterSize(40);
        ipInput.setColor(sf::Color::White);

        //Set the position for port input and ip input
        portInput.setPosition(250 + textRect.left + textRect.width/2.0f, scr_height/2.0f);
        ipInput.setPosition(250 + textRect.left + textRect.width/2.0f, scr_height/2.0f - 100);

        //Formar the ok text view
        ok.setFont(font1);
        ok.setCharacterSize(60);
        ok.setColor(sf::Color::White);

        ok.setPosition(scr_width - 200,scr_height/2.0f + 100);


    }
private:
    int scr_height;
    int scr_width;
    sf::Text ipLabel;
    sf::Text ipInput;
    sf::Text portLabel;
    sf::Text portInput;
    sf::Text introTitle;
    sf::Text ok;
    sf::Font font1;
};

#endif //ATOMAS_ENTERIPVIEW_H
