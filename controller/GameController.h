//
// Created by bit on 1/5/16.
//

#ifndef ATOMAS_GAMECONTROLLER_H
#define ATOMAS_GAMECONTROLLER_H
#define PI 3.14159265

#include "../model/GameModel.h"
#include "../view/GameView.h"
#include "Controller.h"
#include "../view/GameOverView.h"
#include "GameOverController.h"
#include "../game/Atomas.h"

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

//This function is used to calculate the angle between the 2 atoms
//a1 and a2 represent the atoms that is going to be found the angle
//radius is the radius of the circle that both atoms are placed on
float calculateAngle(AtomDisplay &a1, AtomDisplay &a2,int radius){

    //x1,y1 is the top point of the atom a1
    float x1 = a1.getCirclePosition().x + 330 + a1.getCircleRadius();
    float y1 = a1.getCirclePosition().y + 194;

    //x2,y2 is the top point of the atom a2
    float x2 = a2.getCirclePosition().x + 330 + a2.getCircleRadius();
    float y2 = a2.getCirclePosition().y + 194;

    //Find the distance between 2 top points
    float length = sqrt(pow(x2-x1,2) + pow(y2-y1,2));

    //Calculate and return the angle
    return (asin (length/(2*radius)) * 180.0 / PI);

}

class GameController:public Controller{
public:
    GameController(GameView &gameView, GameModel &gameModel):gv{gameView}, gm{gameModel}{

    }

