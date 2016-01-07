//
// Created by bit on 1/6/16.
//

#include "AtomRing.h"

#include "AtomRing.h"

int AtomRing::getMaxAtom() {
    int max = 0;
    Atom *current = atom;
    for (int i = 0; i < size; i++) {
        if (current->atom > max)
            max = current->atom;
        current = current->next;
    }
    return max;
}

void AtomRing::addAtom(Atom *atom) {
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

void AtomRing::addAtom(int value) {
    Atom *atom = new Atom();
    atom->atom = value;
    atom->next = nullptr;
    atom->last = nullptr;
    addAtom(atom);
}

int AtomRing::deleteAtom() {
    int index = -2;
    if (forward()) {
        index = atom->atom;
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

int AtomRing::deleteLastAtom() {
    if (back()) {
        return deleteAtom();
    }
    return NULL_ATOM;
}

int AtomRing::deleteNextAtom() {
    int index = NULL_ATOM;
    if (forward()) {
        index = atom->atom;
        deleteAtom();
        back();
    }
    return index;
}

void AtomRing::deleteAtomLastNext() {
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

bool AtomRing::forward() {
    if (atom->next != nullptr) {
        atom = atom->next;
        return true;
    }
    return false;
}

bool AtomRing::back() {
    if (atom->last != nullptr) {
        atom = atom->last;
        return true;
    }
    return false;
}

void AtomRing::printRing() {
    if (atom != nullptr) {
        Atom *current = atom;
        cout << "Ring: ";
        for (int i = 0; i < size; i++) {
            if (atom == current)
                cout << "*" << current->atom << "* ";
            else
                cout << current->atom << " ";
            current = current->next;
        }
        cout << endl;
    }
}

int AtomRing::getAtom(int index) {
    Atom *current = atom;
    if (current == nullptr)
        return NULL_ATOM;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->atom;
}