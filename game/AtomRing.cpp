#include "AtomRing.h"

bool free_atom(Atom *atom) {
    if (atom->isotope > 0) {
        atom->isotope--;
        return false;
    }
    delete atom;
    return true;
}

int AtomRing::get_max_atom() {
    int max = 0;
    Atom *current = atom;
    for (int i = 0; i < size; i++) {
        if (current->atom > max)
            max = current->atom;
        current = current->next;
    }
    return max;
}

void AtomRing::add_atom(int index, Atom *atom) {
    if (size == 0) {
        this->atom = atom;
        size++;
    }
    else if (size == 1) {
        this->atom->next = atom;
        this->atom->last = atom;
        atom->next = this->atom;
        atom->last = this->atom;
        size++;

    }
    else {
        move_to_index(index);
        atom->last = this->atom;
        atom->next = this->atom->next;
        this->atom->next->last = atom;
        this->atom->next = atom;
        size++;
    }
}

void AtomRing::add_atom(int index, int value, int isotope) {
    Atom *atom = new Atom();
    atom->atom = value;
    atom->isotope = isotope;
    atom->next = nullptr;
    atom->last = nullptr;
    atom->isotope = isotope;
    add_atom(index, atom);
}

bool AtomRing::delete_atom(int index) {
    if (size == 0) {
        cout << "ATOM NOT DELETED1" << endl;
        return false;
    }
    if (size == 1) {
        if (free_atom(atom)) {
            atom = nullptr;
            size--;
            return true;
        }
        cout << "ATOM NOT DELETED2" << endl;
        return false;
    }
    if (size == 2) {
        move_to_index(index);
        back();
        if (free_atom(atom->next)) {
            atom->next = nullptr;
            atom->last = nullptr;
            this->index = 0;
            size--;
            return true;
        }
        cout << "ATOM NOT DELETED3" << endl;
        return false;
    }
    move_to_index(index);
    back();
    Atom *temp = atom->next->next;
    if (free_atom(atom->next)) {
        atom->next = temp;
        temp->last = atom;
        if (index == 0)
            decrement_index();
        size--;
        return true;
    }
    cout << "ATOM NOT DELETED4" << endl;
    return false;
}

bool AtomRing::forward() {
    if (atom->next != nullptr) {
        atom = atom->next;
        increment_index();
        return true;
    }
    return false;
}

bool AtomRing::back() {
    if (atom->last != nullptr) {
        atom = atom->last;
        decrement_index();
        return true;
    }
    return false;
}

void AtomRing::print() {
    move_to_index(0);
    Atom *current = atom;
    cout << "Ring: ";
    for (int i = 0; i < size; i++) {
        cout << current->atom << " ";
        current = current->next;
    }
    cout << endl;
}

void AtomRing::move_to_index(int index) {
    while (index < 0) {
        index += size;
    }
    index = index % size;
    int count = this->index - index;
    if (count < 0)
        for (int i = count; i != 0; i++)
            forward();
    else if (count > 0)
        for (int i = count; i != 0; i--)
            back();
    this->index = index;
}

void AtomRing::add_atoms_from_data(Data data) {

}

