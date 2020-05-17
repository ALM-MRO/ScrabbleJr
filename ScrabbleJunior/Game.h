//
// Created by marga on 08/05/2020.
//

#ifndef UNTITLED13_GAME_H
#define UNTITLED13_GAME_H

#include "Pool.h"
#include "Player.h"
#include "Letter.h"
#include "Board.h"

#include <vector>

class Game {
    std::vector<Player> players_vec;
    std::vector<std::vector<char>> players_options;
    Pool pool;
    Board* board;
    bool flag_end_of_game;
    int complete_words;
    int pre_complete_words;
    int move_line;
    int move_col;
public:
    // constructors
    Game();
    Game(Pool pool, Board* board);

    // functions

    /*
     * resizes players_options according to chosen board's size
     */
    void resizePlayers_options();

    /*
     * informs user of how many players can play with the chosen board
     * offers chance to end the game
     * receives number of players and their names as inputs
     * assigns each player different a color
     */
    bool addPlayers();


    void play();

    /*
 * returns check_possibilities
 * updates players_options for the current player
 */
    int updatePlayers_options(std::vector <char> player_letters);
    void printNoMoveAvailable(int turn);
    void getMove(int turn);
    void printLettersScores();
    void addPointsToPlayer(int word_number, std::vector <Word > word_vec, int turn, int line, int col);
    void endGame();
   
};


#endif //UNTITLED13_GAME_H
