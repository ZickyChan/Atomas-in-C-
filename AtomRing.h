//
// Created by Mike Bui on 09/12/2015.
//

#ifndef ATOMAS_ATOMRING_H
#define ATOMAS_ATOMRING_H

#include <iostream>
#include <list>

typedef struct atom {
    int index;
    struct atom *next;
    struct atom *last;
} Atom;



using namespace std;

class AtomRing {
public:
    int getSize() {
        if (atom == nullptr)
            return 0;
        if (atom->next == nullptr)
            return 1;
        Atom *start = atom;
        Atom *current = start->next;
        int count = 0;
        while (current->next != start) {
            current = current->next;
            count++;
        }
        return count;
    }



    void addAtom(int value) {
        Atom *atom = new Atom();
        atom->index = value;
        atom->next = nullptr;
        atom->last = nullptr;

        if (this->atom == nullptr) {
            this->atom = atom;
        }
        else if (this->atom->next == nullptr) {
            this->atom->next = atom;
            atom->last = this->atom;
            this->atom->last = atom;
            atom->next = this->atom;
        }

        else {
            atom->next = this->atom->next;
            atom->last = this->atom;
            this->atom->next->last = atom;
            this->atom->next = atom;
        }
        forward();
    }

    Atom *getAtom() {
        return atom;
    }

    void processPlus() {
        if (atom->index == -2) {
                int value = atom->next->index;
                if (value == atom->last->index) {
                    deleteAtom(atom->last);
                    deleteAtom(atom->next);
                    atom->index = value + 1;
                }

        }
    }

    void deleteAtom(Atom *atom) {
        if (atom != nullptr) {
//            atom->next->last = atom->last;
//            atom->last->next = atom->next;
//            free(atom);
            Atom *temp = atom;
            atom = atom -> last;
            temp->next = atom->next;
            temp->next->last = atom;
            free(temp);
        }
//
//        Atom *temp = atom;
//        atom = atom -> last;
//        temp->next->last = temp->last;
//        temp->last->next = temp->next;
//        free(temp);
    }

    void forward() {
        if (atom->next != 0)
            atom = atom->next;
    }
    void back() {
        if (atom->last != 0)
            atom = atom->last;
    }

private:
    Atom *atom;
    Atom *start;
};


#endif //ATOMAS_ATOMRING_H
