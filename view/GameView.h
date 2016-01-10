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
            centerPoint{valCenter,atomRadius},outsideCircle(outRadius),insideCircle(inRadius){
        scoreText.setString("0");
    }

    GameView(GameView &gv):centerPoint{gv.centerPoint}{
        numPoints = gv.numPoints;
        atoms = gv.atoms;
        outsideCircle = gv.outsideCircle;
        insideCircle = gv.insideCircle;
        scoreText = gv.scoreText;
    }

    /*This function is used to set the position for every components of the view */
    void setPosition(){
        setUpScoreText();

        cout << "score text X: " << scoreText.getPosition().x << " Y: "  << scoreText.getPosition().y << endl;

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

        //Set position for each atom
        for (int i=0;i<insideCircle.getPointCount();i++){
            sf::Vector2f position = insideCircle.getPoint(i);
            atoms[i].setPosition(position.x+330,position.y+194);
            atoms[i].setColor();
        }

    }

    /*
     * This function is used to add the atom display when it is null
     */
    void addAtomDisplay(GameModel &gm){
        if(atoms.size() == 0) {
            for (int i = 0; i < gm.getAtomRingSize(); i++) {
                AtomDisplay shape{gm.getAtomValue(i), 20};
                atoms.push_back(shape);
            }
        }
    }

    /*Reset the value for the atom display */
    void setValueForAtoms(GameModel &gm){
        for (int i=0;i<gm.getAtomRingSize();i++) {
            atoms[i].reset(gm.getAtomValue(i));
        }
    }

    /*This function is used to reset the game */
    void restart(GameModel &gm){
        for(int i=atoms.size();i>gm.getAtomRingSize();i--) {
            atoms.pop_back();
            cout << "i is: " << i << endl;
        }
        cout << "game score: " << gm.getScore();
        scoreText.setString("0");
        scoreText.setColor(sf::Color::White);
        numPoints = gm.getAtomRingSize();
        insideCircle.setPointCount(gm.getAtomRingSize());
        setValueForAtoms(gm);
        centerPoint.reset(gm.getCenterValue());
    }

    void setValueForScoreText(int val){
        scoreText.setString(std::to_string(val));
    }

    /*Format the score text view */
    void setUpScoreText(){
        font1.loadFromFile("libelsuit.ttf");

        scoreText.setFont(font1);
        scoreText.setCharacterSize(60);
        scoreText.setColor(sf::Color::White);


        //center text
        sf::FloatRect textRect = scoreText.getLocalBounds();
        scoreText.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        scoreText.setPosition(sf::Vector2f(1001/2.0f,50));
    }

    int numPoints;
    int position_insert;
    vector <AtomDisplay> atoms;
    AtomDisplay centerPoint;
    sf::Font font1;
    sf::Text scoreText;
    sf::CircleShape outsideCircle;
    sf::CircleShape insideCircle;
};

#endif //ATOMAS_GAMEVIEW_H
