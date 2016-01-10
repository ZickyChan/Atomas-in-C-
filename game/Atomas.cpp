//
// Created by Mike Bui on 02/01/2016.
//

#include "Atomas.h"

int random_int(int min, int max) {
    if (max < min)
        return 0;
    return (rand() % (max - min + 1) + min);
}

Atom *random_atom(int min, int max) {
    Atom * atom = new Atom();
    atom->last = nullptr;
    atom->next = nullptr;
    atom->atom = random_int(min, max);
    return atom;
}

void Atomas::replace_player_atom() {
    setBan();
    int value = random_int(ELECTRON, max/2 );
    while (value < ban || (value == -1 && ring.get_size() == 1)){
        value = random_int(ELECTRON, max/2);
    }
    replace_player_atom(value);
}

void Atomas::replace_player_atom(int player_atom) {
    this->player_atom = player_atom;
}


bool Atomas::player_to_ring(int index) {
    bool replace = true;
    ring.add_atom(index, player_atom, 0);
    set_max();

    return replace;
}

int Atomas::check_proton(int index) {
    int combo = 0;
    if (ring.get_size() < 3)
        return combo;
    int back_value = ring.get_atom(index - 1);
    int forward_value = ring.get_atom(index + 1);
    int value = ring.get_atom(index);
    if (back_value == forward_value && back_value > 0) {
        combo++;
        score += back_value * 2;

        if (value < back_value) {
            ring.set_atom(index, back_value);
            cout << "IN HERE BLAH BLAH BLAH " << value << endl;
        }
        ring.addToAtom(index, 1);
        cout << "new value of atom: " << ring.get_atom(index) << endl;
        cout << endl << endl;
        print();
        cout << endl << endl;
        bool forward_deleted = ring.delete_atom(index + 1);
        bool backward_deleted = ring.delete_atom(index - 1);
        print();
        if (index > 0)
            index--;
        combo += check_proton(index);

    }
    return combo;

}


void Atomas::addAtoms(int count) {
    for (int i = 0; i < count; i++) {
        ring.add_atom(i, random_int(HYDROGEN, max/2), 0);
    }
}

void Atomas::set_max() {
    int max = ring.get_max_atom();
    if (this->max < max)
        this->max = max;
}

void Atomas::print() {
    cout << "Max: " << max << " Size: " << ring.get_size() << endl;
    ring.print();
    cout << "Player: " << player_atom << endl;
}


void Atomas::add_ring_data(Data &data) {
    for (int i = 0; i < ring.get_size(); i++) {
        data.add_atom(i, ring.get_atom(i));
    }
}

void Atomas::add_player_atom_data(Data &data) {
    data.put("player_atom", player_atom);
}

void Atomas::add_atom(int index, int value, int isotope) {
    ring.add_atom(index, value, isotope);
}

int Atomas::find_proton() {
    for (int i = 0; i < ring.get_size(); i++)
        if (ring.get_atom(i) == PROTON)
            return i;
    return -1;
}

void Atomas::add_atoms(Data &data) {
    string value;
    int count = 0;
    while (true) {
        value = data.get(to_string(count));
        if (value == "ERROR") {
            cout << value << endl;
            break;
        }
        add_atom(count - 1, stoi(value), 0);
        count++;
    }
}
