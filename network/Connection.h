//
// Created by Mike Bui on 30/12/2015.
//

#ifndef ATOMAS_CLIENT_CONNECT_H
#define ATOMAS_CLIENT_CONNECT_H


#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <string>

#include "Data.h"
#include "../game/Atomas.h"

#define MAX_LENGTH 1024

using namespace std;
using boost::asio::ip::tcp;

/*
 * Wraps <boost/asio.hpp> tcp socket connection services into class for sending and receiving data conveniently
 */
class Connection {
public:
    /*
     * Constructor for Connection class
     * @param name name of the client joining server
     * @param count the number of players to wait for before game starts
     */
    Connection(string name, int count): name{name}, count{count} {}

    /*
     * Sends string data to client using socket
     * @param data the data to be sent to client
     */
    void send(string data);

    /*
     * Reads string data from client using socket
     * @return the string data received from client
     */
    string read();

    /*
     * Adds Connection object to vector connections
     * @param connection the connection to be added
     */
    void connect(string ip, string port, boost::asio::io_service &io_service);

    /*
     * Sends client data to server and receives client ID from server
     */
    void setup();

    void wait_to_start(Atomas &player, Atomas &opponent);

    int get_count() {
        return count;
    }

    int connection_id() {
        return id;
    }

private:
    int id;                                 ///< ID of client assigned by server
    int count;                              ///< The number of players to wait for before game starts
    string name;                            ///< Name of the client
    boost::shared_ptr<tcp::socket> socket;  ///< Shared pointer to socket object
};

#endif //ATOMAS_CLIENT_CONNECT_H
