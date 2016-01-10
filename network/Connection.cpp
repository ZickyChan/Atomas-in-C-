#include "Connection.h"
#include "../game/Atomas.h"

const int max_size = 1024;

string Connection::read() {
    boost::system::error_code error;
    char data[max_size];
    size_t length = socket->read_some(boost::asio::buffer(data, max_size), error);
    string myString(data);
    return myString;
}

void Connection::send(string data) {
    char c_data[max_size];
    strcpy(c_data, data.c_str());
    socket->write_some(boost::asio::buffer(c_data, max_size));
}



void Connection::connect(string ip, string port, boost::asio::io_service &io_service) {
    try {
        boost::shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
        this->socket = socket;
        tcp::resolver resolver(io_service);
        boost::asio::connect(*socket, resolver.resolve({ip, port}));
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void Connection::setup() {
    Data data;
    data.put("name", name);
    data.put("count", to_string(count));
    send(data.to_json());
    Data data1(read());
    id = stoi(data1.get("id"));
    cout << "Setup Method: " << data1.to_json() << endl;
}

void Connection::wait_to_start(Atomas &player, Atomas &opponent) {
    Data start(read());
    int count = get_count();
    int this_id = connection_id();

    cout << "wait_to_start: " << start.to_json() << endl;

    for (int i = 0; i < count; i++) {
        int id = stoi(start.get(to_string(i)));
        if (this_id != id) {
            opponent.setId(id);
        }
    }

    Data data;
    player.add_ring_data(data);
    player.add_player_atom_data(data);

    cout << "Send this to Server: " << data.to_json() << endl;

    send(data.to_json());
    Data setup(read());
    cout << "Read from Server: " << setup.to_json() << endl;

    stringstream atom_stream;
    stringstream player_atom_stream;
    atom_stream << opponent.getId() << ".atom";
    player_atom_stream << opponent.getId() << ".player_atom";

    Data atoms = setup.get_child(atom_stream.str());
    int player_atom = stoi(setup.get(player_atom_stream.str()));


    opponent.add_atoms(atoms);
    opponent.replace_player_atom(player_atom);
    opponent.print();
}

