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
//    if (player_atom == ELECTRON) {
//        player_atom = ring.get_atom(index);
//        ring.delete_atom(index);
//        replace = false;
//    }
    ring.add_atom(index, player_atom, 0);
    set_max();

    //check_protons();
    return replace;
}

//
//int Atomas::check_protons() {
//    int index = 0;
//    int combo = 0;
//    while (index < ring.get_size()) {
//        if (ring.get_atom(index) == PROTON) {
//            int delta_combo = check_adjacent(index);
//            if (delta_combo > 0) {
//                combo += delta_combo;
//            }
//        }
//    }
//    return combo;
//}



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
//
//bool check_adjacent(Atom *atom) {
//    if (atom != nullptr && atom->last != nullptr && atom->next != nullptr && atom->next->atom > PROTON && atom->last != atom->next)
//        return atom->last->atom == atom->next->atom;
//    return false;
//}


//int Atomas::check_proton() {
//    int deleted = 0;
//    if (check_adjacent(ring.get_atom())) {
//        int index = ring.deleteNextAtom();
//        ring.deleteLastAtom();
//
//        if (ring.get_atom()->atom == 0) {
//            ring.addToAtom(++index);
//        }
//        else if (ring.get_atom()->atom > index)
//            ring.addToAtom(1);
//        else
//            ring.setAtom(index + 2);
//        score += index*2;
//        deleted += check_proton() + 2;
//        if(this->index > 0 ){
//            this->index--;
//        }
//    }
//    ring.printRing();
//    if (ring.get_size() == 1){
//        this->index = 0;
//    }
//    return deleted;
//}

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

//Atom *Atomas::get_index_atom(int index) {
//    Atom *current = ring.get_atom();
//    int count = this->index - index;
//    if (count < 0)
//        for (int i = count; i != 0; i++)
//            current = current->next;
//    else if (count > 0)
//        for (int i = count; i != 0; i--)
//            current = current->last;
//    return current;
//}


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
