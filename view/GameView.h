//
// Created by bit on 1/5/16.
//

#ifndef ATOMAS_GAMEVIEW_H
#define ATOMAS_GAMEVIEW_H
#include <iostream>
#include "AtomDisplay.h"
#include "../model/GameModel.h"

using namespace std;
class GameView{
public:
    GameView(int valCenter, int numP, float atomRadius,float outRadius, float inRadius):numPoints{numP},
            centerPoint{valCenter,atomRadius},outsideCircle(outRadius),insideCircle(inRadius){    }

    GameView(GameView &gv):centerPoint{gv.centerPoint}{
        numPoints = gv.numPoints;
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

//        //Add number of elements into the vecor
//        for (int i=0;i<insideCircle.getPointCount();i++){
//            AtomDisplay shape{atomVal,20};
//            atoms.push_back(shape);
//        }

        //Set position for each atom
        for (int i=0;i<insideCircle.getPointCount();i++){
            sf::Vector2f position = insideCircle.getPoint(i);
            atoms[i].setPosition(position.x+330,position.y+194);
            atoms[i].setColor();
        }

    }

    void addAtomDisplay(GameModel &gm){
        cout << atoms.size();
        if(atoms.size() == 0) {
            for (int i = 0; i < gm.getAtomRingSize(); i++) {
                AtomDisplay shape{gm.getAtomValue(i), 20};
                atoms.push_back(shape);
                cout << gm.getAtomValue(i) << " ";
            }
            cout << endl;
            gm.Print();
        }
    }

    void setValueForAtoms(GameModel &gm){
        for (int i=0;i<gm.getAtomRingSize();i++) {
            atoms[i].reset(gm.getAtomValue(i));
        }
    }

    void restart(GameModel &gm){
        for(int i=atoms.size();i>gm.getAtomRingSize();i--) {
            atoms.pop_back();
            cout << "i is: " << i << endl;
        }
        numPoints = gm.getAtomRingSize();
        insideCircle.setPointCount(gm.getAtomRingSize());
        setValueForAtoms(gm);
        centerPoint.reset(gm.getCenterValue());
        cout << "atom size: " << atoms.size();
    }

    int numPoints;
    int position_insert;
    vector <AtomDisplay> atoms;
    AtomDisplay centerPoint;
    sf::CircleShape outsideCircle;
    sf::CircleShape insideCircle;
};

#endif //ATOMAS_GAMEVIEW_H
