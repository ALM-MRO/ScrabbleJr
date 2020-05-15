//
// Created by marga on 05/05/2020.
//

#include "Board.h"
#include "Word.h"
#include "Colors.h"
#include "Player.h"
#include "Pool.h"
#include "Letter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Board::Board(string name){
    this -> name = name;
    readBoardFile();
}

Board::Board(string name, int lines, int columns, int players,vector<vector<Letter>> brd_objects, int word_number, vector<Word> words_vec){
    this -> name = name;
    this -> lines = lines;
    this -> columns = columns;
    this -> players = players;
    this -> brd_objects = brd_objects;
    this -> word_number = word_number;
    this -> words_vec = words_vec;
}

void Board::buildBoard(){
    brd_objects.resize(lines);
    for (int i = 0; i < lines; i++) {
        brd_objects[i].resize(columns);
    }
    for (int i = 0; i < lines; i++)
        for (int k = 0; k < columns; k++) {
            brd_objects[i][k] = Letter(i, k, ' ', ' ', 'E', false);
        }
}

void Board::readBoardFile(){
    word_number = 0;
    string srg;
    int count = 0;
    ifstream filestream("Board1.txt");
    vector<char> word_vec;
    char line, column, direction, aux;
    int len;
    stringstream ss;
    if (filestream.is_open()) {
        while (getline(filestream, srg)){
            if (count == 0) {
                ss = stringstream(srg);
                ss >> lines >> aux >> columns;
                buildBoard();
            } else {
                line = srg[0];
                column = srg[1];
                direction = srg[3];
                len = srg.length();
                word_vec.resize(len - 5);

                for (int i = 5; i < len; i++)
                    word_vec[i - 5] = srg[i];

                insertWord(word_vec, line, column, direction);
            }
            count++;
        }

    } else cout << "Failed to open the file";



}

void Board::insertWord(vector <char> word_vec, char line, char column, char direction){
    int l, c;
    bool intersection;
    vector <Letter*> letters_vec;
    l = line - 'A';
    c = column - 'a';

    for (int i = 0; i < word_vec.size() ; i++) {

        intersection = brd_objects[l][c].getLet() != ' ';

        if (brd_objects[l][c].getState() == 'P')
            brd_objects[l][c].setIntersection(true);

        if (i == 0) {
            brd_objects[l][c] = Letter(l, c, word_vec[i], direction, 'P', intersection);
        } else if (brd_objects[l][c].getState() != 'P'){
            brd_objects[l][c] = Letter(l, c, word_vec[i], direction, 'I', intersection);
        }

        letters_vec.push_back(&brd_objects[l][c]);

        if (direction == 'H') c++;
        else l++;

    }

    words_vec.push_back(Word(letters_vec, line, column, direction));

    word_number++;

}

void Board::printBoard(vector <vector<char>> players_options){
    setColor(YELLOW, BLACK);
    cout << "  ";
    for (int i = 0; i < columns ; i++){
        cout << "  " << char('a' + i);
    }
    cout << "  ";
    for (int i = 0; i < lines ; i++) {
        setColor(YELLOW, BLACK);
        cout << "\n " << char(65 + i) << " ";

        for (int k = 0; k < columns; k++) {
            /*
            if (brd_objects[i][k].getState() == 'P') setColor(GREEN, WHITE);
            */
            if (players_options[i][k] == 'P') {
                setColor(GREEN, WHITE);
            }else if (brd_objects[i][k].getState() == 'F') {
                setColor(RED, WHITE);
            } else
                setColor(BLACK, WHITE);

            cout << " " << brd_objects[i][k].getLet() << " ";
        }
    }
    setColor(GREEN, BLACK);
    cout << "\n   Temporary & Available: Green";
    setColor(RED, BLACK);
    cout << "\n   Permanent: Red\n";
    setColor(WHITE, BLACK);
}






//setters & getters

int Board::getWord_number(){
    return word_number;
}

vector<vector<Letter>> Board::getBrd_objects(){
    return brd_objects;
}


void Board::setBrd_objects(vector <vector <Letter>> new_brd){
    brd_objects = new_brd;
}

vector <Word> Board::getWords_vec(){
    return words_vec;
}