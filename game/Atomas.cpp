//
// Created by bit on 1/6/16.
//

#include "Atomas.h"

int random_int(int min, int max) {
    if (max < min)
        return 0;
    return (rand() % (max - min + 1) + min);
}

Atom *random_atom(int min, int max, int ban) {
    Atom * atom = new Atom();
    atom->last = nullptr;
    atom->next = nullptr;
    int value = random_int(min, max);
    while(value < ban){
        value = random_int(min, max);
    }
    atom->atom = value;
    return atom;
}

bool check_adjacent(Atom *atom) {
    if (atom != nullptr && atom->last != nullptr && atom->next != nullptr && atom->next->atom > PROTON && atom->last != atom->next)
        return atom->last->atom == atom->next->atom;
    return false;
}

void Atomas::replace_player_atom() {
    int value = random_int(ELECTRON, max / 2);
    while (value < ban){
        value = random_int(ELECTRON, max / 2);
    }
    replace_player_atom(value);
}

void Atomas::replace_player_atom(int player_atom) {
    this->player_atom = player_atom;
}


bool Atomas::player_to_ring() {
    bool replace = true;
    /*if (player_atom == ELECTRON) {
        player_atom = ring.get_atom()->atom;
        ring.deleteAtom();
        replace = false;
    }
    else {
        ring.addAtom(player_atom);
        replace_player_atom();
        setMax();
    }*/
    ring.addAtom(player_atom);
    replace_player_atom();
    setMax();
    index = (index + 1)%(ring.get_size());
    //check_protons();
    return replace;
}

bool Atomas::player_to_ring(int index) {
    move_to_index(index);
    return player_to_ring();
}

void Atomas::deleteAtom(int index){
    move_to_index(index);
    ring.deleteAtom();
    replace_player_atom();
}
//void Atomas::check_protons() {
//    int count = ring.get_size();
//    while (count > 0) {
//        if (ring.get_atom()->atom == PROTON) {
//            count -= check_proton();
//        }
//        forward();
//        count--;
//    }
//}

int Atomas::check_proton() {
    int deleted = 0;
    if (check_adjacent(ring.get_atom())) {
        int index = ring.deleteNextAtom();
        ring.deleteLastAtom();

        if (ring.get_atom()->atom == 0) {
            ring.addToAtom(++index);
        }
        else if (ring.get_atom()->atom > index)
            ring.addToAtom(1);
        else
            ring.setAtom(index + 2);
        deleted += check_proton() + 2;
        if(this->index > 0){
            this->index--;
        }
    }
    cout << "CURRENT INDEX: " << this-> index;
    ring.printRing();
    return deleted;
}

void Atomas::addAtoms(int count) {
    for (int i = 0; i < count; i++) {
        ring.addAtom(random_atom(HYDROGEN, max / 2,ban));
    }
}

void Atomas::setMax() {
    int max = ring.getMaxAtom();
    if (this->max < max)
        this->max = max;
}

void Atomas::printGame() {
    cout << "Max: " << max << " Size: " << ring.get_size() << endl;
    ring.printRing();
    cout << "Player: " << player_atom << endl;
    cout << "Current index: " << index << endl;
}

void Atomas::forward() {
    if(ring.forward())
    {
        index = (index + 1) % (ring.get_size());
    }
}

void Atomas::back() {
    if(ring.back())
    {
        index = (index - 1 + ring.get_size()) % ring.get_size();
    }

}

Atom *Atomas::get_index_atom(int index) {
    Atom *current = ring.get_atom();
    int count = this->index - index;
    if (count < 0)
        for (int i = count; i != 0; i++)
            current = current->next;
    else if (count > 0)
        for (int i = count; i != 0; i--)
            current = current->last;
    return current;
}


void Atomas::move_to_index(int index) {
    if (index > ring.get_size() - 1 || ring.get_size() < 2)
        return;

    int count = this->index - index;
    if (count < 0)
        for (int i = count; i != 0; i++) {
            forward();

        }
    else if (count > 0)
        for (int i = count; i != 0; i--) {
            back();
        }
    this->index = index;
}

//
//void Atomas::add_ring_data(Data &data) {
//    Atom *atom = get_index_atom(0);
//    for (int i = 0; i < ring.get_size(); i++) {
//        data.add_atom(i, atom->atom);
//    }
//
//}
//
//void Atomas::add_player_atom_data(Data &data) {
//    data.put("player_atom", player_atom);
//}