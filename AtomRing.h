#ifndef ATOMAS_ATOMRING_H
#define ATOMAS_ATOMRING_H

#include <iostream>
#include <list>

using namespace std;


typedef struct atom {
    int index;
    struct atom *next;
    struct atom *last;
} Atom;

class AtomRing {
public:
    AtomRing() {
        atom = nullptr;
    }

    int getSize() {
        return size;
    }

    int getMaxAtom() {
        int max = 0;
        Atom *current = atom;
        for (int i = 0; i < size; i++) {
            if (current->index > max)
                max = current->index;
            current = current->next;
        }
        return max;
    }

    void addAtom(Atom *atom) {
        if (this->atom == nullptr) {
            this->atom = atom;
        }
        else if (this->atom->next == nullptr) {
            this->atom->next = atom;
            this->atom->last = atom;
            atom->last = this->atom;
            atom->next = this->atom;
        }
        else {
            atom->last = this->atom;
            atom->next = this->atom->next;
            this->atom->next->last = atom;
            this->atom->next = atom;
        }
        size++;
        forward();
    }

    void addAtom(int value) {
        Atom *atom = new Atom();
        atom->index = value;
        atom->next = nullptr;
        atom->last = nullptr;
        addAtom(atom);
    }


    Atom *getAtom() {
        return atom;
    }

    void setAtom(int index) {
        atom->index = index;
    }

    void addToAtom(int delta) {
        atom->index += delta;
    }


    int deleteAtom() {
        int index = -2;
        if (forward()) {
            index = atom->index;
            if (atom->next->next != atom) {
                atom->last->last->next = atom;
                Atom *temp = atom->last;
                atom->last = atom->last->last;
                free(temp);
            }
            else {
                free(atom->next);
                atom->next = nullptr;
                atom->last = nullptr;
            }
            size--;
        }
        return index;
    }

    int deleteLastAtom() {
        if (back()) {
            return deleteAtom();
        }
        return -2;
    }

    int deleteNextAtom() {
        int index = -2;
        if (forward()) {
            index = atom->index;
            deleteAtom();
            back();
        }
        return index;
    }

    void deleteAtomLastNext() {
        if (atom->next->next == atom->last->last) {
            free(atom->next);
            free(atom->last);
            atom->next = nullptr;
            atom->last = nullptr;
        }
        else {
            Atom *atom = this->atom->last;
            if (atom != nullptr) {
                atom->next->last = atom->last;
                atom->last->next = atom->next;
                free(atom);
            }
            atom = this->atom->next;
            if (atom != nullptr) {
                atom->next->last = atom->last;
                atom->last->next = atom->next;
                free(atom);
            }
        }
    }

    bool forward() {
        if (atom->next != nullptr) {
            atom = atom->next;
            return true;
        }
        return false;
    }

    bool back() {
        if (atom->last != nullptr) {
            atom = atom->last;
            return true;
        }
        return false;
    }

    void printRing() {
        if (atom != nullptr) {
            Atom *current = atom;
            cout << "Ring: ";
            for (int i = 0; i < size; i++) {
                if (atom == current)
                    cout << "*" << current->index << "* ";
                else
                    cout << current->index << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

private:
    Atom *atom;
    int size;
};

#endif //ATOMAS_ATOMRING_H
