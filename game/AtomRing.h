#ifndef ATOMAS_CLIENT_ATOMRING_H
#define ATOMAS_CLIENT_ATOMRING_H


#include <iostream>
#include "../network/Data.h"

#define NULL_ATOM -10

using namespace std;


typedef struct atom {
    int atom;
    int isotope;
    struct atom *next;
    struct atom *last;
} Atom;

bool free_atom(Atom *atom);

class AtomRing {
public:
    AtomRing(): atom{nullptr}, size{0}, index{0} {}

    int get_size() {
        return size;
    }

    int get_index(){
        return index;
    }

    int get_atom(int index) {
        move_to_index(index);
        return atom->atom;
    }

    void set_atom(int index, int value) {
        move_to_index(index);
        atom->atom = value;
    }

    void addToAtom(int index, int delta) {
        move_to_index(index);
        atom->atom += delta;
    }

    int get_max_atom();

    void add_atom(int index, int value, int isotope);

    bool delete_atom(int index);

    void print();

    void add_atoms_from_data(Data &data);


    Atom *get_atom_pointer(int index) {
        move_to_index(index);
        return atom;
    }

    bool forward();

    bool back();

    void increment_index() {
        index = (index + 1) % size;
    }

    void decrement_index() {
        index = (index - 1 + size) % size;
    }

    void move_to_index(int index);


private:
    Atom *atom;
    int size;
    int index;

    void add_atom(int index, Atom *atom);


};


#endif //ATOMAS_CLIENT_ATOMRING_H
