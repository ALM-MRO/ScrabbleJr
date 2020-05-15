//
// Created by marga on 08/05/2020.
//

#include "Game.h"
#include "Player.h"
#include "Pool.h"
#include "Clear.h"
#include <iostream>
#include <algorithm>

using namespace std;

Game::Game(){
}

Game::Game(vector<Player> players_vec, vector<vector<Letter>> brd_objects, Pool pool){
    this -> players_vec = players_vec;
    this -> brd_objects = brd_objects;
    this -> pool = pool;

};

void Game::addPlayers() {
    int num_players;
    char answer;
    string name, username, move, board_name;
    vector <char> pl;
    vector <vector <char>> brd;
    pl = pool.getPl();
    while (pl.size() < 14) {
        cout << "This board is not suitable to be played in, choose another board.\n";
        cin >> board_name;
    }
    if (pl.size() < 21) {
        cout << "This board is only suitable for a 2-player game, do you wish to continue?(y/n)\n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            num_players = 2;
        //acrescentar reiniciar/escolher outro tabuleiro
    } else if (pl.size() >= 21 && pl.size() < 28) {
        do {
            clear();
            cout << "This board is not suitable for a 4-player game, do you wish to continue?(y/n)\n";
            cin >> answer;
        } while (answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n');
        //acrescentar reiniciar/escolher outro tabuleiro

        do {
            cout << "Number of players(2-3): ";
            cin >> num_players;
        } while (num_players < 2 || num_players > 3);
    }

    do {
        cout << "Number of players(2-4): ";
        cin >> num_players;
    } while (num_players < 2 || num_players > 4);


    for (int i = 0; i < num_players; i++){
        cout << "\nInsert Player " << i + 1 << " username:";
        cin >> username;
        players_vec.push_back(Player(username, 0, pool.shuffleLetters()));
    }
    cout << "\n";
}


vector <vector<char>> Game:: startPlaying(){
    vector<char> pl = pool.getPl();

    vector<char> players_letters;
    vector <vector<char>> players_options;
    players_options.resize(brd_objects.size());

    for (int i = 0; i < brd_objects.size(); i++)
        players_options[i].resize(brd_objects[0].size());

    return players_options;
}

Player Game::play(Board board, vector <vector<char>> players_options) {
    int word_number = board.getWord_number();
    int turn = 0;
    int move_line, move_col;
    int check_possibilities;
    int right = 0;
    int move_number = 0;
    int win = 0;
    int complete_words, pre_complete_words = 0;
    int player_score, num_players;

    char change_let1, change_let2;

    string player_name;
    string move;

    vector<char> player_letters;
    vector <Word> words_vec;

    while (true) {
        clear();
        check_possibilities = 0;
        complete_words = 0;

        move_number = move_number % 2;
        turn %= players_vec.size();

        player_letters = players_vec[turn].getLetters();
        player_name = players_vec[turn].getName();
        player_score = players_vec[turn].getScore();
        num_players = players_vec.size();

        for (int i = 0; i < brd_objects.size(); i++)
            for (int k = 0; k < brd_objects[0].size(); k++)
                players_options[i][k] = 'I';


        for (int i = 0; i < brd_objects.size(); i++)
            for (int k = 0; k < brd_objects[0].size(); k++)
                for (char player_letter : player_letters)                      // for (int l = 0; l < player_letters.size(); l++)
                    if (brd_objects[i][k].getState() == 'P' && brd_objects[i][k].getLet() == player_letter) {
                        players_options[i][k] = 'P';
                        check_possibilities++;
                    }

        board.printBoard(players_options);

        printLettersScores(num_players, player_score);

        if (check_possibilities == 0) {                                         // no letters available to be played
            if (move_number == 0) {
                cout << player_name << "\n,you have no letters available to be played.\n" <<
                " Instead of playing choose 2 letters to exchange.";
                do {
                    cout << "\n1st letter:";
                    cin >> change_let1;
                    for (int l = 0; l < player_letters.size(); l++)
                        if (change_let1 == player_letters[l]) {
                            player_letters.erase(player_letters.begin() + l);
                            right = 1;
                        }
                } while (right != 1);
                clear();
                board.printBoard(players_options);
                printLettersScores(num_players, player_score);
                do {
                    cout << "\n2nd letter: ";
                    cin >> change_let2;
                    for (int l = 0; l < player_letters.size(); l++)
                        if (change_let1 == player_letters[l]) {
                            player_letters.erase(player_letters.begin() + l);
                            right = 0;
                        }
                } while (right != 0);
                player_letters.push_back(pool.getLet());                                          // Add new letter to player's pool and delete it in common pool
                player_letters.push_back(pool.getLet());                                          // x2
                players_vec[turn].setLetters(player_letters);                                     // update object player's letters

            } else {
                cout << player_name << " doesn't have any other move available.\n";

                player_letters.push_back(pool.getLet());
                players_vec[turn].setLetters(player_letters);

                _sleep(5000);
            }

        } else {
            do {
                do {
                    cout << "Make your move " << players_vec[turn].getName() << " (e.g. Be)";
                    cin >> move;
                    move_line = move[0] - 'A';
                    move_col = move[1] - 'a';
                } while (move_line > brd_objects.size() || move_col > brd_objects[0].size());

            } while (players_options[move_line][move_col] != 'P' || move.length() != 2);

            brd_objects[move_line][move_col].setState('F');                                    // Change letter state in Letter class

            board.setBrd_objects(brd_objects);                                           // Update letter state in Board class

            players_options[move_line][move_col] = 'I';                                           // Set state of players_options already filled letter to impossible

            for (int i = 0; i < player_letters.size(); i++)
                if (brd_objects[move_line][move_col].getLet() == player_letters[i]) {
                    player_letters.erase(player_letters.begin() + i);                             // Delete played letter from player's pool
                    break;
                }

            if (move_number == 1) {                                                               // only happens after the second move of each player
                player_letters.push_back(pool.getLet());                                          // Add new letter to player's pool and delete it in common pool
                player_letters.push_back(pool.getLet());                                          // x2
            }
            players_vec[turn].setLetters(player_letters);                                         // update object player's letters

            win =  winner(word_number);

            if (win != 0)
                return players_vec[win-1];

            checkNextLetter(move_line, move_col);
            board.setBrd_objects(brd_objects);

            words_vec = board.getWords_vec();

            for(int i = 0; i < word_number; i++) {
                words_vec[i].changeComplete();
                if (words_vec[i].getComplete())
                    complete_words++;
            }

            player_score += complete_words - pre_complete_words;                                  // update player's score
            players_vec[turn].setScore(player_score);                                             // update player's score in Player class
            pre_complete_words = complete_words;                                                  // update number of completed words

        }

        move_number++;
        if (move_number == 2)
            turn++;
    }
}
void Game::printLettersScores(int num_players, int player_score) {
    for (int i = 0; i < num_players; i++) {
        cout << "\n" << players_vec[i].getName() << "'s letters: ";
        for (int k = 0; k < players_vec[i].getLetters().size(); k++)
            cout << players_vec[i].getLetters()[k] << " ";
        cout << "\t| score = " << player_score;
    }
    cout << "\n\n";
}

void Game::checkNextLetter(int line, int col){

    if (brd_objects[line][col].getIntersection()) {               //when the chosen letter belonged to 2 words
        if (line > 0) {
            if (brd_objects[line - 1][col].getState() == 'E' || brd_objects[line - 1][col].getState() == 'F')
                checkVerticalWord(line, col);
        } else
            checkVerticalWord(line, col);

        if (col > 0) {
           if (brd_objects[line][col - 1].getState() == 'E' || brd_objects[line][col - 1].getState() == 'F')
               checkHorizontalWord(line, col);
        } else
            checkHorizontalWord(line, col);

    } else if (brd_objects[line][col].getWord_direction() == 'V') //when the chosen letter belonged to a vertical word
        checkVerticalWord(line, col);

    else if (brd_objects[line][col].getWord_direction() == 'H')   //when the chosen letter belonged to a horizontal word
        checkHorizontalWord(line, col);

}

void Game::checkVerticalWord(int line, int col) {
    for (int i = line; i < brd_objects.size(); i++) {
        if (brd_objects[i][col].getState() == 'I') {
            for(int k = col; k > 0; k--) {
                if (brd_objects[i][k].getState() == 'E') {
                    brd_objects[i][col].setState('P');
                    break;
                } else if (brd_objects[i][k].getState() == 'I' || brd_objects[i][k].getState() == 'P') {
                    break;
                }
            }
        } else if (brd_objects[i][col].getState() == 'E' || brd_objects[i][col].getState() == 'P')
            break;
    }
}

void Game::checkHorizontalWord(int line, int col) {
    for (int k = col; k < brd_objects[0].size(); k++) {
        if (brd_objects[line][k].getState() == 'I') {
            for(int i = line; i > 0; i--) {
                if (brd_objects[i][k].getState() == 'E') {
                    brd_objects[line][k].setState('P');
                    break;
                } else if (brd_objects[i][k].getState() == 'I' || brd_objects[i][k].getState() == 'P') {
                    break;
                }
            }
        } else if (brd_objects[line][k].getState() == 'E' || brd_objects[line][k].getState() == 'P')
            break;
    }
}

int Game::winner(int word_number){
    vector <int> scores;
    if (players_vec.size() == 2)
        scores = {players_vec[0].getScore(), players_vec[1].getScore()};
    else if (players_vec.size() == 3)
        scores.push_back(players_vec[2].getScore());
    else
        scores.push_back(players_vec[3].getScore());

    int previous = 0, pre_previous = 0, best = 0, second_best = 0;

    for (int i = 0; i < players_vec.size(); i++)
        if (scores[i] > previous) {
            previous = scores[i];
            best = i;
        } else if (scores[i] > pre_previous){
            pre_previous = scores[i];
            second_best = i;
        }

    if (word_number + second_best < 2*best )
        return best + 1;

    return 0;
}