#include <iostream>
#include "AtomRing.h"

using namespace std;

int main() {
    AtomRing ring = AtomRing();

    Atom *atom = ring.getAtom();


    ring.addAtom(1);
    ring.addAtom(1);
    ring.addAtom(1);
    ring.addAtom(1);
    ring.addAtom(-2);



    cout << atom->next->index << atom->index << atom->last->index;

    return 0;
}