#ifndef ATOMAS_ATOMRING_H
#define ATOMAS_ATOMRING_H


#include <iostream>
#include "../network/Data.h"

#define NULL_ATOM -10   ///< Value returned when getting an invalid Atom from linked list

using namespace std;

/*
 * struct for node in linked list
 */
typedef struct atom {
    int atom;
    int isotope;
    struct atom *next;
    struct atom *last;
} Atom;

/*
 * Function to free an atom allocated on the heap, if its isotope value is 0
 * @param atom to be freed
 * @return true if atom is freed, else isotope value is decremented by 1 and false returned
 */
bool free_atom(Atom *atom);

/*
 * Class for the implementation of a specialised doubled linked list for use in game logic
 */
class AtomRing {
public:
    /*
     * Constructor for AtomRing class
     */
    AtomRing(): atom{nullptr}, size{0}, index{0} {}

    int get_size() {
        return size;
    }

    int get_index(){
        return index;
    }
    /*
     * Get the int value of atom at index
     * @param index the index of the atom relative to the head of the linked list
     * @return the value stored in the atom at index
     */
    int get_atom(int index) {
        move_to_index(index);
        return atom->atom;
    }

    /*
     * Sets the value of atom at index
     * @param index the index of the atom relative to the head of the linked list
     * @param value the new value to be assigned to atom at index
     */
    void set_atom(int index, int value) {
        move_to_index(index);
        atom->atom = value;
    }

    /*
     * Adds delta to value of atom at index
     * @param index the index of the atom relative to the head of the linked list
     * @param delta the change to be applied to value of atom at index
     */
    void addToAtom(int index, int delta) {
        move_to_index(index);
        atom->atom += delta;
    }

    /*
     * Gets the maximum atom value in the linked list
     * @return the maximum value of all the atoms in linked list
     */
    int get_max_atom();

    /*
     * Creates an atom with the selected value and isotope, and inserts it into position after index
     * @param index the index of the atom relative to the head of the linked list. Atom will be inserted in front of this
     * @param value the value of the atom to be created
     * @param isotope the isotope of the atom to be created
     */
    void add_atom(int index, int value, int isotope);

    /*
     * Deletes an atom if its isotope value is equal to zero, and decrements its isotope by 1 othewise
     * @param index the index of the atom to be deleted relative to the head of the linked list
     * @return true if atom is deleted, else isotope value is decremented by 1 and false returned
     */
    bool delete_atom(int index);

    /*
     * Prints values of atoms to terminal
     */
    void print();

    /*
     * Reads a data object and adds atoms to ring from data object
     * @param data a reference to a data object to be read
     */
    void add_atoms_from_data(Data &data);

    /*
     * Gets pointer to atom in linked list at index
     * @param index the index of the atom relative to the head of the linked list
     * @return a pointer to atom at index
     */
    Atom *get_atom_pointer(int index) {
        move_to_index(index);
        return atom;
    }

    /*
     * Moves the root atom stored in linked list forward by one
     * @return true if move is successful, false if no move occurs
     */
    bool forward();

    /*
     * Moves the root atom stored in linked list forward by one
     * @return true if move is successful, false if no move occurs
     */
    bool back();

    /*
     * Increments the index field in object by one, circling back to zero if index exceeds size - 1
     */
    void increment_index() {
        index = (index + 1) % size;
    }

    /*
     * Decrements the index field in object by one, circling to size - 1 if index is less than zero
     */
    void decrement_index() {
        index = (index - 1 + size) % size;
    }

    /*
     * Moves the root atom stored in linked list to index
     * @param index the index of the atom relative to the head of the linked list
     */
    void move_to_index(int index);


private:
    Atom *atom; ///< The root atom of the linked list, can be moved forwards or backwards to next or last atom
    int size;   ///< The number of atoms in linked list
    int index;  ///< A value used to keep track of relative positions of atoms in linked list

    /*
     * Adds atom pointer to linked list at index
     * @param index the index of the atom relative to the head of the linked list. Atom will be inserted in front of this
     * @param atom pointer to atom to be added
     */
    void add_atom(int index, Atom *atom);
};


#endif //ATOMAS_ATOMRING_H