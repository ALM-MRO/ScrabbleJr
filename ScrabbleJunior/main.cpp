#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Clear.h"
#include "Board.h"
#include "Pool.h"
#include "Player.h"
#include "Game.h"
#include "Letter.h"
using namespace std;

int main(){
    srand(time(NULL));

    vector <vector <Letter>> brd_objects;
    vector <Player> players_vec;
    Player winner;
    string name;

    Board board = Board(name);                          // create object board; open board file; build board; insert words
    Pool pool = Pool();                                 // create object pool
    Game game = Game();

    brd_objects = board.getBrd_objects();

    pool.addLettersToPool(brd_objects);                 // include board letters in pool vec (pl)

    game = Game(players_vec, brd_objects, pool);        // update object game

    game.addPlayers();                                  // choose number of players, create Player objects

    cout << "This is your board, the game will start in a few seconds...\n";
   // board.printBoard();
   // _sleep(30000);
    vector <vector<char>> players_options = game.startPlaying();

    winner = game.play(board, players_options);                  // start playing the game
}