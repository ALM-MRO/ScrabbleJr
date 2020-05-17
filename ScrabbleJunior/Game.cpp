//
// Created by marga on 08/05/2020.
//

#include "Game.h"
#include "Player.h"
#include "Pool.h"
#include "common.h"
#include "Board.h"

#include <iostream>
#include <algorithm>
#include <concrt.h>

using namespace std;

Game::Game(){
}

Game::Game(Pool pool, Board* board) {
    this -> pool = pool;      // object pool of class Pool
    this -> board = board;    // pointer to object board (of class Board)
    flag_end_of_game = false; // turns true if game has ended, breaking while loop
    resizePlayers_options();
}

void Game::resizePlayers_options() {
    players_options.resize(board->getBrd().size());
    for (int i = 0; i < board->getBrd().size(); i++)
        players_options[i].resize(board -> getBrd()[0].size());
}

bool Game::addPlayers() {
    unsigned int num_players = 0;
    int max_players = 4;
    string answer =  " ";
    string name, username, board_name;
    int players_colors[4] = {LIGHTBLUE, LIGHTMAGENTA, YELLOW, GREEN};   // define players' colors

    if (pool.getPl().size() < 28){                                      // if board has less than 28 letters
        do {                                                            // can't be used by more than 3 players
            clear();                                                    // asks user if they want to proceed or quit
            cout << SUITABLE_BOARD;
            if (pool.getPl().size() >= 21 && pool.getPl().size() < 28) cout << "2/3";
            else cout << "2";
            cout << PROCEED;
            cin >> answer;
            if (answer == "N" || answer == "n")                          // ends game
                return true;
            max_players = pool.getPl().size() >= 21 && pool.getPl().size() < 28 ? 3 : 2;
            num_players = pool.getPl().size() >= 21 && pool.getPl().size() < 28 ? 4 : 2;
        } while (answer != "y" && answer != "Y");
    }

    while (num_players < 2 || num_players > max_players) {              // inserting number of players
        clear();
        cout << "Number of players(2-" << max_players << "): ";
        cin >> num_players; clearCin();
    }

    for (int i = 0; i < num_players; i++){                              // inserting players names
        clear();
        setColor(players_colors[i],BLACK);
        cout << "\nInsert Player " << i + 1 << " name:";
        cin >> username;
        players_vec.push_back(Player(username, 0, pool.shuffleLetters(), players_colors[i]));
        setColor(WHITE, BLACK);
    }
    cout << "\n";
    return false;
}

void Game::play() {
    int word_number = board -> getWord_number();
    int turn = 0, move_number = 0, check_possibilities;
    int num_changed_letters, num_letters_to_change;
    pre_complete_words = 0;
    char change_let;
    vector <char> player_letters;
    vector <Word > word_vec = board -> getWords_vec();
    vector <char> aux_new_letters;

    while (true) {
        num_changed_letters = 0; // number of letters that have been
        complete_words = 0;
        move_number = move_number % 2;  // checks if it is the first or the second move for each player
        turn %= players_vec.size();     // chooses which is the current player to make a move

        player_letters = players_vec[turn].getLetters();
        check_possibilities = updatePlayers_options(player_letters); // if 0 it means the player has no move available

        clear();
        printLettersScores();                              // prints letters & scores
        board->printBoard(players_options);   // prints the board

        if (check_possibilities == 0) {
            // no letters available to be played
            if (move_number == 0 && pool.getPl().size() > 0) {
                // first move for this player & letters in pool can be exchanged
                printNoMoveAvailable(turn);

                num_letters_to_change = pool.getPl().size() > 1 ? 2 : 1;
                aux_new_letters.resize(num_letters_to_change);

                for (int i = 0; pool.getPl().size() > 0 && i < num_letters_to_change; i++) // get new letter(s) from pool and
                    aux_new_letters[i] = pool.getLet();                                    // delete them in common pool

                do { // send unwanted letters to pool
                    cout <<  " Letter " << num_changed_letters + 1 << ":";
                    cin >> change_let; clearCin();
                    for (int i = 0; i < player_letters.size(); i++)
                        if (change_let == player_letters[i]) {
                            pool.sendLetterToPool(player_letters[i]);
                            player_letters.erase(player_letters.begin() + i);
                            num_changed_letters++;
                            break;
                        }
                } while(num_changed_letters < num_letters_to_change);

                for (int i = 0; pool.getPl().size() > 0 && i < num_letters_to_change; i++) // Add new letter(s) to player's pool and
                    player_letters.push_back(aux_new_letters[i]);                          // delete it in common pool

                players_vec[turn].setLetters(player_letters);                              // update object player's letters
                clear();                                                                   // clear console
                board->printBoard(players_options);                           // prints board
                printLettersScores();                                                      // prints letters & scores
                move_number++;  // increments move_number because 2 moves are made at the same time

            } else {
                // second move for this player OR letters in pool can't be exchanged (0 letters in pool)

                setColor(players_vec[turn].getColor(), BLACK);
                cout << players_vec[turn].getName();
                setColor(WHITE, BLACK);
                cout << OUT_OF_MOVES;
                Concurrency::wait(3000);

                if (!pool.getPl().empty()) player_letters.push_back(pool.getLet()); // if pool is not empty get letter from pool
                players_vec[turn].setLetters(player_letters);                       // update player's letters in players_vec
            }
        } else {
            // there are letters available to be played by the current player
            getMove(turn);

            board -> fillLetter(move_line, move_col);                     // update letter state in Board class

            for (int i = 0; i < player_letters.size(); i++)               // delete played letter from player's pool
                if (board -> getBrd()[move_line][move_col].getLet() == player_letters[i]) {
                    player_letters.erase(player_letters.begin() + i);
                    break;
                }
            if (move_number == 1)                                         // only happens after the second move of each player
                for (int i = 0; pool.getPl().size() > 0 && i < 2; i++)
                    player_letters.push_back(pool.getLet());              // add new letter to player's pool and delete it in common pool
            players_vec[turn].setLetters(player_letters);                 // update object player's letters

            addPointsToPlayer(word_number, word_vec, turn, move_line, move_col); // updates player's score

            if (flag_end_of_game)  //ends game when all words are complete
                break;
        }
        move_number++;             // increments move number by 1
        if (move_number == 2)      // if player has completed to moves in a row turn is passed to the next player
            turn++;
    }
}

