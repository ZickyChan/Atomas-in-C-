#ifndef ATOMAS_GAME_H
#define ATOMAS_GAME_H

#define ELECTRON -1
#define PROTON 0
#define HYDROGEN 1

#include "AtomRing.h"

Atom *randomAtom(int min, int max) {
    Atom * atom = new Atom();
    atom->last = nullptr;
    atom->next = nullptr;
    atom->index = (rand() % (max - min + 1)) + min;
    return atom;
}

bool checkAdjacent(Atom* atom) {
    if (atom != nullptr && atom->last != nullptr && atom->next != nullptr && atom->next->index > PROTON && atom->last != atom->next)
        return atom->last->index == atom->next->index;
    return false;
}

class Game {
public:
    Game(int max) {
        srand((unsigned int)time(NULL));
        this->max = max;
        ring = new AtomRing();
        player = randomAtom(HYDROGEN, max / 2);
    }

    void replacePlayerAtom() {
        if (player != nullptr) {
            player = randomAtom(ELECTRON, max / 2);
        }
    }

    void playerToRing() {
        if (player->index == ELECTRON) {
            player->index = ring->getAtom()->index;
            ring->deleteAtom();
        }
        else {
            ring->addAtom(player);
            replacePlayerAtom();
            setMax();
        }
        checkProtons();
    }

    void checkProtons() {
        int count = ring->getSize();
        while (count > 0) {
            if (ring->getAtom()->index == PROTON) {
                count -= checkProton();
            }
            forward();
            count--;
        }
    }

    int checkProton() {
        int deleted = 0;
        if (checkAdjacent(ring->getAtom())) {
            int index = ring->deleteNextAtom();
            ring->deleteLastAtom();

            if (ring->getAtom()->index == 0) {
                ring->addToAtom(++index);
            }
            else if (ring->getAtom()->index > index)
                ring->addToAtom(1);
            else
                ring->setAtom(index + 2);
            deleted += checkProton() + 2;
        }
        return deleted;
    }


    void addAtoms(int count) {
        for (int i = 0; i < count; i++) {
            ring->addAtom(randomAtom(HYDROGEN, max / 2));
        }
    }

    void setMax() {
        int max = ring->getMaxAtom();
        if (this->max < max)
            this->max = max;
    }

    void printGame() {
        cout << "Max: " << max << " Size: " << ring->getSize() << endl;
        ring->printRing();
        cout << "Player: " << player->index << endl;
    }

    void forward() {
        ring->forward();
    }

    void back() {
        ring->back();
    }

private:
    AtomRing *ring;
    Atom *player;
    int max;
};


#endif //ATOMAS_GAME_H
