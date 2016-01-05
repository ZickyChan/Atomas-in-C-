//
// Created by bit on 1/4/16.
//

#ifndef ATOMAS_GAMESCREEN_H
#define ATOMAS_GAMESCREEN_H

#include <iostream>
#include "Screen.h"
#include "AtomDisplay.h"

using namespace std;


//This equation is used to find the roots of the quadratic equation and return a pointer of integer results
//The equation is ax^2 + bx + c =0, type is used to identify Y or X value will be return
/*float* rootOfEquation(float a, float b, float c){
    float determinant = b*b - 4*a*c;
    float x1,x2;
    float *result = new float[2];
    //If there are 2 roots, store those in the result pointer
    if (determinant > 0) {
        x1 = (-b + sqrt(determinant)) / (2*a);
        x2 = (-b - sqrt(determinant)) / (2*a);
        cout << "x1: " << x1 << " x2: "<<x2<<endl;
        if( x1 < x2) {
            result[0] = x1;
            result[1] = x2;
        }
        else{
            result[1] = x1;
            result[0] = x2;
        }
    }
        //If there is only one root, the root will be store at the place of the pointer point to
    else if (determinant == 0) {
        x1 = ((-b + sqrt(determinant)) / (2*a));
        result[0] = x1;
        result[1] = -1000;
    }
    return result;
} */


class GameScreen: public Screen{
public:
    GameScreen():numPoints{2},min{1},max{3},randNum{rand()%(max-min + 1) + min},centerPoint{randNum,20},outsideCircle(180),insideCircle(150){    }
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

                            //Calculate the position of the point that is on the circle the content the Y Position of the atoms have x coordinate equals to event mouse button x
                            //First have to find the general equation y = k(x - x0) + b0 which content the center point of insideCircle and the event mouse button position
                            float y0 = 344;
                            float k = ((event.mouseButton.y - y0) * 1.0) / (event.mouseButton.x - 500);



                            float r = 150;
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
                            float b = (-2)*y0;
                            float c = y0*y0 - (r*r)/((1/(k*k)) + 1);

                            cout << " b: " << b << " c: " << c << endl;

                            float *roots;// = rootOfEquation(1,b,c);

                            cout << "root: " <<roots[0] << " root 1: " << roots[1] << endl;

                            float valY;
                            if(event.mouseButton.y<=364){
                                valY = roots[0];
                            }
                            else{
                                valY = roots[1];
                            }


                            if (i < insideCircle.getPointCount() - 1) {
                                cout << "mouse x: " << event.mouseButton.x << " mouse y: " << event.mouseButton.y <<
                                endl;

                                cout <<"valY is: " << valY;
                                cout << "point i x is: " << insideCircle.getPoint(i).x << "      point i y is: " <<
                                insideCircle.getPoint(i).y + 194 << endl;
                                cout << "point i + 1 x is: " << insideCircle.getPoint(i + 1).x <<
                                "   point i +1  y is: " << insideCircle.getPoint(i + 1).y + 194 << endl << endl;

//                                if (event.mouseButton.x != insideCircle.getPoint(i).x &&
//                                    event.mouseButton.x != insideCircle.getPoint(i + 1).x &&
//                                    event.mouseButton.y != insideCircle.getPoint(i).y &&
//                                    event.mouseButton.y != insideCircle.getPoint(i + 1).y) {
//
//                                    if (insideCircle.getPoint(i).y != insideCircle.getPoint(i + 1).y) {
//                                        if (event.mouseButton.y >= (insideCircle.getPoint(i).y + 194) &&
//                                            event.mouseButton.y <= (insideCircle.getPoint(i + 1).y + 194) &&
//                                            event.mouseButton.x > 500) {
//                                            position_insert = i + 1;
//                                            break;
//
//                                        }
//                                        else if (event.mouseButton.y <= (insideCircle.getPoint(i).y + 194) &&
//                                                 event.mouseButton.y >= (insideCircle.getPoint(i + 1).y + 194) &&
//                                                 event.mouseButton.x < 500) {
//                                            cout << "what's up?" << endl;
//                                            position_insert = i + 1;
//                                            break;
//
//                                        }
//                                    }
//                                    else {
//                                        if (event.mouseButton.x <= (insideCircle.getPoint(i).x + 330) &&
//                                            event.mouseButton.x >= (insideCircle.getPoint(i + 1).x + 330)
//                                            && event.mouseButton.y >= (insideCircle.getPoint(i).y + 194)) {
//                                            cout << "equal" << endl;
//                                            position_insert = i + 1;
//                                            break;
//
//                                        }
//                                    }
//                                }


                                if (insideCircle.getPoint(i).y != insideCircle.getPoint(i + 1).y) {
                                    if (valY > (insideCircle.getPoint(i).y + 194) &&
                                        valY < (insideCircle.getPoint(i + 1).y + 194) &&
                                        event.mouseButton.x > 500) {
                                        position_insert = i + 1;
                                        break;
                                    }
                                    else if (valY < (insideCircle.getPoint(i).y + 194) &&
                                            valY > (insideCircle.getPoint(i + 1).y + 194) &&
                                             event.mouseButton.x < 500) {
                                        cout << "what's up?" << endl;
                                        position_insert = i + 1;
                                        break;
                                    }
                                }
                                else {
                                    if (event.mouseButton.x <= (insideCircle.getPoint(i).x + 330) &&
                                        event.mouseButton.x >= (insideCircle.getPoint(i + 1).x + 330)
                                        && valY >= (insideCircle.getPoint(i).y + 194)) {
                                        cout << "equal" << endl;
                                        position_insert = i + 1;
                                        break;
                                    }
                                }

                            }
                            else {
                                cout << "in here" << endl;
//                                if ((event.mouseButton.y < (insideCircle.getPoint(i).y + 194)) &&
//                                    (event.mouseButton.y > (insideCircle.getPoint(0).y + 194)) &&
//                                    event.mouseButton.x < 500) {
//                                    position_insert = -1;
//
//                                }
                                if ((valY < (insideCircle.getPoint(i).y + 194)) &&
                                    (valY > (insideCircle.getPoint(0).y + 194)) &&
                                    event.mouseButton.x < 500) {
                                    position_insert = -1;

                                }
                                else{
                                    position_insert = -2;
                                }

                            }
                        }
                        randNum = rand() % (max - min + 1) + min;
                        AtomDisplay temp{centerPoint};
                        centerPoint.reset(randNum);

                        if (position_insert > -1) {
                            atoms.insert(atoms.begin() + position_insert, temp);
                        }
                        else if(position_insert == -1){
                            atoms.push_back(temp);
                        }
                        insideCircle.setPointCount(numPoints);
                        cout << numPoints << " and position " << position_insert << endl;
                        for (int i = 0; i < insideCircle.getPointCount(); i++) {
                            sf::Vector2f position = insideCircle.getPoint(i);
                            atoms[i].setPosition(position.x + 330, position.y + 194);
                            atoms[i].draw1(window);
                        }
                        cout << "position " << position_insert;
                    }
                    else {
                        cout << "wrong" << endl;
                    }

                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(outsideCircle);
        //window.draw(abc);
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
