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
        Atom *temp = atomas.getRing().get_atom_pointer(index);
        return temp->atom;
    }

    int getCenterValue(){
        return atomas.getPlayerAtom();
    }


    void deleteAtom(int index){
        atomas.deleteAtom(index);
    }

    void addAtomToRing(int index){
        atomas.player_to_ring(index);
    }

    void Print(){
        atomas.print();
    }

    int check_proton(int index){
        return atomas.check_proton(index);
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
    int findProton(){
        return atomas.find_proton();
    }
    void restart(){
        Atomas a{6};
        atomas = a;
        atomas.addAtoms(6);
    }
private:
    Atomas atomas;

};

#endif //ATOMAS_GAMEMODEL_H
