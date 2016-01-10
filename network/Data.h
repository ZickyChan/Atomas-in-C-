#ifndef ATOMAS_CLIENT_DATA_H
#define ATOMAS_CLIENT_DATA_H

#define ERROR "ERROR"   ///< string to be returned if attempt is made to retrieve using invalid key

#include <map>
#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;
using boost::property_tree::json_parser::write_json;
using boost::property_tree::json_parser::read_json;

using namespace std;

/*
 * Data class encapusulates property tree implementation to store data and convert to JSON string to send over network
 */
class Data {
public:
    /*
     * Constructor for Data object
     * @param jString a JSON formatted string to be converted into a property tree for storage in Data object
     */
    Data(string j_string) {
        stringstream stream(j_string);
        read_json(stream, tree);
    }

    /*
     * Constructor for Data object
     * @param tree a property tree to be stored in object
     */
    Data(ptree tree): tree{tree} {}

    Data() {}

    /*
     * Puts string value into the Data object with string key
     * @param key the key used to retrieve the string value
     * @param value the value to be stored in Data object
     */
    void put(string key, string value);

    /*
     * Puts int value into the Data object with string key, value will be stored as a string
     * @param key the key used to retrieve the string value
     * @param value the value to be stored in Data object
     */
    void put(string key, int value);

    /*
     * Puts data object into this object as a branch under the specified key
     *  @param key the key used to retrieve the branch value
     *  @param data the data object to be added as a branch
     */
    void put(string key, Data data);

    /*
     * Gets the string value paired with the specified key
     * @param key the key paired with the desired string value
     * @return the string value paired with specified key
     */
    string get(string key);


    Data get_child(string key);

    /*
     * Encodes the data stored in Data object to a JSON string
     * @return a string in JSON format containing all key-value pairs and branches stored in this object
     */
    string to_json();

    /*
     * Adds index key and value atom to this object
     * @param index the key to be used for storing atom value
     * @param atom the value to be stored (as a string)
     */
    void add_atom(int index, int atom);

    ptree get_tree() {
        return tree;
    }

private:
    ptree tree; ///< Property tree used to store key value pairs
};

#endif //ATOMAS_CLIENT_DATA_H
