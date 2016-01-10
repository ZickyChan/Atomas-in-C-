# README #

This project was completed by Tran Thach Thao, s3494528 and Bui Viet Phuong, s3463064.

### What is this repository for? ###

This repository contains the Client for playing a single or multiplayer game of Atomas.

### How do I get set up? ###

To setup the server or client, open project using Clion. This project has been tested on the Debian image provided by the lecturer using VirtualBox.

In order to run the server or client, first click "Run"->"Edit Configurations" in the file menu bar. Click on "Application" in the sidebar and for "Target:" choose "atomas_server" and click "OK". The project can now be compiled and run using Clion.

### Contribution guidelines ###

### How to Play ###

To play a single player game, the server does not need to be running. Run the client program from Clion, and when the game interface window opens, click on "1 Player".

A ring of atoms will appear on the screen with the player's atom appearing in the centre. Each turn, the player must move his/her atom to the ring by clicking on an area between two atoms, and his/her atom is replaced by a new one. When a player receives a "+" atom, he/she should move it between two atoms of identical value. This will cause the two atoms to fuse, leaving behind an atom of higher value and points are scored. This process can cause two or more atoms to fuse, creating a combo, thus scoring more points. When a player receives a "-" atom, he/she must click on an atom to delete it from the ring. This is useful for removing atoms with a value or position that is difficult to cause fusion. The game ends when the the atom ring is filled with 24 atoms.

### Known Issues ###

Due to unresolvable issues, the multiplayer game option is incomplete. Currently, the multiplayer allows for two players to play, with each player being able to view the other player's ring, but there is no interaction between the individual games.

Due to the nature of double linked list, it is difficult to have a permanent root node as a reference point. In order to resolve this problem, the use of an additional variable (int index) was used keep track of the relative location of the current root atom. This solved many issues as it allowed for easy location of the atom at index = 0, regardless what the current root atom was pointing at. However, complications arose from the deletion and addition of atoms to/from the ring, which caused the index value to be unreliable. Attempts to resolve all of these issues have not been entirely successful, thus unexpected bugs may appear during gameplay.

For reasons unknown, a client may suddenly go into an non-stop infinite loop as it attempts to read from the server and a likely EOF value is returned. It is suspected that this is due to the TCP connection breaking, as normally, a call to the read function in the client is synchronous, as such it waits for the server to send data before returning. This would not be possible if connected to the server, as the server does not send continuous data to clients (the server waits for messages from clients and forwards them on to other players). This issue was unable to be resolved, and it is possible that it is an issue with the internet connection and not entirely due to the code.