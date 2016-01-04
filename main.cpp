//#include <iostream>
//#include <SFML>
//#include "AtomRing.h"
//
//using namespace std;
//
//int main() {
//    AtomRing ring = AtomRing();
//
//    ring.addAtom(2);
//    ring.addAtom(1);
//    ring.addAtom(1);
//    ring.addAtom(1);
//    ring.addAtom(1);
//    ring.addAtom(1);
//
//    ring.addAtom(2);
//
//    ring.addAtom(-2);
//
//    ring.processPlus();
//
//    Atom *atom = ring.getAtom();
//
//
//
//    cout << atom->index ;
//
//    return 0;
//}

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "AtomDisplay.h"
#include "GameScreen.h"

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(1001, 769), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    GameScreen game;
    int running = 0;
    while (running >=0) {
        game.Run(window);
    }
    return 0;
}



//
//    int numPoints = 2;
//    int position_insert;
//
//    int min = 1;
//    int max = 3;
//    int randNum = rand() % (max - min + 1) + min;
//
//    vector<AtomDisplay> shapes;
//
//    sf::RenderWindow window(sf::VideoMode(1001, 769), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
//    sf::CircleShape ring(180);
//    ring.setFillColor(sf::Color::Transparent);
//    // set a 10-pixel wide orange outline
//    ring.setOutlineThickness(1);
//    ring.setOutlineColor(sf::Color(250, 150, 100));
//    ring.setPosition(320, 184);
//
//
//    sf::CircleShape ring2(150);
//    ring2.setFillColor(sf::Color::Transparent);
//    ring2.setPosition(350, 214);
//    ring2.setPointCount(numPoints);
//
//
//    sf::CircleShape ring3(170);
//    ring3.setFillColor(sf::Color::Transparent);
//    ring3.setPosition(330, 194);
//    ring3.setOutlineColor(sf::Color::White);
//    ring3.setOutlineThickness(2);
//
//    sf::Transform t;
//
//    sf::CircleShape node{20};
//    node.setPosition(480, 344);
//    node.setFillColor(sf::Color::Yellow);
//
//    sf::Text try1;
//    try1.setColor(sf::Color::White);
//    try1.setCharacterSize(8);
//    try1.setString("abc");
//
//
//    for (int i = 0; i < ring2.getPointCount(); i++) {
//        AtomDisplay shape{1};
//        sf::Vector2f position = ring2.getPoint(i);
//        shape.setPosition(position.x + 330, position.y + 194);
//        //shape.setOrigin({150,150});
//        shapes.push_back(shape);
//    }
//
//
//    while (window.isOpen()) {
//        sf::Event event;
//
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    cout << event.mouseButton.x << " and " << event.mouseButton.y << endl;
//                    if (std::pow((event.mouseButton.x - 500), 2) + std::pow((event.mouseButton.y - 364), 2) <=
//                        std::pow(180, 2)) {
//                        numPoints++;
//                        //ring2.setPointCount(3);
//
//                        for (int i = 0; i < ring2.getPointCount(); i++) {
//
//
//                            if (i < ring2.getPointCount() - 1) {
//                                cout << "mouse x: " << event.mouseButton.x << " mouse y: " << event.mouseButton.y <<
//                                endl;
//                                cout << "point i x is: " << ring2.getPoint(i).x << "      point i y is: " <<
//                                ring2.getPoint(i).y + 194 << endl;
//                                cout << "point i + 1 x is: " << ring2.getPoint(i + 1).x << "   point i +1  y is: " <<
//                                ring2.getPoint(i + 1).y + 194 << endl << endl;
//
//                                if (event.mouseButton.x != ring2.getPoint(i).x &&
//                                    event.mouseButton.x != ring2.getPoint(i + 1).x &&
//                                    event.mouseButton.y != ring2.getPoint(i).y &&
//                                    event.mouseButton.y != ring2.getPoint(i + 1).y) {
//
//                                    if (ring2.getPoint(i).y != ring2.getPoint(i + 1).y) {
//                                        if (event.mouseButton.y >= (ring2.getPoint(i).y + 194) &&
//                                            event.mouseButton.y <= (ring2.getPoint(i + 1).y + 194) &&
//                                            event.mouseButton.x > 500) {
//                                            position_insert = i + 1;
//                                            break;
//
//                                        }
//                                        else if (event.mouseButton.y <= (ring2.getPoint(i).y + 194) &&
//                                                 event.mouseButton.y >= (ring2.getPoint(i + 1).y + 194) &&
//                                                 event.mouseButton.x < 500) {
//                                            cout << "what's up?" << endl;
//                                            position_insert = i + 1;
//                                            break;
//
//                                        }
//                                    }
//                                    else {
//                                        if (event.mouseButton.x <= (ring2.getPoint(i).x + 330) &&
//                                            event.mouseButton.x >= (ring2.getPoint(i + 1).x + 330)
//                                            && event.mouseButton.y >= (ring2.getPoint(i).y + 194)) {
//                                            cout << "equal" << endl;
//                                            position_insert = i + 1;
//                                            break;
//
//                                        }
//                                    }
//                                }
//                            }
//                            else {
//                                cout << "in here" << endl;
//                                if ((event.mouseButton.y < (ring2.getPoint(i).y + 194)) &&
//                                    (event.mouseButton.y > (ring2.getPoint(0).y + 194)) && event.mouseButton.x < 500) {
//                                    position_insert = -1;
//
//                                }
//
//                            }
//                        }
//                        randNum = rand() % (max - min + 1) + min;
//                        AtomDisplay temp{randNum};
//
//                        if (position_insert != -1) {
//                            shapes.insert(shapes.begin() + position_insert, temp);
//                        }
//                        else {
//                            shapes.push_back(temp);
//                        }
//                        ring2.setPointCount(numPoints);
//                        cout << numPoints << " and position " << position_insert << endl;
//                        for (int i = 0; i < ring2.getPointCount(); i++) {
//                            sf::Vector2f position = ring2.getPoint(i);
//                            shapes[i].setPosition(position.x + 330, position.y + 194);
//                        }
//                    }
//                    else {
//                        cout << "wrong" << endl;
//                    }
//
//                }
//            }
//
//            /*switch(event.type)
//            {
//                case sf::Event::KeyPressed:
//                    if(event.key.code == sf::Keyboard::Up)
//                    {
//                        shape.move(0, -1);
//                    }
//                    if(event.key.code == sf::Keyboard::Down)
//                    {
//                        shape.move(0, 1);
//                    }
//                    if(event.key.code == sf::Keyboard::Left)
//                    {
//                        shape.move(-1,0);
//                    }
//                    if(event.key.code == sf::Keyboard::Right)
//                    {
//                        shape.move(1, 0);
//                    }
//                    cout << shape.getPosition().x << " " << shape.getPosition().y << endl;
//                    break;
//
//            }*/
//
//
//
//        }
//        window.clear();
//        window.draw(ring);
//        //window.draw(shape);
//        window.draw(ring2);
//        window.draw(ring3);
//        window.draw(node);
//        window.draw(try1);
//        for (int i = 0; i < shapes.size(); i++) {
//
//            shapes[i].draw1(window);
//
//
//        }
//
//        window.display();
//    }
//    return 0;
//}



//    int width = 769;
//    int height = 769;
//    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Titlebar | sf::Style::Close);
//    sf::CircleShape c;
//    c.setFillColor(sf::Color::Red);
//    c.setPosition(width / 2.f, height / 2.f - 100);
//    c.setRadius(50);
//    c.setOrigin({200,200});
//
//    float angle = 1.0;
//
//    sf::Text text;
//    sf::Font font;
//    font.loadFromFile("coolvetica rg.ttf");
//    text.setFont(font);
//    text.setColor(sf::Color::White);
//    text.setPosition(1,1);
//    text.setString("ABC");
//    sf::Transform t;
//
//    while(window.isOpen())
//    {
//        sf::Event event;
//
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        window.clear(sf::Color::Black);
//
//        t.rotate(angle, { width/2.f, height / 2.f });
//
//        window.draw(c);
//        window.draw(text);
//        window.display();
//    }
