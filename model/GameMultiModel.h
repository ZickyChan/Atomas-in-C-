//
// Created by bit on 1/10/16.
//

#ifndef ATOMAS_GAMEMULTIMODEL_H
#define ATOMAS_GAMEMULTIMODEL_H

#include "../game/AtomRing.h"
#include "../game/Atomas.h"

class GameMultiModel{
public:
    GameMultiModel():atomas1{6},atomas2{6} {
        atomas1.addAtoms(6);
    }
    GameMultiModel(GameMultiModel &gm):atomas1{gm.atomas1},atomas2{gm.atomas2}{}

    int getAtomRingSize(){
        return atomas1.getRingSize();
    }

    int getAtomValue(int index){
        Atom *temp = atomas1.get_index_atom(index);
        return temp->atom;
    }

    int getCenterValue(){
        //cout << " value: " << atomas1.getPlayerAtom() << endl;
        return atomas1.getPlayerAtom();
    }

    int getCurrentIndex(){
        return atomas1.getCurrentIndex();
    }

    void deleteAtom(int index){
        atomas1.deleteAtom(index);
    }

    void addAtomToRing(int index){
        atomas1.player_to_ring(index);
    }

    void Print(){
        atomas1.printGame();
    }

    void forward(){
        atomas1.forward();
    }

    int check_proton(){
        return atomas1.check_proton();
    }

    int getScore(){
        return atomas1.getScore();
    }

    void setNewCenterValue(){
        atomas1.replace_player_atom();
    }

    AtomRing& getRing(){
        return atomas1.getRing();
    }

    void restart(){
        Atomas a{6};
        a.printGame();
        atomas1 = a;
        atomas1.addAtoms(6);
        atomas1.printGame();
    }

    Atomas &getAtomas(int i){
        if(i==0){
            return atomas1;
        }
        else {
            return atomas2;
        }
    }
private:
    Atomas atomas1;
    Atomas atomas2;

};

#endif //ATOMAS_GAMEMULTIMODEL_H