    //This function is used to check if there is a PROTON in the ring
    //If there is a PROTON, check if there is any combos
    //If there are combos, do the animation
    void checkAtoms(sf::RenderWindow &window){
        int index = 0;
        int combo = 0;
        //Loop the ring, find the position of the PROTON
        while (index < gm.getRing().get_size()) {
            if (gm.getRing().get_atom(index) == PROTON) {
                //Get how many combo can be made from the PROTON
                combo = gm.check_proton(index);
                
                //If there is a combo, do the animation
                if (combo > 0) {
                    sf::Transform t1;
                    sf::Transform t2;
                    for (int i = 1; i <= (combo); i++) {

                        //Calculate the angle to rotate
                        float angle = calculateAngle(gv.atoms[(index + i) % gv.atoms.size()], gv.atoms[index], 150);

                        //step is used to set how many time do the transform
                        int step = 0;
                        while (true) {
                            if (angle <= step) {
                                break;
                            }

                            window.clear(sf::Color::Black);
                            //t1 transform is used for the atom to the left of the PROTON
                            t1.rotate(2.0, {500, 364});
                            //t2 transform is used for the atom to the right of the PROTON
                            t2.rotate(-2.0, {500, 364});

                            //gv.atoms[(index - i + gv.atoms.size())%gv.atoms.size()].ro
                            if ((gv.atoms[index].getCirclePosition().y + 194) > 344) {
                                gv.atoms[(index + i) % gv.atoms.size()].draw(window, t2);
                                gv.atoms[(index - i + gv.atoms.size()) % gv.atoms.size()].draw(window, t1);
                            }
                            else {
                                gv.atoms[(index + i) % gv.atoms.size()].draw(window, t1);
                                gv.atoms[(index - i + gv.atoms.size()) % gv.atoms.size()].draw(window, t2);
                            }
                            window.draw(gv.outsideCircle);
                            window.draw(gv.scoreText);
                            gv.centerPoint.draw1(window);
                            for (int j = 0; j < gv.atoms.size(); j++) {
                                if (j != ((index + i) % gv.atoms.size()) &&
                                    j != (index - i + gv.atoms.size()) % gv.atoms.size()) {
                                    gv.atoms[j].draw1(window);
                                }


                            }

                            window.display();
                            step += i + 1;
                        }
                        gv.setValueForScoreText(gm.getScore());
                        gv.atoms[(index + i) % gv.atoms.size()].setPosition(gv.atoms[index].getCirclePosition().x,
                                                                            gv.atoms[index].getCirclePosition().y);
                        gv.atoms[(index - i + gv.atoms.size()) % gv.atoms.size()].setPosition(
                                gv.atoms[index].getCirclePosition().x, gv.atoms[index].getCirclePosition().y);
                        window.clear(sf::Color::Black);
                        window.draw(gv.outsideCircle);
                        window.draw(gv.scoreText);
                        gv.centerPoint.draw1(window);

                        for (int i = 0; i < gv.atoms.size(); i++) {

                            gv.atoms[i].draw1(window);


                        }

                        window.display();


                    }

                    //After finish the animation, reduce the size of the atoms ring display and draw it on screen

                    for (int i = gv.atoms.size(); i > gm.getAtomRingSize(); i--) {
                        gv.atoms.pop_back();
                    }
                    gv.insideCircle.setPointCount(gm.getAtomRingSize());
                    gv.setValueForAtoms(gm);
                    for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {
                        sf::Vector2f position = gv.insideCircle.getPoint(i);
                        gv.atoms[i].setPosition(position.x + 330, position.y + 194);
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

        //reset the center value
        gm.setNewCenterValue();
    }


    virtual int Run(sf::RenderWindow &window);
private:
    GameView gv;
    GameModel gm;
};

int GameController::Run(sf::RenderWindow &window) {
    float k,x0,y0,r,b,c;
    gv.addAtomDisplay(gm);
    gv.setPosition();
    window.clear();

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return (-1);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    //If user click inside the outSideCircle and don't click too close to the center(away from the center 50 px)
                    //And the center value must not be -1
                    //Do the animation to shoot the center value to the ring
                    //Check if there is any PROTON that could make combo
                    if (std::pow((event.mouseButton.x - 500), 2) + std::pow((event.mouseButton.y - 364), 2) <=
                        std::pow(180, 2) && std::pow((event.mouseButton.x - 500), 2) + std::pow((event.mouseButton.y - 364), 2) >
                                            std::pow(50, 2)
                            && gv.centerPoint.getValue() != (-1)
                            ) {

                        //If there is only an atom in ring
                        if (gv.insideCircle.getPointCount() == 1) {
                            AtomDisplay temp{gv.centerPoint};

                            gv.atoms.push_back(temp);
                            gm.addAtomToRing(gm.getAtomRingSize() - 1);


                            gv.centerPoint.reset(gm.getCenterValue());

                            gv.insideCircle.setPointCount(gm.getAtomRingSize());
                            for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {
                                sf::Vector2f position = gv.insideCircle.getPoint(i);
                                gv.atoms[i].setPosition(position.x + 330, position.y + 194);
                            }

                        }
                        else {
                            for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {

                                //Calculate the position of the point that is on the circle the content the Y Position of the atoms have x coordinate equals to event mouse button x
                                //First have to find the general equation y = k(x - x0) + b0 which content the center point of insideCircle and the event mouse button position
                                y0 = 344;
                                k = ((event.mouseButton.y - y0) * 1.0) / (event.mouseButton.x - 500);

                                r = 150;

                                /* The point which is finding have x and y match the linear equation above and have the length equal to the radius of the circle
                                 * Therefore we have 2 equations to find the y coordinate of the point
                                 * (x - x0)^2 + (y - y0)^2 = r^2
                                 * y = k(x - x0) + b0
                                 * After do the calculation, I come up with the equation to find y
                                 * ay^2 + by + c = 0
                                 * While a = 1
                                 * b = -2y0
                                 * c = (r^2) / (1/(k^2) + 1 )
                                 * Calculate b,c
                                 */
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

                                //Find the position to insert the center atom to atoms ring base on the event moue click
                                if (i < gv.insideCircle.getPointCount() - 1) {
                                    float y1 = roundf(gv.insideCircle.getPoint(i).y * 1000)/ 1000;
                                    float y2  = roundf(gv.insideCircle.getPoint(i + 1).y * 1000)/ 1000;

                                    if (y1!=y2) {
                                        if (valY > (gv.insideCircle.getPoint(i).y + 194) &&
                                            valY < (gv.insideCircle.getPoint(i + 1).y + 194) &&
                                            event.mouseButton.x > 500) {
                                            gv.position_insert = i + 1;
                                            break;
                                        }
                                        else if (valY < (gv.insideCircle.getPoint(i).y + 194) &&
                                                 valY > (gv.insideCircle.getPoint(i + 1).y + 194) &&
                                                 event.mouseButton.x < 500) {
                                            gv.position_insert = i + 1;
                                            break;
                                        }
                                    }
                                    else {
                                        if (event.mouseButton.x <= (gv.insideCircle.getPoint(i).x + 330) &&
                                            event.mouseButton.x >= (gv.insideCircle.getPoint(i + 1).x + 330)
                                            && valY >= (gv.insideCircle.getPoint(i).y + 194)) {
                                            gv.position_insert = i + 1;
                                            break;
                                        }
                                    }

                                }
                                else {
                                    if ((valY < (gv.insideCircle.getPoint(i).y + 194)) &&
                                        (valY > (gv.insideCircle.getPoint(0).y + 194)) &&
                                        event.mouseButton.x < 500) {
                                        gv.position_insert = -1;

                                    }
                                        //If the place that user clicked is not in between any 2 atoms that are side by side, position insert will be -2
                                    else {
                                        gv.position_insert = -2;
                                    }

                                }
                            }

                            //If the center atom could be inserted in the ring
                            //Then add into the atomas ring
                            //Display the animation
                            if(gv.position_insert != -2) {
                            AtomDisplay temp{gv.centerPoint};
                            gv.centerPoint.setDisappear();

                            if (gv.position_insert > -1) {
                                gv.atoms.insert(gv.atoms.begin() + gv.position_insert, temp);
                                gm.addAtomToRing(gv.position_insert - 1);
                            }
                            else if (gv.position_insert == -1) {
                                gv.atoms.push_back(temp);
                                gm.addAtomToRing(gm.getAtomRingSize() - 1);
                            }

                            gv.insideCircle.setPointCount(gm.getAtomRingSize());
                            for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {
                                if (i != gv.position_insert) {
                                    sf::Vector2f position = gv.insideCircle.getPoint(i);
                                    gv.atoms[i].setPosition(position.x + 330, position.y + 194);
                                    gv.atoms[i].draw1(window);
                                }
                            }

                            int index = gv.position_insert;
                            if (index == -1) {
                                index = gv.atoms.size() - 1;
                            }
                            gv.atoms[index].setPosition(480, 344);
                            sf::Vector2f position = gv.insideCircle.getPoint(index);

                            y0 = 344;
                            x0 = 480;

                            k = ((position.y + 194 - y0) * 1.0) / (position.x + 350 - 500);


                            if (event.mouseButton.x > 500) {
                                while (gv.atoms[index].getCirclePosition().x <= (position.x + 330)) {
                                    gv.atoms[index].move(10, 10 * k);
                                    window.clear(sf::Color::Black);
                                    window.draw(gv.outsideCircle);
                                    window.draw(gv.scoreText);
                                    gv.centerPoint.draw1(window);
                                    for (int i = 0; i < gv.atoms.size(); i++) {

                                        gv.atoms[i].draw1(window);


                                    }
                                    window.display();
                                }
                            }
                            else {
                                while (gv.atoms[index].getCirclePosition().x >= (position.x + 330)) {
                                    gv.atoms[index].move((-10), (-10) * k);
                                    window.clear(sf::Color::Black);
                                    window.draw(gv.outsideCircle);
                                    window.draw(gv.scoreText);
                                    gv.centerPoint.draw1(window);
                                    for (int i = 0; i < gv.atoms.size(); i++) {

                                        gv.atoms[i].draw1(window);


                                    }
                                    window.display();
                                }
                            }

                            gv.atoms[index].setPosition(position.x + 330, position.y + 194);

                            checkAtoms(window);

                                gv.centerPoint.reset(gm.getCenterValue());
                            }

                            //If the ring reached the size of 24 atoms, game will end
                            if (gv.atoms.size() == 24) {
                                GameOverView gov{1001,769,gm.getScore(),1};
                                GameOverController goc{gov};
                                gm.restart();
                                gv.restart(gm);
                                return goc.Run(window);
                            }
                            cout << "done" << endl;
                            gm.Print();
                        }
                    }

                        //If the center Atom is -1
                    else if (gv.centerPoint.getValue() == -1) {
                        for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {

                            /* Check if user clicked into any atoms of the ring
                             * Delete that atom with the index i
                             * Reduce the atom display size by 1
                             * Check if there is any combos can be made
                             * Draw the ring again
                             */
                            if (std::pow((event.mouseButton.x -
                                              (gv.atoms[i].getCirclePosition().x + gv.atoms[i].getCircleRadius())), 2) +
                                    std::pow((event.mouseButton.y -
                                              (gv.atoms[i].getCirclePosition().y + gv.atoms[i].getCircleRadius())),
                                             2) <=
                                    std::pow(gv.atoms[i].getCircleRadius(), 2)) {
                                    gm.deleteAtom(i);
                                    gv.atoms.pop_back();
                                    gv.setValueForAtoms(gm);
                                    gv.numPoints = gm.getAtomRingSize();

                                    gv.insideCircle.setPointCount(gv.numPoints);
                                    for (int i = 0; i < gv.insideCircle.getPointCount(); i++) {
                                        sf::Vector2f position = gv.insideCircle.getPoint(i);
                                        gv.atoms[i].setPosition(position.x + 330, position.y + 194);

                                    }
                                    checkAtoms(window);
                                    gv.centerPoint.reset(gm.getCenterValue());
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
        window.draw(gv.outsideCircle);
        window.draw(gv.scoreText);
        gv.centerPoint.draw1(window);
        for (int i = 0; i < gv.atoms.size(); i++) {

            gv.atoms[i].draw1(window);


        }

        window.display();
    }

    return -1;

}



#endif //ATOMAS_GAMECONTROLLER_H
