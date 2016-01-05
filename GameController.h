//
// Created by bit on 1/5/16.
//

#ifndef ATOMAS_GAMECONTROLLER_H
#define ATOMAS_GAMECONTROLLER_H

#include "GameModel.h"
#include "GameView.h"
#include "Controller.h"

//This equation is used to find the roots of the quadratic equation and return a pointer of integer results
//The equation is ax^2 + bx + c =0, type is used to identify Y or X value will be return
float* rootOfEquation(float a, float b, float c){
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
}

class GameController:public Controller{
public:
    GameController(GameView &gameView, GameModel &gameModel):gv{gameView}{ }

    virtual int Run(sf::RenderWindow &window);

private:
    GameView gv;
    GameModel gm;
};

int GameController::Run(sf::RenderWindow &window) {
    float k,x0,y0,r,b,c;
    gv.setPosition();
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
                        gv.numPoints++;


                        for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {

                            //Calculate the position of the point that is on the circle the content the Y Position of the atoms have x coordinate equals to event mouse button x
                            //First have to find the general equation y = k(x - x0) + b0 which content the center point of insideCircle and the event mouse button position
                            y0 = 344;
                            k = ((event.mouseButton.y - y0) * 1.0) / (event.mouseButton.x - 500);



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
                            b = (-2)*y0;
                            c = y0*y0 - (r*r)/((1/(k*k)) + 1);

                            cout << " b: " << b << " c: " << c << endl;

                            float *roots = rootOfEquation(1,b,c);

                            cout << "root: " <<roots[0] << " root 1: " << roots[1] << endl;

                            float valY;
                            if(event.mouseButton.y<=364){
                                valY = roots[0];
                            }
                            else{
                                valY = roots[1];
                            }


                            if (i < gv.insideCircle.getPointCount() - 1) {
                                cout << "mouse x: " << event.mouseButton.x << " mouse y: " << event.mouseButton.y <<
                                endl;

                                cout <<"valY is: " << valY;
                                cout << "point i x is: " << gv.insideCircle.getPoint(i).x << "      point i y is: " <<
                                gv.insideCircle.getPoint(i).y + 194 << endl;
                                cout << "point i + 1 x is: " << gv.insideCircle.getPoint(i + 1).x <<
                                "   point i +1  y is: " << gv.insideCircle.getPoint(i + 1).y + 194 << endl << endl;

                                if (gv.insideCircle.getPoint(i).y != gv.insideCircle.getPoint(i + 1).y) {
                                    if (valY > (gv.insideCircle.getPoint(i).y + 194) &&
                                        valY < (gv.insideCircle.getPoint(i + 1).y + 194) &&
                                        event.mouseButton.x > 500) {
                                        gv.position_insert = i + 1;
                                        break;
                                    }
                                    else if (valY < (gv.insideCircle.getPoint(i).y + 194) &&
                                             valY > (gv.insideCircle.getPoint(i + 1).y + 194) &&
                                             event.mouseButton.x < 500) {
                                        cout << "what's up?" << endl;
                                        gv.position_insert = i + 1;
                                        break;
                                    }
                                }
                                else {
                                    if (event.mouseButton.x <= (gv.insideCircle.getPoint(i).x + 330) &&
                                        event.mouseButton.x >= (gv.insideCircle.getPoint(i + 1).x + 330)
                                        && valY >= (gv.insideCircle.getPoint(i).y + 194)) {
                                        cout << "equal" << endl;
                                        gv.position_insert = i + 1;
                                        break;
                                    }
                                }

                            }
                            else {
                                cout << "in here" << endl;
                                if ((valY < (gv.insideCircle.getPoint(i).y + 194)) &&
                                    (valY > (gv.insideCircle.getPoint(0).y + 194)) &&
                                    event.mouseButton.x < 500) {
                                    gv.position_insert = -1;

                                }
                                else{
                                    gv.position_insert = -2;
                                }

                            }
                        }
                        gv.randNum = rand() % (gv.max - gv.min + 1) + gv.min;
                        AtomDisplay temp{gv.centerPoint};
                        gv.centerPoint.reset(gv.randNum);

                        if (gv.position_insert > -1) {
                            gv.atoms.insert(gv.atoms.begin() + gv.position_insert, temp);
                        }
                        else if(gv.position_insert == -1){
                            gv.atoms.push_back(temp);
                        }
                        gv.insideCircle.setPointCount(gv.numPoints);
                        cout << gv.numPoints << " and position " << gv.position_insert << endl;
                        for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {
                            if(i!=gv.position_insert) {
                                cout << "draw setting in here" << i << endl;
                                sf::Vector2f position = gv.insideCircle.getPoint(i);
                                gv.atoms[i].setPosition(position.x + 330, position.y + 194);
                                gv.atoms[i].draw1(window);
                            }
                        }
                        cout << "center x: " << gv.centerPoint.getCirclePosition().x << endl;
                        gv.atoms[gv.position_insert].setPosition(480,344);
                        sf::Vector2f position = gv.insideCircle.getPoint(gv.position_insert);

                        y0 = 344;
                        x0=480;

                        k = ((position.y + 194 - y0) * 1.0) / (position.x + 350 - 500);

                        int index = gv.position_insert;
                        if(index == -1){
                            index = gv.atoms.size()  - 1;
                        }

                        cout << "position x: " << position.x << "position y: " << position.y << endl;

                        while(gv.atoms[index].getCirclePosition().x <= (position.x + 330 )){
                            cout << "index:   " << index << endl;
                            gv.atoms[index].move(2,2*k);
                            window.clear(sf::Color::Black);
                            window.draw(gv.outsideCircle);
                            gv.centerPoint.draw1(window);
                            for (int i = 0; i < gv.atoms.size(); i++) {

                                gv.atoms[i].draw1(window);


                            }
                            window.display();
                        }

                        gv.atoms[index].setPosition(position.x + 330, position.y + 194);
                        cout << "position " << gv.position_insert;
                    }
                    else {
                        cout << "wrong" << endl;
                    }

                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(gv.outsideCircle);
        //window.draw(abc);
        // window.draw(insideCircle);
        gv.centerPoint.draw1(window);
        //centerPoint.draw1(window);
        for (int i = 0; i < gv.atoms.size(); i++) {

            gv.atoms[i].draw1(window);


        }

        window.display();
    }

    return -1;

}

#endif //ATOMAS_GAMECONTROLLER_H