void Game::printNoMoveAvailable(int turn){
    setColor(players_vec[turn].getColor(), BLACK);
    cout << "\n" << players_vec[turn].getName();
    setColor(WHITE, BLACK);
    cout << NO_LETTERS_AVAILABLE;   // how many letters can be exchanged
    cout << (pool.getPl().size() > 1 ? " 2 letters " : " 1 letter ") << "to exchange.";
}

void Game::getMove(int turn){
    string move;
    move_line = 0;
    move_col = 0;
    do { // move input has to: be a string with length = 2; refer to an existing
        do { // index of line and column which is set as possible to be played in
            setColor(players_vec[turn].getColor(), BLACK);
            cout << players_vec[turn].getName();
            setColor(WHITE, BLACK);
            cout << MAKE_MOVE;
            cin >> move;
            move_line = move[0] - 'A';
            move_col = move[1] - 'a';
        } while (move_line > board -> getBrd().size() || move_col > board -> getBrd()[0].size());
    } while (players_options[move_line][move_col] != 'P' || move.length() != 2);
}

int Game::updatePlayers_options(vector <char> player_letters){
    int check_possibilities = 0;

    for (int i = 0; i < board -> getBrd().size(); i++) {         // resets players_options so it can be used by
        for (int k = 0; k < board->getBrd()[0].size(); k++)      // multiple players
            players_options[i][k] = 'I';
    }

    for (int i = 0; i < board -> getBrd().size(); i++) {         // sets players options to 'P' (possible) if the
        for (int k = 0; k < board->getBrd()[0].size(); k++)      // player has letters that are set has available
            for (char player_letter : player_letters)            // to be played in the board
                if (board->getBrd()[i][k].getState() == 'P' && board->getBrd()[i][k].getLet() == player_letter) {
                    players_options[i][k] = 'P';
                    check_possibilities++;
                }
    }
    return check_possibilities;
}

void Game::printLettersScores() {
    for (Player p : players_vec) {
        setColor(p.getColor(), BLACK);
        cout << "\n Score: " << p.getScore() << " | " << p.getName() << "'s letters: ";
        for (int k = 0; k < p.getLetters().size(); k++)
            cout << p.getLetters()[k] << " ";
    }
    setColor(WHITE, BLACK);
}

void Game::addPointsToPlayer(int word_number, vector <Word> word_vec, int turn, int line, int col){
    complete_words = 0;
    for (int i = 0; i < word_number; i++) {                                      // get number of completed words
        word_vec[i].updateComplete();
        if (word_vec[i].getComplete())
            complete_words++;
    }

    int score_diff = complete_words - pre_complete_words;                        // check if new words were completed
    players_vec[turn].setScore(players_vec[turn].getScore() + score_diff);    // update player's score in Player
    pre_complete_words = complete_words;                                         // update number of completed words

    if (complete_words == word_number) {
        players_options[line][col] = 'I';
        clear();
        board->printBoard(players_options);
        endGame();
        flag_end_of_game = true;
    }
}

void Game::endGame() {
    int draw = 1;
    int i = 1;
    Player temp;
    bool swapped = true;

    while(swapped){
        swapped = false;
        for (size_t j = 0; j < players_vec.size() - 1; j++)
            if (players_vec[j].getScore() < players_vec[j+1].getScore()){
                temp = players_vec[j];
                players_vec[j] = players_vec[j + 1];
                players_vec[j + 1] = temp;
                swapped = true;
            }
    }

    while(i < players_vec.size() && players_vec[i++].getScore() == players_vec[0].getScore())
        draw++;

    clear();

    for (size_t j = 0; j < players_vec.size(); j++)
        cout << "\n" << players_vec[j].getName() << "'s score: " << players_vec[j].getScore();

    if (draw > 1) {
        cout << "\n\nThe winners are:\n";
        for (int k = 0; k < draw - 1; k++) {
            setColor(players_vec[k].getColor(), BLACK);
            cout << "-> "<<players_vec[k].getName() << "\n";
        }
        setColor(WHITE, BLACK);
    } else {
        cout << "\nThe winner is ";
        setColor(players_vec[0].getColor(), BLACK);
        cout << players_vec[0].getName();
        setColor(WHITE, BLACK);
        cout << "!!";
    }
    cout <<"\n";
    Concurrency::wait(3000);
}