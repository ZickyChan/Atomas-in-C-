//
// Created by bit on 1/9/16.
//

#ifndef ATOMAS_GAMEMULTIVIEW_H
#define ATOMAS_GAMEMULTIVIEW_H

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include "AtomDisplay.h"
#include "../model/GameMultiModel.h"

using namespace std;
class GameMultiView{
public:
    GameMultiView(int numP, int valCenter, int offsetX, float atomRadius,float outRadius, float inRadius):numPoints{numP}, offsetX{offsetX}, centerPoint{valCenter,atomRadius},outsideCircle(outRadius),insideCircle(inRadius){
        scoreText.setString("0");
    }

    GameMultiView(GameMultiView &gv):centerPoint{gv.centerPoint}{
        numPoints = gv.numPoints;
        atoms = gv.atoms;
        outsideCircle = gv.outsideCircle;
        insideCircle = gv.insideCircle;
        scoreText = gv.scoreText;
        offsetX = gv.offsetX;
    }

    void setPosition(){
        setUpScoreText();

        cout << "score text X: " << scoreText.getPosition().x << " Y: "  << scoreText.getPosition().y << endl;

        //Set the format and position for outside circle
        outsideCircle.setFillColor(sf::Color::Transparent);
        outsideCircle.setOutlineThickness(1);
        outsideCircle.setOutlineColor(sf::Color(250, 150, 100));
        outsideCircle.setPosition(70 + offsetX,184);
        cout << "blah" << endl;
        //Set the format and position for inside circle
        insideCircle.setFillColor(sf::Color::Transparent);
        insideCircle.setPosition(100 + offsetX,194);
        insideCircle.setPointCount(numPoints);

        //Set position for the center point
        centerPoint.setPosition(230 + offsetX,344);

        //Set position for each atom
        for (int i=0;i<insideCircle.getPointCount();i++){
            sf::Vector2f position = insideCircle.getPoint(i);
            atoms[i].setPosition(position.x+80+offsetX,position.y+194);
            atoms[i].setColor();
        }

    }

    void addAtomDisplay(Atomas &a){
        cout << atoms.size();
        Atom *atom = a.getRing().get_atom_pointer(0);
        if(atoms.size() == 0) {
            for (int i = 0; i < a.getRingSize(); i++) {
                AtomDisplay shape{atom->atom, 20};
                atoms.push_back(shape);
                //cout << a.get_index_atom(i)->atom << " ";
                atom = atom->next;
            }
            cout << endl;
            //gm.Print();
        }
    }

    void draw(sf::RenderWindow &window){

        window.draw(outsideCircle);
        window.draw(scoreText);
        centerPoint.draw1(window);

        for (int i = 0; i < atoms.size(); i++) {
            atoms[i].draw1(window);

        }


    }

    void setValueForAtoms(GameMultiModel &gm, int mode){
        if(mode == 1) {
            for (int i = 0; i < gm.getAtomRingSize(); i++) {
                atoms[i].reset(gm.getAtomValue(i));
                cout << "each value of ring 1 : " << gm.getAtomValue(i) << endl;
            }
        }
        else{
            for (int i = 0; i < gm.getAtomRing2Size(); i++) {
                atoms[i].reset(gm.getAtomValue2(i));
                cout << "each value of ring 2 : " << gm.getAtomValue2(i) << endl;
            }
        }
    }


    void setValueForScoreText(int val){
        scoreText.setString(std::to_string(val));
    }

    void setUpScoreText(){
        font1.loadFromFile("libelsuit.ttf");

        scoreText.setFont(font1);
        scoreText.setCharacterSize(60);
        scoreText.setColor(sf::Color::White);


        //center text
        sf::FloatRect textRect = scoreText.getLocalBounds();
        scoreText.setOrigin(textRect.left + textRect.width/2.0f,
                            textRect.top  + textRect.height/2.0f);
        scoreText.setPosition(sf::Vector2f(500/2.0f + offsetX,50));
    }

    int numPoints;
    int position_insert;
    int offsetX;
    vector <AtomDisplay> atoms;
    AtomDisplay centerPoint;
    sf::Font font1;
    sf::Text scoreText;
    sf::CircleShape outsideCircle;
    sf::CircleShape insideCircle;
};


#endif //ATOMAS_GAMEMULTIVIEW_H
