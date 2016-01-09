//
// Created by bit on 1/5/16.
//

#ifndef ATOMAS_GAMEMODEL_H
#define ATOMAS_GAMEMODEL_H

#include "../game/Atomas.h"
#include "../game/AtomRing.h"
class GameModel{
public:
    GameModel():atomas{6} {
        atomas.addAtoms(6);
    }
    GameModel(GameModel &gm):atomas{gm.atomas}{}

    int getAtomRingSize(){
        return atomas.getRingSize();
    }

    int getAtomValue(int index){
        Atom *temp = atomas.get_index_atom(index);
        return temp->atom;
    }

    int getCenterValue(){
        return atomas.getPlayerAtom();
    }

    int getCurrentIndex(){
        return atomas.getCurrentIndex();
    }

    void deleteAtom(int index){
        atomas.deleteAtom(index);
    }

    void addAtomToRing(int index){
        atomas.player_to_ring(index);
    }

    void Print(){
        atomas.printGame();
    }

    void forward(){
        atomas.forward();
    }

    int check_proton(){
        return atomas.check_proton();
    }

    int getScore(){
        return atomas.getScore();
    }

    void setNewCenterValue(){
        atomas.replace_player_atom();
    }

    AtomRing& getRing(){
        return atomas.getRing();
    }

    void restart(){
        Atomas a{6};
        a.printGame();
        atomas = a;
        atomas.addAtoms(6);
        atomas.printGame();
    }
private:
    Atomas atomas;

};

#endif //ATOMAS_GAMEMODEL_H
