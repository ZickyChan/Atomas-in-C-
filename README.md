# README #

This project was completed by Tran Thach Thao, s3494528 and Bui Viet Phuong, s3463064.

### What is this repository for? ###

This repository contains the Client for playing a single or multiplayer game of Atomas.

### How do I get set up? ###

To setup the server or client, open project using Clion. This project has been tested on the Debian image provided by the lecturer using VirtualBox.

In order to run the server or client, first click "Run"->"Edit Configurations" in the file menu bar. Click on "Application" in the sidebar and for "Target:" choose "atomas_server" and click "OK". The project can now be compiled and run using Clion.

### How to Play ###

To play a single player game, the server does not need to be running. Run the client program from Clion, and when the game interface window opens, click on "1 Player".

A ring of atoms will appear on the screen with the player's atom appearing in the centre. Each turn, the player must move his/her atom to the ring by clicking on an area between two atoms, and his/her atom is replaced by a new one. When a player receives a "+" atom, he/she should move it between two atoms of identical value. This will cause the two atoms to fuse, leaving behind an atom of higher value and points are scored. This process can cause two or more atoms to fuse, creating a combo, thus scoring more points. When a player receives a "-" atom, he/she must click on an atom to delete it from the ring. This is useful for removing atoms with a value or position that is difficult to cause fusion. The game ends when the the atom ring is filled with 24 atoms.

### Known Issues ###

Due to unresolvable issues, the multiplayer game option is incomplete. Currently, the multiplayer allows for two players to play, with each player being able to view the other player's ring, but there is no interaction between the individual games.

For reasons unknown, a client may suddenly go into an non-stop infinite loop as it attempts to read from the server and a likely EOF value is returned. It is suspected that this is due to the TCP connection breaking, as normally, a call to the read function in the client is synchronous, as such it waits for the server to send data before returning. This would not be possible if connected to the server, as the server does not send continuous data to clients (the server waits for messages from clients and forwards them on to other players). This issue was unable to be resolved, and it is possible that it is an issue with the internet connection and not entirely due to the code.

### Notes ###

Initially, it was believed that the game logic portion was relatively simple, however, complex manipulation of and comparisons between elements of a double linked list proved to be more difficult than imagined. Several strategies were implemented to help simplify these operations, though the implementation of these strategies also proved to be challenging.

The AtomRing class itself implements many of the necessary functions for basic manipulations of a double linked list. However, in order to maintain the code's readability, the more complex game-specific manipulations of the AtomRing reside in functions belonging to the Atomas class, which contains an instance of an AtomRing object. A similar strategy was employed for the implementation of <boost> library services such as sockets and threads.

Due to the nature of double linked lists, it is difficult to have a permanent root node as a reference point. In order to resolve this problem, the use of an additional variable (int index) was used keep track of the relative location of the current root atom. This solved many issues as it allowed for easy location of the atom at index = 0, regardless what the current root atom was pointing at.

The server logic was written to allow two or more players to participate in a given game against each other. Such functionality still theoretically exists (specifically in the WaitList class), however, due to the unexpected complexity of the game logic, the client program has been written to restrict multiplayer games to two players only.