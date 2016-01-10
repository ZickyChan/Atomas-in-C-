//
// Created by bit on 1/10/16.
//

#ifndef ATOMAS_GAMEMULTICONTROLLER_H
#define ATOMAS_GAMEMULTICONTROLLER_H

#define PI 3.14159265

#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <iostream>
#include <thread>
#include "../view/AtomDisplay.h"
#include "Controller.h"
#include "../view/GameMultiView.h"
#include "../model/GameMultiModel.h"
#include "GameController.h"

using namespace std;

class GameMultiController:public Controller{
public:
    GameMultiController(GameMultiView &gameView, GameMultiView &game2, GameMultiModel &gameModel):gv1{gameView}, gv2{game2}, gm{gameModel}{

    }

    void checkAtoms(sf::RenderWindow &window) {
        int index = 0;
        int combo = 0;
        while (index < gm.getRing().get_size()) {
            if (gm.getRing().get_atom(index) == PROTON) {
                combo = gm.check_proton(index);
                if (combo > 0) {
                    sf::Transform t1;
                    sf::Transform t2;
                    for (int i = 1; i <= (combo); i++) {
                        float angle = calculateAngle(gv1.atoms[(index + i) % gv1.atoms.size()], gv1.atoms[index], 150);
                        int step = 0;
                        while (true) {
                            if (angle <= step) {
                                break;
                            }
                            window.clear(sf::Color::Black);

                            t1.rotate(2.0, {250, 364});
                            t2.rotate(-2.0, {250, 364});

                            if ((gv1.atoms[index].getCirclePosition().y + 194) > 344) {
                                gv1.atoms[(index + i) % gv1.atoms.size()].draw(window, t2);
                                gv1.atoms[(index - i + gv1.atoms.size()) % gv1.atoms.size()].draw(window, t1);
                            }
                            else {
                                gv1.atoms[(index + i) % gv1.atoms.size()].draw(window, t1);
                                gv1.atoms[(index - i + gv1.atoms.size()) % gv1.atoms.size()].draw(window, t2);
                            }
                            window.draw(gv1.outsideCircle);
                            window.draw(gv1.scoreText);
                            gv1.centerPoint.draw1(window);
                            for (int j = 0; j < gv1.atoms.size(); j++) {
                                if (j != ((index + i) % gv1.atoms.size()) &&
                                    j != (index - i + gv1.atoms.size()) % gv1.atoms.size()) {
                                    gv1.atoms[j].draw1(window);
                                }


                            }
                            gv2.draw(window);

                            window.display();
                            step += i + 1;
                        }
                        gv1.setValueForScoreText(gm.getScore(1));
                        gv1.atoms[(index + i) % gv1.atoms.size()].setPosition(gv1.atoms[index].getCirclePosition().x,
                                                                              gv1.atoms[index].getCirclePosition().y);
                        gv1.atoms[(index - i + gv1.atoms.size()) % gv1.atoms.size()].setPosition(
                                gv1.atoms[index].getCirclePosition().x, gv1.atoms[index].getCirclePosition().y);
                        window.clear(sf::Color::Black);
                        gv1.draw(window);
                        gv2.draw(window);

                        window.display();


                    }

                    for (int i = combo * 2; i > 0; i--) {
                        gv1.atoms.pop_back();
                    }
                    gv1.insideCircle.setPointCount(gm.getAtomRingSize());
                    gv1.setValueForAtoms(gm,1);
                    for (int i = 0; i < gv1.insideCircle.getPointCount(); i++) {
                        sf::Vector2f position = gv1.insideCircle.getPoint(i);
                        gv1.atoms[i].setPosition(position.x + 80, position.y + 194);
                        //gv.atoms[i].draw1(window);
                    }
                    index = 0;
                    combo = 0;
                }
                else{
                    index++;
                }
            }
            else{
                index++;
            }
        }
        gm.setNewCenterValue();

        cout << endl << endl << endl;
        cout << "RING 1 IS :    " <<endl;
        gm.print();
    }

