#ifndef ATOMAS_ATOMRING_H
#define ATOMAS_ATOMRING_H


#include <iostream>

#define NULL_ATOM -10

using namespace std;


typedef struct atom {
    int atom;
    int isotope;
    struct atom *next;
    struct atom *last;
} Atom;

class AtomRing {
public:
    AtomRing() {
        atom = nullptr;
        size = 0;
    }

    AtomRing(AtomRing &ar){
        atom = ar.atom;
        size = ar.size;
    }

    int get_size() {
        return size;
    }

    Atom *get_atom() {
        return atom;
    }

    void setAtom(int index) {
        atom->atom = index;
    }

    void addToAtom(int delta) {
        atom->atom += delta;
    }

    int getMaxAtom();

    void addAtom(Atom *atom);

    void addAtom(int value);

    int deleteAtom();

    int deleteLastAtom();

    int deleteNextAtom();

    void deleteAtomLastNext();

    bool forward();

    bool back();

    void printRing();

    int getAtom(int index);

    void add_atom(int index, int value, int isotope);

    void move_to_index(int index);

private:
    Atom *atom;
    int size;
    int index;


    void increment_index() {
        index = (index + 1) % size;
    }

    void decrement_index() {
        index = (index - 1 + size) % size;
    }
};

#endif //ATOMAS_ATOMRING_H
