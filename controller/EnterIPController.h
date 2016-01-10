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
    virtual int Run(sf::RenderWindow &window){
        std::string ip;
        std::string port;
        int input = 0;
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
                        if(view.inOkText(event.mouseButton.x,event.mouseButton.y)){
                            cout << "aloha" << endl;
                            boost::asio::io_service io_service;
                            Connection connection{"Mike", 2};
                            //connection.connect(ip, port, io_service);
                            connection.connect("192.168.1.25", "6996", io_service);
                            connection.setup();

                            GameMultiModel gm{};

                            connection.wait_to_start(gm.getAtomas(0),gm.getAtomas(1));
                            GameMultiView gv1{gm.getAtomas(0).getRingSize(),1,0,20,180,150};
                            GameMultiView gv2{gm.getAtomas(1).getRingSize(),1,500,20,180,150};
                            GameMultiController gc {gv1,gv2,gm};

                            return gc.Run(window);
                            //return 3;
                        }
                        else if(view.inIp(event.mouseButton.x,event.mouseButton.y)){
                            input = 1;
                        }
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
                    if(input == 1) {
                        if (event.text.unicode == 8 && ip.size() > 0) {
                            ip.pop_back();
                            std::cout << ip << std::endl;
                        }
                        else if (event.text.unicode < 128) {
                            ip.push_back((char) event.text.unicode);
                            std::cout << ip << std::endl;
                        }
                    }
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
