//
// Created by bit on 1/9/16.
//

#ifndef ATOMAS_ENTERIPCONTROLLER_H
#define ATOMAS_ENTERIPCONTROLLER_H

#include "Controller.h"
#include "../view/EnterIPVIew.h"
#include "../model/GameMultiModel.h"
#include "../view/GameMultiView.h"
#include "GameMultiController.h"
#include "../network/Connection.h"
#include <iostream>
#include <boost/asio.hpp>

using namespace std;

class EnterIPController:public Controller{
public:
    EnterIPController(EnterIPView &menu):view{menu}{ }

    /*This function will use to draw and get Event when the window is int the Enter IP View */

    virtual int Run(sf::RenderWindow &window){
        std::string ip;
        std::string port;
        boost::asio::io_service io_service;
        int input = 0;
        int count = 0;
        while (window.isOpen()){
            sf::Event event;
            view.setPosition();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return (-1);
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {

                        //Check if user is click in the OK text view
                        if(view.inOkText(event.mouseButton.x,event.mouseButton.y)){
                            //count represent how many time user click the button
                            count++;
                            //Only execute connection once
                            if(count == 1){
                                //Input is used to set the text of the status below in the view
                                input = 3;

                                view.setTextStatus(input);
                                view.draw(window,ip,port);

                                //Create the multi game model and view
                                GameMultiModel gm{ip,port,io_service};

                                GameMultiView gv1{gm.getAtomas(0).getRingSize(), gm.getCenterValue(1), 0, 20, 180, 150};
                                GameMultiView gv2{gm.getAtomas(1).getRingSize(), gm.getCenterValue(2), 500, 20, 180, 150};
                                GameMultiController gc{gv1, gv2, gm};


                                return gc.Run(window);
                            }
                        }
                            //Check if user is click in the spaces that user could modify IP
                        else if(view.inIp(event.mouseButton.x,event.mouseButton.y)){
                            input = 1;
                        }
                            //Check if user is click in the spaces that user could modify port
                        else if(view.inPort(event.mouseButton.x,event.mouseButton.y)){
                            input = 2;
                        }
                        else{
                            input = 0;
                            cout << "wrong menu" << endl;
                        }
                    }
                }
                if (event.type == sf::Event::TextEntered){
                    //If user is modifying IP
                    if(input == 1) {
                        //Check if the text entered is Back Space and the ip size must be greater than 0
                        if (event.text.unicode == 8 && ip.size() > 0) {
                            ip.pop_back();
                            std::cout << ip << std::endl;
                        }
                            //Check if the text enter is the text that have the unicode under 128
                        else if (event.text.unicode < 128) {
                            ip.push_back((char) event.text.unicode);
                            std::cout << ip << std::endl;
                        }
                    }

                        //If user is modying port
                        //Check the same way with ip
                    else if(input == 2){
                        if (event.text.unicode == 8 && port.size() >0) {
                            port.pop_back();
                            std::cout << port << std::endl;
                        }
                        else if (event.text.unicode < 128) {
                            port.push_back((char) event.text.unicode);
                            std::cout << port << std::endl;
                        }
                    }
                }
            }
            view.setTextStatus(input);
            view.draw(window,ip,port);

        }
        return (-1);
    }
private:
    EnterIPView view;
};




#endif //ATOMAS_ENTERIPCONTROLLER_H
