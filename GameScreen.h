//
// Created by bit on 1/4/16.
//

#ifndef ATOMAS_GAMESCREEN_H
#define ATOMAS_GAMESCREEN_H

#include <iostream>
#include "Screen.h"
#include "AtomDisplay.h"

using namespace std;
class GameScreen: public Screen{
public:
    GameScreen():numPoints{2},min{1},max{3},randNum{rand()%(max-min + 1) + min},centerPoint{randNum},outsideCircle(180),insideCircle(150){    }
    virtual int Run(sf::RenderWindow &window);

private:
    int numPoints;
    int max;
    int min;
    int randNum;
    int position_insert;
    vector <AtomDisplay> atoms;
    AtomDisplay centerPoint;
    sf::CircleShape outsideCircle;
    sf::CircleShape insideCircle;
};

int GameScreen::Run(sf::RenderWindow &window) {
    //Set the format and position for outside circle
    outsideCircle.setFillColor(sf::Color::Transparent);
    outsideCircle.setOutlineThickness(1);
    outsideCircle.setOutlineColor(sf::Color(250, 150, 100));
    outsideCircle.setPosition(320,184);

    //Set the format and position for inside circle
    insideCircle.setFillColor(sf::Color::Transparent);
    insideCircle.setPosition(350,214);
    insideCircle.setPointCount(numPoints);

    //Set position for the center point
    centerPoint.setPosition(480,344);

    cout << "points: "<<insideCircle.getPointCount() << endl;

    //Add number of elements into the vecor
    for (int i=0;i<insideCircle.getPointCount();i++){
        randNum = rand()%(max-min + 1) + min;
        AtomDisplay shape{randNum};
        atoms.push_back(shape);
    }

    //Set position for each atom
    for (int i=0;i<insideCircle.getPointCount();i++){
        sf::Vector2f position = insideCircle.getPoint(i);
        atoms[i].setPosition(position.x+330,position.y+194);
        atoms[i].setColor();
    }





    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return (-1);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cout << event.mouseButton.x << " and " << event.mouseButton.y << endl;
                    if (std::pow((event.mouseButton.x - 500), 2) + std::pow((event.mouseButton.y - 364), 2) <=
                        std::pow(180, 2)) {
                        numPoints++;
                        //ring2.setPointCount(3);

                        for (int i = 0; i < insideCircle.getPointCount(); i++) {


                            if (i < insideCircle.getPointCount() - 1) {
                                cout << "mouse x: " << event.mouseButton.x << " mouse y: " << event.mouseButton.y <<
                                endl;
                                cout << "point i x is: " << insideCircle.getPoint(i).x << "      point i y is: " <<
                                insideCircle.getPoint(i).y + 194 << endl;
                                cout << "point i + 1 x is: " << insideCircle.getPoint(i + 1).x <<
                                "   point i +1  y is: " << insideCircle.getPoint(i + 1).y + 194 << endl << endl;

                                if (event.mouseButton.x != insideCircle.getPoint(i).x &&
                                    event.mouseButton.x != insideCircle.getPoint(i + 1).x &&
                                    event.mouseButton.y != insideCircle.getPoint(i).y &&
                                    event.mouseButton.y != insideCircle.getPoint(i + 1).y) {

                                    if (insideCircle.getPoint(i).y != insideCircle.getPoint(i + 1).y) {
                                        if (event.mouseButton.y >= (insideCircle.getPoint(i).y + 194) &&
                                            event.mouseButton.y <= (insideCircle.getPoint(i + 1).y + 194) &&
                                            event.mouseButton.x > 500) {
                                            position_insert = i + 1;
                                            break;

                                        }
                                        else if (event.mouseButton.y <= (insideCircle.getPoint(i).y + 194) &&
                                                 event.mouseButton.y >= (insideCircle.getPoint(i + 1).y + 194) &&
                                                 event.mouseButton.x < 500) {
                                            cout << "what's up?" << endl;
                                            position_insert = i + 1;
                                            break;

                                        }
                                    }
                                    else {
                                        if (event.mouseButton.x <= (insideCircle.getPoint(i).x + 330) &&
                                            event.mouseButton.x >= (insideCircle.getPoint(i + 1).x + 330)
                                            && event.mouseButton.y >= (insideCircle.getPoint(i).y + 194)) {
                                            cout << "equal" << endl;
                                            position_insert = i + 1;
                                            break;

                                        }
                                    }
                                }
                            }
                            else {
                                cout << "in here" << endl;
                                if ((event.mouseButton.y < (insideCircle.getPoint(i).y + 194)) &&
                                    (event.mouseButton.y > (insideCircle.getPoint(0).y + 194)) &&
                                    event.mouseButton.x < 500) {
                                    position_insert = -1;

                                }

                            }
                        }
                        randNum = rand() % (max - min + 1) + min;
                        AtomDisplay temp{centerPoint};
                        centerPoint.reset(randNum);

                        if (position_insert != -1) {
                            atoms.insert(atoms.begin() + position_insert, temp);
                        }
                        else {
                            atoms.push_back(temp);
                        }
                        insideCircle.setPointCount(numPoints);
                        cout << numPoints << " and position " << position_insert << endl;
                        for (int i = 0; i < insideCircle.getPointCount(); i++) {
                            sf::Vector2f position = insideCircle.getPoint(i);
                            atoms[i].setPosition(position.x + 330, position.y + 194);
                        }
                    }
                    else {
                        cout << "wrong" << endl;
                    }

                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(outsideCircle);
       // window.draw(insideCircle);
        centerPoint.draw1(window);
        //centerPoint.draw1(window);
        for (int i = 0; i < atoms.size(); i++) {

            atoms[i].draw1(window);


        }

        window.display();
    }

    return -1;

}

#endif //ATOMAS_GAMESCREEN_H
