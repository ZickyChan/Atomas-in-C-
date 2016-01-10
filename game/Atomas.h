////
//// Created by Mike Bui on 05/01/2016.
////
//
//#ifndef ATOMAS_CLIENT_ATOMAS_H
//#define ATOMAS_CLIENT_ATOMAS_H
//
//
//#ifndef ATOMAS_SERVER_ATOMAS_H
//#define ATOMAS_SERVER_ATOMAS_H
//
//#define ELECTRON -1
//#define PROTON 0
//#define HYDROGEN 1
//
//#include "AtomRing.h"
//
//int random_int(int min, int max);
//
//Atom *random_atom(int min, int max);
//
//class Atomas {
//public:
//    Atomas(int max): max{max},ban{-2},score{0} {
//        player_atom = random_int(HYDROGEN, max / 2);
//    }
//
//    int getRingSize(){
//        return ring.get_size();
//    }
//
//
//    void replace_player_atom();
//
//    void replace_player_atom(int player_atom);
//
//    bool player_to_ring(int index);
//
//    void addAtoms(int count);
//
//    void set_max();
//
//    void print();
//
//    void add_ring_data(Data &data);
//
//    void add_player_atom_data(Data &data);
//
//    void add_atom(int index, int value, int isotope);
//
//    int check_proton(int index);
//
//    int getId() const {
//        return id;
//    }
//
//    void setId(int id) {
//        Atomas::id = id;
//    }
//
//    Atom *get_atom_pointer(int index);
//
//    void add_atoms(Data &data);
//
//    int find_proton();
//
//    int getPlayerAtom(){
//        return player_atom;
//    }
//
//    void deleteAtom(int index){
//        ring.delete_atom(index);
//    }
//
//    AtomRing &getRing(){
//        return ring;
//    }
//    int getScore(){
//        return score;
//    }
//
//    void setBan(){
//        if (ban == -2 && (max/2) == 5){
//            ban = 1;
//        }
//        else if(((max/2) - ban > 4)){
//            ban++;
//        }
//    }
//
//private:
//    AtomRing ring;
//    int player_atom;
//    int max;
//    int id;
//    int score;
//    int ban;
//
//
//};
//
//#endif //ATOMAS_SERVER_ATOMAS_H
//
//
//#endif //ATOMAS_CLIENT_ATOMAS_H

#ifndef ATOMAS_ATOMAS_H
#define ATOMAS_ATOMAS_H

#define ELECTRON -1
#define PROTON 0
#define HYDROGEN 1

#include "AtomRing.h"

int random_int(int min, int max);

Atom *random_atom(int min, int max);

/*
 * Class providing more game specific functions for the manipulation of an AtomRing object
 */
class Atomas {
public:
    /*
     * Constructor for Atomas class
     * @param max used to set an upper bound for the atoms that can be generated during gameplay
     */
    Atomas(int max): max{max},ban{-2},score{0} {
        player_atom = random_int(HYDROGEN, max / 2);
    }

    int getRingSize(){
        return ring.get_size();
    }

    /*
     * Replaces player atom with a randomly generated one
     */
    void replace_player_atom();

    /*
     * Sets player atom to the new value, player_atom
     * @param player_atom the value to be assigned to player atom
     */
    void replace_player_atom(int player_atom);

    /*
     * Moves player_atom value to ring at index
     * @param index the index where the atom is to be inserted
     * @return true if the atom added to ring is an ELECTRON, else false
     */
    bool player_to_ring(int index);

    /*
     * Adds a number of random atoms to the AtomRing object
     * @param count the number of atoms to be added
     */
    void addAtoms(int count);

    /*
     * Determines the highest value of the atoms in AtomRing object and sets it to int max field
     */
    void set_max();

    /*
     * Prints Atomas state to terminal
     */
    void print();

    /*
     * Adds AtomRing object state data to data object
     * @param data a reference to a Data object to which data is added
     */
    void add_ring_data(Data &data);

    /*
     * Adds player_atom data to data objec
     * @param data a reference to a Data object to which data is added
     */
    void add_player_atom_data(Data &data);

    /*
     * Adds an atom with specified value and isotope to AtomRing object
     * @param index the index where the atom is to be inserted
     * @param value the value of the atom to be inserted
     * @param isotope the isotope of the atom to be inserted
     */
    void add_atom(int index, int value, int isotope);

    /*
     * Checks to see if fusion of atoms occurs at index
     * @param index the index of the atom to be checked
     * @return the count of how many fusions occured during check
     */
    int check_proton(int index);


    int getId() const {
        return id;
    }

    void setId(int id) {
        Atomas::id = id;
    }

    /*
     * Gets a pointer to an Atom struct at index
     * @param index the index where the pointer should be retrieved
     * @return a pointer to the atom at index
     */
    Atom *get_atom_pointer(int index);

    /*
     * Adds atoms to AtomRing object using data encoded in a Data object
     * @param data the Data object in which atom data is encoded
     */
    void add_atoms(Data &data);

    /*
     * Finds the first proton in AtomRing object
     * @return the index of the first proton in AtomRing object
     */
    int find_proton();

    int getPlayerAtom(){
        return player_atom;
    }

    void deleteAtom(int index){
        ring.delete_atom(index);
    }

    AtomRing &getRing(){
        return ring;
    }
    int getScore(){
        return score;
    }


    void setBan(){
        if (ban == -2 && (max/2) == 5){
            ban = 1;
        }
        else if(((max/2) - ban > 4)){
            ban++;
        }
    }

private:
    AtomRing ring;      ///< Data structure to store atoms in game
    int player_atom;    ///< Value of player's atom at centre of screen
    int max;            ///< The highest value of the atoms in ring
    int id;             ///< The ID of the game as assigned by the server
    int score;          ///< The score of the current game
    int ban;            ///< A lower bound for the atoms that can be generated for the player
};



#endif //ATOMAS_ATOMAS_H
