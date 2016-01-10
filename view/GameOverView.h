//
// Created by bit on 1/8/16.
//

#ifndef ATOMAS_GAMEOVERVIEW_H
#define ATOMAS_GAMEOVERVIEW_H

#include <SFML/Graphics.hpp>
#include <iostream>

class GameOverView{
public:
    GameOverView(int width, int height,int score, int mode):scr_width{width},scr_height{height},scoreValue{score}, mode{mode}{ }
    GameOverView(GameOverView &mv){
        scr_height = mv.scr_height;
        scr_width = mv.scr_width;
        score = mv.score;
        scoreValue = mv.scoreValue;
        replay = mv.replay;
        back_to_menu = mv.back_to_menu;
        mode = mv.mode;
    }
    void setPosition(){
        font1.loadFromFile("libelsuit.ttf");

        score.setFont(font1);
        score.setCharacterSize(60);
        score.setColor(sf::Color::White);
        score.setString(std::to_string(scoreValue));

        //center Title
        sf::FloatRect textRect = score.getLocalBounds();
        score.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        score.setPosition(sf::Vector2f(scr_width/2.0f,scr_height/2.0f - 100));

        replay.setFont(font1);
        replay.setCharacterSize(40);
        replay.setColor(sf::Color::White);
        replay.setString("Replay");

        //center replay text
        textRect = replay.getLocalBounds();
        replay.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
        replay.setPosition(sf::Vector2f(scr_width/2.0f - 150 ,scr_height/2.0f));


        back_to_menu.setFont(font1);
        back_to_menu.setCharacterSize(40);
        back_to_menu.setColor(sf::Color::White);
        back_to_menu.setString("Back To Menu");

        //center back to menu text
        textRect = back_to_menu.getLocalBounds();
        back_to_menu.setOrigin(textRect.left + textRect.width/2.0f,
                           textRect.top  + textRect.height/2.0f);
        back_to_menu.setPosition(sf::Vector2f(scr_width/2.0f + 100,scr_height/2.0f));

    }

    void setGameState(int state){
        game_state.setFont(font1);
        game_state.setCharacterSize(80);
        game_state.setColor(sf::Color::White);

        if(state == 1){
            game_state.setString("You Win!!!");
        }
        else{
            game_state.setString("Loser!!!");
        }
        //center Title
        sf::FloatRect textRect = game_state.getLocalBounds();
        game_state.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        game_state.setPosition(sf::Vector2f(scr_width/2.0f,scr_height/2.0f - 300));

    }

    bool inReplayText(int x, int y){
        bool result;
        sf::FloatRect replayRect = replay.getLocalBounds();
        std::cout << "start x: " <<(replay.getPosition().x - replayRect.width/2.0f) << " stop x: " << (replay.getPosition().x + replayRect.width/2.0f) << std::endl;
        std::cout << "start y: " <<(replay.getPosition().y - replayRect.height/2.0f) << " stop y: " << (replay.getPosition().y + replayRect.height/2.0f) << std::endl;
        result = ((x >= (replay.getPosition().x - replayRect.width/2.0f)) && (x <= (replay.getPosition().x + replayRect.width/2.0f))
                  && (y >= (replay.getPosition().y - replayRect.height/2.0f)) && (y <= (replay.getPosition().y + replayRect.height/2.0f)));
        return result;
    }

    bool inBackMenuText(int x, int y){
        bool result;
        sf::FloatRect player2Rect = back_to_menu.getLocalBounds();
        std::cout << "start x: " <<(back_to_menu.getPosition().x - player2Rect.width/2.0f) << " stop x: " << (back_to_menu.getPosition().x + player2Rect.width/2.0f) << std::endl;
        std::cout << "start y: " <<(back_to_menu.getPosition().y - player2Rect.height/2.0f) << " stop y: " << (back_to_menu.getPosition().y + player2Rect.height/2.0f) << std::endl;

        result = ((x >= (back_to_menu.getPosition().x - player2Rect.width/2.0f)) && (x <= (back_to_menu.getPosition().x + player2Rect.width/2.0f))
                  && (y >= (back_to_menu.getPosition().y - player2Rect.height/2.0f)) && (y <= (back_to_menu.getPosition().y + player2Rect.height/2.0f)));
        return result;
    }

    void draw(sf::RenderWindow &window){
        window.clear();
        window.draw(score);
        if(mode == 1) {
            window.draw(replay);
        }
        else{
            window.draw(game_state);
        }
        window.draw(back_to_menu);
        window.display();
    }

    int getMode(){
        return mode;
    }
private:
    int scr_width;
    int scr_height;
    int scoreValue;
    int mode;
    sf::Text score;
    sf::Text replay;
    sf::Text game_state;
    sf::Text back_to_menu;
    sf::Font font1;
};
#endif //ATOMAS_GAMEOVERVIEW_H
