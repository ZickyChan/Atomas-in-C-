//
// Created by bit on 1/5/16.
//

#ifndef ATOMAS_GAMEVIEW_H
#define ATOMAS_GAMEVIEW_H
#include <iostream>
#include "AtomDisplay.h"

using namespace std;
class GameView{
public:
    GameView(int numP, int minVal, int maxVal, float atomRadius,float outRadius, float inRadius):numPoints{numP},min{minVal},max{maxVal},randNum{rand()%(max-min + 1) + min}
            ,centerPoint{randNum,atomRadius},outsideCircle(outRadius),insideCircle(inRadius){    }

    GameView(GameView &gv):centerPoint{gv.centerPoint}{
        numPoints = gv.numPoints;
        max = gv.max;
        min = gv.min;
        randNum = gv.randNum;
        atoms = gv.atoms;
        outsideCircle = gv.outsideCircle;
        insideCircle = gv.insideCircle;
    }

    void setPosition(){
        //Set the format and position for outside circle
        outsideCircle.setFillColor(sf::Color::Transparent);
        outsideCircle.setOutlineThickness(1);
        outsideCircle.setOutlineColor(sf::Color(250, 150, 100));
        outsideCircle.setPosition(320,184);

        //Set the format and position for inside circle
        insideCircle.setFillColor(sf::Color::Transparent);
        insideCircle.setPosition(350,214);
        insideCircle.setPointCount(numPoints);

        sf::CircleShape abc{150};
        abc.setOutlineThickness(1);
        abc.setOutlineColor(sf::Color(250, 150, 100));
        abc.setFillColor(sf::Color::Transparent);
        abc.setPosition(350,194);

        //Set position for the center point
        centerPoint.setPosition(480,344);

        cout << "points: "<<insideCircle.getPointCount() << endl;

        //Add number of elements into the vecor
        for (int i=0;i<insideCircle.getPointCount();i++){
            randNum = rand()%(max-min + 1) + min;
            AtomDisplay shape{randNum,20};
            atoms.push_back(shape);
        }

        //Set position for each atom
        for (int i=0;i<insideCircle.getPointCount();i++){
            sf::Vector2f position = insideCircle.getPoint(i);
            atoms[i].setPosition(position.x+330,position.y+194);
            atoms[i].setColor();
        }

    }

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

#endif //ATOMAS_GAMEVIEW_H
