//
// Created by bit on 1/6/16.
//

#ifndef ATOMAS_ATOMAS_H
#define ATOMAS_ATOMAS_H

#define ELECTRON -1
#define PROTON 0
#define HYDROGEN 1

#include <stdlib.h>
#include "AtomRing.h"

int random_int(int min, int max);

Atom *random_atom(int min, int max, int ban);

bool check_adjacent(Atom *atom);

class Atomas {
public:
    Atomas(int max): max{max},ban{-2},score{0} {
        srand((unsigned int)time(NULL));
        player_atom = random_int(HYDROGEN, max / 2);
    }
    Atomas(Atomas &a): ring{a.ring}{
        player_atom = a.player_atom;
        max = a.max;
        ban = a.ban;
        score = a.score;
    }

    int getScore(){
        return score;
    }

    int getRingSize(){
        return ring.get_size();
    }

    int getPlayerAtom(){
        return player_atom;
    }

    int getCurrentIndex(){
        return index;
    }

    AtomRing& getRing(){
        return ring;
    }

    void setBan(){
        if (ban == -2 && (max/2) == 5){
            ban = 1;
        }
        else if(((max/2) - ban > 4)){
            ban++;
        }
    }

    void replace_player_atom();

    void replace_player_atom(int player_atom);

    bool player_to_ring();

    bool player_to_ring(int index);

    void deleteAtom(int index);

    void check_protons();

    int check_proton();

    void addAtoms(int count);

    void setMax();

    void printGame();

    void forward();

    void back();

    Atom *get_index_atom(int index);

    void move_to_index(int index);

    //void add_ring_data(Data &data);

    //void add_player_atom_data(Data &data);

private:
    AtomRing ring;
    int player_atom;
    int max;
    int ban;
    int score;
    int index = 0;
};

#endif //ATOMAS_ATOMAS_H
