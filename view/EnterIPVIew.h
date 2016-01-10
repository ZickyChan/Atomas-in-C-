//
// Created by bit on 1/9/16.
//

#ifndef ATOMAS_ENTERIPVIEW_H
#define ATOMAS_ENTERIPVIEW_H

#include <SFML/Graphics.hpp>
#include <iostream>


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




        //Format the ip label
        ipLabel.setFont(font1);
        ipLabel.setCharacterSize(40);
        ipLabel.setColor(sf::Color::White);
        ipLabel.setString("IP   : ");

        //set Position for ip label
        sf::FloatRect  textRect = ipLabel.getLocalBounds();
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


        //set the position for the intro title
        introTitle.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top  + textRect.height/2.0f);
        introTitle.setPosition(sf::Vector2f(200,scr_height/2.0f - 200));

        //Format the port input and ip input
        portInput.setFont(font1);
        portInput.setCharacterSize(40);
        portInput.setColor(sf::Color::White);

        ipInput.setFont(font1);
        ipInput.setCharacterSize(40);
        ipInput.setColor(sf::Color::White);

        //Set the position for port input and ip input
        portInput.setPosition(250 + textRect.left + textRect.width/2.0f, scr_height/2.0f);
        portInput.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
        ipInput.setOrigin(textRect.left + textRect.width/2.0f,
                          textRect.top  + textRect.height/2.0f);
        ipInput.setPosition(250 + textRect.left + textRect.width/2.0f, scr_height/2.0f - 100);

        //Formar the ok text view
        ok.setFont(font1);
        ok.setCharacterSize(60);
        ok.setColor(sf::Color::White);

        textRect = ok.getLocalBounds();
        ok.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
        ok.setPosition(scr_width - 300,scr_height/2.0f + 100);
        ok.setString("OK");

        //Set up the status text
        //Status text is use to notice the user that which place the user is modifying
        status.setFont(font1);
        status.setCharacterSize(30);
        status.setColor(sf::Color::White);

        //Set position for the status
        textRect = status.getLocalBounds();
        status.setOrigin(textRect.left + textRect.width/2.0f,
                            textRect.top  + textRect.height/2.0f);
        status.setPosition(sf::Vector2f(scr_width/2.0f,scr_height - 200));


    }
    bool inOkText(float x, float y){
        bool result;
        sf::FloatRect okRect = ok.getLocalBounds();
        result = ((x >= (ok.getPosition().x - okRect.width/2.0f)) && (x <= (ok.getPosition().x + okRect.width/2.0f))
                  && y >= ok.getPosition().y - okRect.height/2.0f) && (y <= (ok.getPosition().y + okRect.height/2.0f));
        return result;
    }

    bool inIp(float x, float y){
        bool result;
        sf::FloatRect ipRect = portLabel.getLocalBounds();
        result = ((x >= (ipInput.getPosition().x - ipRect.width/2.0f)) && (x <= (ipInput.getPosition().x + ipRect.width*5))
                  && y >= ipInput.getPosition().y - ipRect.height/2.0f) && (y <= (ipInput.getPosition().y + ipRect.height/2.0f));
        return result;
    }

    bool inPort(float x, float y){
        bool result;
        sf::FloatRect portRect = portLabel.getLocalBounds();
        result = ((x >= (portInput.getPosition().x - portRect.width/2.0f)) && (x <= (portInput.getPosition().x + portRect.width*5))
                  && y >= portInput.getPosition().y - portRect.height/2.0f) && (y <= (portInput.getPosition().y + portRect.height/2.0f));
        return result;
    }
    void setTextStatus(int input){
        if(input == 0){
            status.setString("You can't modify anything!");
        }
        else if(input == 1){
            status.setString("You are modifying IP address!");
        }
        else{
            status.setString("You are modifying port!");
        }

    }


    void draw(sf::RenderWindow &window,std::string ip, std::string port){
        if(ip == ""){
            ip= "                      ";

        }
        if(port == ""){
            port = "                      ";
        }
        window.clear();
        ipInput.setString(ip);
        portInput.setString(port);
        window.draw(ipLabel);
        window.draw(ipInput);
        window.draw(portLabel);
        window.draw(portInput);
        window.draw(introTitle);
        window.draw(ok);
        window.draw(status);
        window.display();
    }

private:
    int scr_height;
    int scr_width;
    sf::Text ipLabel;
    sf::Text ipInput;
    sf::Text portLabel;
    sf::Text portInput;
    sf::Text introTitle;
    sf::Text status;
    sf::Text ok;
    sf::Font font1;
};

#endif //ATOMAS_ENTERIPVIEW_H