    void thread_function() {
        string type;
        float y0,x0,k;

        do {
            Data data(gm.read());
            type = data.get("type");

            cout << "type receive: " << type << endl;
            if(type == "normal"){
                int index = stoi(data.get("index"));
                int new_atom = stoi(data.get("new atom"));

                gv2.position_insert = index;
                AtomDisplay temp{gv2.centerPoint};

                if (gv2.position_insert > -1) {
                    gv2.atoms.insert(gv2.atoms.begin() + gv2.position_insert, temp);
                    gm.addAtomToRing2(gv2.position_insert - 1);
                }
                else if (gv2.position_insert == -1) {
                    gv2.atoms.push_back(temp);
                    gm.addAtomToRing2(gm.getAtomRing2Size() - 1);
                }

                gv2.insideCircle.setPointCount(gm.getAtomRing2Size());
                for (int i = 0; i < gv2.insideCircle.getPointCount(); i++) {
                        sf::Vector2f position = gv2.insideCircle.getPoint(i);
                        gv2.atoms[i].setPosition(position.x + 80 + gv2.offsetX, position.y + 194);
                }


                gv2.centerPoint.reset(new_atom);

                gm.print2();


                index = 0;
                int combo = 0;
                while (index < gm.getRing2().get_size()) {
                    if (gm.getRing2().get_atom(index) == PROTON) {
                        combo = gm.check_proton2(index);
                        if(combo > 0) {
                            gv2.setValueForScoreText(gm.getScore(2));
                            for (int i = combo * 2; i > 0; i--) {
                                gv2.atoms.pop_back();
                            }
                            gv2.insideCircle.setPointCount(gm.getAtomRing2Size());
                            gv2.setValueForAtoms(gm,2);
                            for (int i = 0; i < gv2.insideCircle.getPointCount(); i++) {
                                sf::Vector2f position = gv2.insideCircle.getPoint(i);
                                gv2.atoms[i].setPosition(position.x + 80 + gv2.offsetX, position.y + 194);
                            }
                            index = 0;
                            combo = 0;
                        }
                        else{
                            index++;
                        }
                    }
                    else{
                        index++;
                    }
                }

                cout << endl << endl << "RING 2 IS:    " << endl;
                gm.setNewCenterValue(new_atom);
                gm.print2();


            }
            else if(type == "minus"){
                int index = stoi(data.get("index"));
                int new_atom = stoi(data.get("new atom"));

                cout << "minus index received: " << index << endl;
                gm.deleteAtom2(index);
                gv2.atoms.pop_back();
                gv2.setValueForAtoms(gm,2);
                gv2.numPoints = gm.getAtomRing2Size();
                //gv.centerPoint.reset(gm.getCenterValue());

                gv2.insideCircle.setPointCount(gv2.numPoints);
                for (int i = 0; i < gv2.insideCircle.getPointCount(); i++) {
                    sf::Vector2f position = gv2.insideCircle.getPoint(i);
                    gv2.atoms[i].setPosition(position.x + 80 + gv2.offsetX, position.y + 194);

                }
                gm.setNewCenterValue(new_atom);
                gv2.centerPoint.reset(new_atom);

                index = 0;
                int combo = 0;
                while (index < gm.getRing2().get_size()) {
                    if (gm.getRing2().get_atom(index) == PROTON) {
                        combo = gm.check_proton2(index);
                        if(combo > 0) {
                            gv2.setValueForScoreText(gm.getScore(2));
                            for (int i = combo * 2; i > 0; i--) {
                                gv2.atoms.pop_back();
                            }
                            gv2.insideCircle.setPointCount(gm.getAtomRing2Size());
                            gv2.setValueForAtoms(gm,2);
                            for (int i = 0; i < gv2.insideCircle.getPointCount(); i++) {
                                sf::Vector2f position = gv2.insideCircle.getPoint(i);
                                gv2.atoms[i].setPosition(position.x + 80 + gv2.offsetX, position.y + 194);
                            }
                            index = 0;
                            combo = 0;
                        }
                        else{
                            index++;
                        }
                    }
                    else{
                        index++;
                    }
                }
            }
        }while(type != "END");
    }



    virtual int Run(sf::RenderWindow &window);
private:
    GameMultiView gv1;
    GameMultiView gv2;
    GameMultiModel gm;
    sf::RenderWindow *window;
    std::thread *t1;
};

