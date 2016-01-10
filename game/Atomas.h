//
// Created by Mike Bui on 05/01/2016.
//

#ifndef ATOMAS_CLIENT_ATOMAS_H
#define ATOMAS_CLIENT_ATOMAS_H


#ifndef ATOMAS_SERVER_ATOMAS_H
#define ATOMAS_SERVER_ATOMAS_H

#define ELECTRON -1
#define PROTON 0
#define HYDROGEN 1

#include "AtomRing.h"

int random_int(int min, int max);

Atom *random_atom(int min, int max);

class Atomas {
public:
    Atomas(int max): max{max},ban{-2},score{0} {
        player_atom = random_int(HYDROGEN, max / 2);
    }

    int getRingSize(){
        return ring.get_size();
    }


    void replace_player_atom();

    void replace_player_atom(int player_atom);

    bool player_to_ring(int index);

    void addAtoms(int count);

    void set_max();

    void print();

    void add_ring_data(Data &data);

    void add_player_atom_data(Data &data);

    void add_atom(int index, int value, int isotope);

    int check_proton(int index);

    int getId() const {
        return id;
    }

    void setId(int id) {
        Atomas::id = id;
    }

    Atom *get_atom_pointer(int index);

    void add_atoms(Data &data);

    int find_proton();

    int getPlayerAtom(){
        return player_atom;
    }

    void deleteAtom(int index){
        ring.delete_atom(index);
    }

    AtomRing &getRing(){
        return ring;
    }
    int getScore(){
        return score;
    }

    void setBan(){
        if (ban == -2 && (max/2) == 5){
            ban = 1;
        }
        else if(((max/2) - ban > 4)){
            ban++;
        }
    }

private:
    AtomRing ring;
    int player_atom;
    int max;
    int id;
    int score;
    int ban;


};

#endif //ATOMAS_SERVER_ATOMAS_H


#endif //ATOMAS_CLIENT_ATOMAS_H
