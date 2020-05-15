//
// Created by marga on 08/05/2020.
//

#ifndef UNTITLED13_GAME_H
#define UNTITLED13_GAME_H

#include "Pool.h"
#include "Player.h"
#include "Letter.h"

#include <vector>

class Game {
    std::vector<Player> players_vec;
    std::vector<std::vector<Letter>> brd_objects;
    Pool pool;
public:
    Game();
    Game(std::vector<Player> players_vec, std::vector<std::vector<Letter>> brd_objects, Pool pool);
    void addPlayers();
    std::vector <std::vector<char>> startPlaying();
    Player play(Board board, std::vector <std::vector<char>> players_options);
    int winner(int word_number);
    void checkNextLetter(int move_line, int move_col);
    void checkVerticalWord(int line, int col);
    void checkHorizontalWord(int line, int col);
    void printLettersScores(int num_players, int player_score);
};


#endif //UNTITLED13_GAME_H
