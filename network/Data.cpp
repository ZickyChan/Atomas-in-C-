#include "Data.h"

string Data::to_json() {
    std::stringstream data;
    write_json(data, tree, true);
    return data.str();
}

void Data::put(string key, string value) {
    tree.put(key, value);
}

void Data::put(string key, int value) {
    tree.put(key, to_string(value));
}

void Data::put(string key, Data data) {
    this->tree.add_child(key, data.get_tree());
}

string Data::get(string key) {
    boost::optional<string> o_string = tree.get_optional<string>(key);
    string data = ERROR;
    if (o_string)
        data = o_string.get();
    return data;
}

Data Data::get_child(string key) {
    boost::optional<ptree&> o_tree = tree.get_child_optional(key);
    ptree tree;
    if (o_tree)
        tree = o_tree.get();
    Data child(tree);
    return child;
}

void Data::add_atom(int index, int atom) {
    stringstream key;
    key << "atom." << index;
    tree.put(key.str(), atom);
}