int GameMultiController::Run(sf::RenderWindow &window) {
    float k,x0,y0,r,b,c;
    gv1.addAtomDisplay(gm.getAtomas(0));
    gv1.setPosition();
    window.clear();

    gv2.addAtomDisplay(gm.getAtomas(1));
    gv2.setPosition();

    t1 = new thread(&GameMultiController::thread_function, this);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return (-1);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cout << "left click " << endl;
                    if (std::pow((event.mouseButton.x - 250), 2) + std::pow((event.mouseButton.y - 364), 2) <=
                        std::pow(180, 2) &&
                        std::pow((event.mouseButton.x - 250), 2) + std::pow((event.mouseButton.y - 364), 2) >
                        std::pow(50, 2)
                        && gv1.centerPoint.getValue() != (-1)
                            ) {
                        if (gv1.insideCircle.getPointCount() == 1) {
                            AtomDisplay temp{gv1.centerPoint};

                            gv1.atoms.push_back(temp);
                            gm.addAtomToRing(gm.getAtomRingSize() - 1);


                            gv1.centerPoint.reset(gm.getCenterValue(1));

                            gv1.insideCircle.setPointCount(gm.getAtomRingSize());
                            for (int i = 0; i < gv1.insideCircle.getPointCount(); i++) {
                                sf::Vector2f position = gv1.insideCircle.getPoint(i);
                                gv1.atoms[i].setPosition(position.x + 80, position.y + 194);
                            }

                            gm.send_normal(-1);

                        }
                        else {
                            for (int i = 0; i < gv1.insideCircle.getPointCount(); i++) {
                                cout << "in here again " << endl;
                                //Calculate the position of the point that is on the circle the content the Y Position of the atoms have x coordinate equals to event mouse button x
                                //First have to find the general equation y = k(x - x0) + b0 which content the center point of insideCircle and the event mouse button position
                                y0 = 344;
                                k = ((event.mouseButton.y - y0) * 1.0) / (event.mouseButton.x - 250);

                                r = 150;

                                //The point which is finding have x and y match the linear equation above and have the length equal to the radius of the circle
                                //Therefore we have 2 equations to find the y coordinate of the point
                                // (x - x0)^2 + (y - y0)^2 = r^2
                                // y = k(x - x0) + b0
                                //After do the calculation, I come up with the equation to find y
                                // ay^2 + by + c = 0
                                //While a = 1
                                // b = -2y0
                                // c = (r^2) / (1/(k^2) + 1 )

                                //Calculate b,c
                                b = (-2) * y0;
                                c = y0 * y0 - (r * r) / ((1 / (k * k)) + 1);


                                float *roots = rootOfEquation(1, b, c);


                                float valY;
                                if (event.mouseButton.y <= 364) {
                                    valY = roots[0];
                                }
                                else {
                                    valY = roots[1];
                                }


                                if (i < gv1.insideCircle.getPointCount() - 1) {
                                    //Round the postion y to 3 decimal places
                                    float y1 = roundf(gv1.insideCircle.getPoint(i).y * 1000)/ 1000;
                                    float y2  = roundf(gv1.insideCircle.getPoint(i + 1).y * 1000)/ 1000;

                                    if (y1!=y2) {
                                        if (valY > (gv1.insideCircle.getPoint(i).y + 194) &&
                                            valY < (gv1.insideCircle.getPoint(i + 1).y + 194) &&
                                            event.mouseButton.x > 250) {
                                            gv1.position_insert = i + 1;
                                            break;
                                        }
                                        else if (valY < (gv1.insideCircle.getPoint(i).y + 194) &&
                                                 valY > (gv1.insideCircle.getPoint(i + 1).y + 194) &&
                                                 event.mouseButton.x < 250) {
                                            gv1.position_insert = i + 1;
                                            break;
                                        }
                                    }
                                    else {
                                        cout << "equal " << endl;
                                        if (event.mouseButton.x <= (gv1.insideCircle.getPoint(i).x + 80) &&
                                            event.mouseButton.x >= (gv1.insideCircle.getPoint(i + 1).x + 80)
                                            && valY >= (gv1.insideCircle.getPoint(i).y + 194)) {
                                            gv1.position_insert = i + 1;
                                            break;
                                        }
                                    }

                                }
                                else {
                                    if ((valY < (gv1.insideCircle.getPoint(i).y + 194)) &&
                                        (valY > (gv1.insideCircle.getPoint(0).y + 194)) &&
                                        event.mouseButton.x < 250) {
                                        gv1.position_insert = -1;

                                    }
                                    else {
                                        gv1.position_insert = -2;
                                    }

                                }
                            }

                            if(gv1.position_insert != -2) {
                                AtomDisplay temp{gv1.centerPoint};
                                gv1.centerPoint.setDisappear();

                                if (gv1.position_insert > -1) {
                                    gv1.atoms.insert(gv1.atoms.begin() + gv1.position_insert, temp);
                                    gm.addAtomToRing(gv1.position_insert - 1);
                                }
                                else if (gv1.position_insert == -1) {
                                    gv1.atoms.push_back(temp);
                                    gm.addAtomToRing(gm.getAtomRingSize() - 1);
                                }

                                gv1.insideCircle.setPointCount(gm.getAtomRingSize());
                                for (int i = 0; i < gv1.insideCircle.getPointCount(); i++) {
                                    if (i != gv1.position_insert) {
                                        sf::Vector2f position = gv1.insideCircle.getPoint(i);
                                        gv1.atoms[i].setPosition(position.x + 80, position.y + 194);
                                        gv1.atoms[i].draw1(window);
                                    }
                                }

                                int index = gv1.position_insert;
                                if (index == -1) {
                                    index = gv1.atoms.size() - 1;
                                }
                                gv1.atoms[index].setPosition(230, 344);
                                sf::Vector2f position = gv1.insideCircle.getPoint(index);

                                y0 = 344;
                                x0 = 80;

                                k = ((position.y + 194 - y0) * 1.0) / (position.x + 100 - 250);


                                if (event.mouseButton.x > 250) {
                                    while (gv1.atoms[index].getCirclePosition().x <= (position.x + 80)) {
                                        gv1.atoms[index].move(10, 10 * k);
                                        window.clear(sf::Color::Black);
                                        gv1.draw(window);
                                        gv2.draw(window);
                                        window.display();
                                    }
                                }
                                else {
                                    while (gv1.atoms[index].getCirclePosition().x >= (position.x + 80)) {
                                        gv1.atoms[index].move((-10), (-10) * k);
                                        window.clear(sf::Color::Black);
                                        gv1.draw(window);
                                        gv2.draw(window);
                                        window.display();
                                    }
                                }

                                gv1.atoms[index].setPosition(position.x + 80 , position.y + 194);


                                checkAtoms(window);

                                gv1.centerPoint.reset(gm.getCenterValue(1));

                                gm.send_normal(gv1.position_insert);
                                cout << "center value: " << gv1.centerPoint.getValue() << endl;

                            }
                            if (gv1.atoms.size() == 24 || gv2.atoms.size() == 24)  {
                                GameOverView gov{1001,769,gm.getScore(1),2};
                                if (gv1.atoms.size() == 24){
                                    gov.setGameState(0);
                                }
                                else{
                                    gov.setGameState(1);
                                }
                                GameOverController goc{gov};
                                return goc.Run(window);
                            }
                            cout << "done" << endl;
                        }
                    }
                    else if (gv1.centerPoint.getValue() == -1) {
                        cout << "minus" <<endl;
                        for (int i = 0; i < gv1.insideCircle.getPointCount(); i++) {
                            if (std::pow((event.mouseButton.x -
                                          (gv1.atoms[i].getCirclePosition().x + gv1.atoms[i].getCircleRadius())), 2) +
                                std::pow((event.mouseButton.y -
                                          (gv1.atoms[i].getCirclePosition().y + gv1.atoms[i].getCircleRadius())),
                                         2) <=
                                std::pow(gv1.atoms[i].getCircleRadius(), 2)) {
                                gm.deleteAtom(i);
                                cout << "delete index: " << i << endl;
                                gv1.atoms.pop_back();
                                gv1.setValueForAtoms(gm,1);
                                gv1.numPoints = gm.getAtomRingSize();
                                //gv.centerPoint.reset(gm.getCenterValue());

                                gv1.insideCircle.setPointCount(gv1.numPoints);
                                for (int i = 0; i < gv1.insideCircle.getPointCount(); i++) {
                                    sf::Vector2f position = gv1.insideCircle.getPoint(i);
                                    gv1.atoms[i].setPosition(position.x + 80, position.y + 194);

                                }
                                checkAtoms(window);
                                gv1.centerPoint.reset(gm.getCenterValue(1));
                                gm.send_minus(i);
                                break;
                            }
                        }

                    }
                    else {
                            cout << "wrong" << endl;
                        }
                    }


                }
            }

            window.clear(sf::Color::Black);
            gv1.draw(window);
            gv2.draw(window);
            window.display();
        }

        return -1;


}


#endif //ATOMAS_GAMEMULTICONTROLLER_H
