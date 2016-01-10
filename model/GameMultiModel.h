//
// Created by bit on 1/10/16.
//

#ifndef ATOMAS_GAMEMULTIMODEL_H
#define ATOMAS_GAMEMULTIMODEL_H

#include "../game/AtomRing.h"
#include "../game/Atomas.h"
#include "../network/Connection.h"

class GameMultiModel{
public:
    GameMultiModel(std::string ip, std::string port, boost::asio::io_service &io_service):atomas1{6},atomas2{6},connection{"Mike",2} {
        atomas1.addAtoms(6);
        //connection.connect(ip, port, io_service);
        connection.connect("localhost", "6996", io_service);
        connection.setup();

        connection.wait_to_start(atomas1,atomas2);
    }
    GameMultiModel(GameMultiModel &gm):atomas1{gm.atomas1},atomas2{gm.atomas2},connection{gm.connection}{}

    int getAtomRingSize(){
        return atomas1.getRingSize();
    }

    int getAtomRing2Size(){
        return atomas2.getRingSize();
    }

    int getAtomValue(int index){
        return atomas1.getRing().get_atom(index);//temp->atom;
    }

    int getAtomValue2(int index){
        return atomas2.getRing().get_atom(index);
    }

    int getCenterValue(int mode){
        if(mode == 1) {
            return atomas1.getPlayerAtom();
        }
        else{
            return atomas2.getPlayerAtom();
        }
    }


    void deleteAtom(int index){
        atomas1.deleteAtom(index);
    }

    void deleteAtom2(int index){
        atomas2.deleteAtom(index);
    }

    void addAtomToRing(int index){
        atomas1.player_to_ring(index);
    }
    void addAtomToRing2(int index){
        atomas2.player_to_ring(index);
    }


    int check_proton(int index){
        return atomas1.check_proton(index);
    }

    int check_proton2(int index){
        return atomas2.check_proton(index);
    }

    int getScore(int mode){
        if(mode == 1) {
            return atomas1.getScore();
        }
        else{
            return atomas2.getScore();
        }
    }

    void setNewCenterValue(){
        atomas1.replace_player_atom();
    }

    void setNewCenterValue(int val){
        atomas2.replace_player_atom(val);
    }

    AtomRing& getRing(){
        return atomas1.getRing();
    }

    AtomRing& getRing2(){
        return atomas2.getRing();
    }


    Atomas &getAtomas(int i){
        if(i==0){
            return atomas1;
        }
        else {
            return atomas2;
        }
    }
    void send_normal(int index) {
        Data data;
        data.put("index", index);
        data.put("new atom",getCenterValue(1));
        data.put("type","normal");
        data.put("id",connection.connection_id());
        connection.send(data.to_json());
    }

    void send_minus(int index) {
        Data data;
        data.put("index", index);
        data.put("new atom",getCenterValue(1));
        data.put("type","minus");
        data.put("id",connection.connection_id());
        connection.send(data.to_json());
    }
    std::string read(){
        return connection.read();
    }
    void print(){
        atomas1.print();
    }
    void print2(){
        atomas2.print();
    }

private:
    Atomas atomas1;
    Atomas atomas2;
    Connection connection;

};

#endif //ATOMAS_GAMEMULTIMODEL_H
