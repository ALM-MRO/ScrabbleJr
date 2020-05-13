//
// Created by aluis on 04/05/2020.
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include<vector>
#include<stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
#include "Board.h"
#include "Colors.h"
#include "Words.h"
#include "Rules.h"
#include <map>
#include <stdio.h>

using namespace std;

Board::Board(){
    file_word = Words();
    boardSize();
    printBoard();
    readFile();
    validation = Rules(lines,columns);
    validation.flagEnd(false);
}

void Board::boardSize() {
    cout << "Enter the name you want to give your file (example: Board):\n";
    cin >> file_name;

    cout << "Choose the size of the board you wish to build.\n"<<
    "Number of lines(5-20):";
    cin >> lines;
    while (cin.fail() || lines < 5 || lines > 20) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Choose again (5-20):";
        cin >> lines;
    }
    cout << "Number of columns(5-20):";
    cin >> columns;
    while (cin.fail() || columns < 5 || columns > 20) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Choose again (5-20):\n";
        cin >> columns;
    }

    resetBoard(lines, columns);
    file_word.sizeBoardFile(lines, columns);
}
/*void Board::chooseIntersection(){
    char chose_intersection;
    cout << "Do you want the words on the board to be all intersected? (Y / N)\n";
    cin >> chose_intersection;
    while (cin.fail() || (chose_intersection != 'Y' && chose_intersection != 'y'
            && chose_intersection != 'n' && chose_intersection != 'N')) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Enter 'Y' or 'N':\n";
        cin >> columns;
    }
    if (chose_intersection == 'n' || chose_intersection == 'N') { validation.dontIntersect(true);}
    else validation.dontIntersect(false);

}*/
void Board::resetBoard(int lines, int columns){

    cout << "\nThis is your initial board.\n";

    board.resize(lines);

    for (int i = 0; i < lines; i++){
        board[i].resize(columns);
        for (int k = 0; k < columns; k++)
            board[i][k] = ' ';
    }
}

void Board::readFile(){
    string srg;
    size = max(lines, columns);
    ifstream filestream("WORDS.TXT");
    if (filestream.is_open()) {
        while (getline(filestream, srg)){
            if ( srg.size() <= size && srg.size()>1 ){
                dictionary.push_back(srg);
            }
        }
    }
    else cout << "Failed to open the file";
}

void Board::listOfWords(){
    validation.currentBoard(board);
    chosen_index = 12;
    bool same_word = false;
    int word_size = chosen_word.size();
    int dic_size = dictionary.size();
    int i = 0;

    cout << endl;
    if (count_letter > 13){
        cout << "-1) finish the board\n";
    }

    cout << "0) exit\n";
    if(word_size == 0)
        cout <<"\nHere is a list of 10 words from where you may choose one to place on the board.\n"; // ask Phil
    else
        cout <<"\nList of words:\n";

    int random_times=0;
    while(i < 10) { //choosing 10 random words from dictionary

        random_number = rand() % dic_size;
        random_times ++;
        validation.currentDic(dictionary[random_number]);
        for (auto & c: dictionary[random_number]) c = toupper(c);
        if (validation.verifyWordsList()) {
            if (random_times > 10000){ //VERIFICAR SE É NECESSÁRIO
                cout << "Our dictionary has no more available words to put on this board\n";
                if (i == 0){validation.flagEnd(true);}
                else break;
            }
            for (int j = 0; j < i; j++){
                if (temporary_words[j]==dictionary[random_number]) { // make sure words list has no repeated words
                    same_word = true;
                    break;
                }
            }

            if(!same_word){
                temporary_words[i] = dictionary[random_number];
                cout << i + 1 << ") ";
                cout << temporary_words[i] << "\n";
                i++;
            }
            same_word = false;
        }
    }
    cout << "\n11) choose your own word\n" ;
    validation.changeFlag(false);
}

bool Board::findWordDic(string u_word) {
    int d_size = dictionary.size();
    for (int i = 0; i < d_size; i++){
        if (dictionary[i] == u_word){return true;}
    }
    return false;
}

void Board::choosingIndex() {
    if (count_letter < 14){
    cout << "\nEnter the number of the word you chose (1-10), 11 if you want to write a word that it's not in the list, or 0 if you want to leave the program.\n";}
    else {cout << "\nEnter 1-10 to choose a word from the list, 11 to write your word, -1 to end the board, or 0 to exit.\n";}

    cin >> chosen_index;
    validation.currentBoard(board);

    if (count_letter < 13) {
        while (cin.fail() || chosen_index < 0 || chosen_index > 11) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Please, enter a number between 0 and 11.\n";
            cin >> chosen_index;
        }
    } else {
        while (cin.fail() || chosen_index < -1 || chosen_index > 11) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Please, enter a number between -1 and 11.\n";
            cin >> chosen_index;
        }
    }

    if (chosen_index == -1) {
        char answer;
        if (count_letter < 21) {
            cout << "Are you sure you want to finish the board? This board only allows 2 players.";
        }
        if (count_letter < 28 && count_letter > 20) {
            cout << "Are you sure you want to finish the board? This board only allows 3 players.";
        }
        if (count_letter > 28) { cout << "Are you sure you want to finish the board?"; }

        cout << "(Y or N)\n";
        cin >> answer;

        while (cin.fail() || ((answer != 'Y' && answer != 'y') && (answer != 'N' && answer != 'n'))) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " Please, answer 'Y' or 'N";
            cin >> answer;
        }

        if (answer == 'y' || answer == 'Y') { cout << "\nThis is your final board:\n";
        printBoard();
        file_word.createFile(file_name);
        validation.flagEnd(true);
        char again;
        cout << "\nDo you want to build another board? (Y/N)\n";
        cin >> again;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Enter 'Y' if you want to play again or 'N' if you want to exit.";
                cin >> again;
            }
            validation.flagAgain(again == 'y' || again == 'Y');
        }
        if (answer == 'n' || answer == 'N') { choosingIndex(); }


    }

    if (chosen_index == 0) {
        char exit_aswer;
        cout << "\nAre you sure you want to exit? (Y / N)\n";
        cin >> exit_aswer;
        while (cin.fail() || (exit_aswer != 'Y' && exit_aswer != 'y' && exit_aswer!= 'n' && exit_aswer!= 'N')) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Enter 'Y' or 'N'.";
            cin >> exit_aswer;
        }
        if (exit_aswer == 'Y'||exit_aswer == 'y'){validation.flagEnd(true);}
        else choosingIndex();

    }

    if (chosen_index == 11) {
        cout << "Write your word:\n";
        cin >> user_word;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Write your word again:\n";
            cin >> user_word;
        }
        if (findWordDic(user_word)) {
            for (auto &u: user_word) u = toupper(u);
            chosen_word = user_word;
        } else {
            cout << "Your word does not belong to our dictionary. Choose again:\n";
            choosingIndex();
        }
    } else {
        chosen_index--; // changing from position to index
        chosen_word = temporary_words[chosen_index];
    }
}

void Board::choosingInfo() {
    cout << "Chosen word: '" << chosen_word << "'" << endl;
    cout << "Now you may choose the position where the first letter will be placed. " << endl << "Line (uppercase):\n" ;
    cin >> pos_y;
    while ( cin.fail() || pos_y > lines + 'A' - 1 || pos_y < 65 ) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please, enter a valid line:\n";
        cin >> pos_y;
    }
    cout << "Column (lowercase):\n" ;
    cin >> pos_x;

    while ( cin.fail() || pos_x > columns + 'a' - 1  || pos_x < 97 ) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please, enter a valid column:\n ";
        cin >> pos_x;
    }

    cout << "And now choose the direction(H or V):\n ";
    cin >> dir;

    while ( cin.fail() || ((dir != 'H' && dir != 'h')&& (dir != 'V' && dir != 'v')) ) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please, enter a valid direction (H or V):\n";
        cin >> dir;
    }
    if (dir == 'h') dir = 'H';
    if (dir == 'v') dir = 'V';

}

void Board::changeBoard(){
    int s = chosen_word.size();
//    validation.changeIntersection(false);
    bool flag = false;
    int x =  0, y = 0;

    for (idx = 0; idx < s; idx++) {
            if (dir == 'H') x = idx;
            if (dir == 'V') y = idx;
            flag  = false;

            if (!validation.verifyLimits(pos_y - 'A'+ y,pos_x - 'a' + x))
                {cout << "\n(The word is overcoming the limits of the board)\n"; break;}

            if (!validation.verifyIntersection(board[pos_y - 'A'+y][pos_x - 'a' + x],chosen_word[idx], idx))
                {cout << "\n(The word is intersecting other words in places that have not the same letter)\n"; break;}

            if(!validation.verifySide(pos_y - 'A'+y,pos_x - 'a' + x, idx, dir,s))
                {cout << "\n(The word cannot have anny letter around it, except for those in which intersect other words)\n"; break;}

//            validation.forceIntersection();
            flag = true;

    }
    validation.changeFlag(flag);

    if(validation.verifyRules()){
        for (idx = 0; idx < s; idx++) {
            if (dir == 'H') x = idx;
            if (dir == 'V') y = idx;
            if (board[pos_y - 'A'+ y][pos_x - 'a' + x] == ' '){
                board[pos_y - 'A'+ y][pos_x - 'a' + x] = chosen_word[idx];
            }
        }
    }

    //if (!validation.forceIntersection()){cout << "(The word has to be intersected in, at least, one letter)\n";}

    if (validation.verifyRules())
        file_word.writeInFile(pos_x, pos_y, dir, chosen_word );

    /*if (dir == 'V' || dir == 'v'){
        for (idx = 0; idx < s; idx++) {
            flag = false;
            if (!validation.verifyLimits(pos_y - 'A' + idx, pos_x - 'a'))
                {cout << "\n(The word is overcoming the limits of the board)\n" ; break;}

            if (!validation.verifyIntersection(board[pos_y - 'A' + idx][pos_x - 'a'],chosen_word[idx]))
                {cout << "\n(The word is not intersecting other words in places that have the same letter)\n"; break;}

            if (!validation.verifySide(pos_y - 'A' + idx,pos_x - 'a',idx,'V',s))
                {cout << "\n(The word cannot have anny letter around it, except for those in which intersect other words)\n"; break;}

            validation.forceIntersection();
            flag = true;
        }
        validation.changeFlag(flag);
        if(validation.verifyRules()){
            for (idx = 0; idx < s; idx++) {
                if (board[pos_y - 'A' + idx][pos_x - 'a'] == ' '){
                    board[pos_y - 'A' + idx][pos_x - 'a'] = chosen_word[idx];
                }
            }
        }
    }*/
}


void Board::printBoard(){
    count_letter = 0;

    cout <<"\n";
    setColor(YELLOW, BLACK);
    cout << "  ";
    for (int i = 0; i < columns ; i++){
        cout << "  " << char('a' + i);
    }
    cout << "  ";

    for (int i = 0; i < lines ; i++) {
        setColor(YELLOW, BLACK);
        cout << "\n " << char(65 + i) << " ";
        setColor(BLACK, LIGHTGRAY);
        for (int k = 0; k < columns; k++){
            cout << " " << board[i][k] << " ";
            if (board[i][k]!=' ') count_letter++;
        }
    }

    setColor(WHITE, BLACK);
    cout << endl;
}

Rules Board::getValidation() {
    return validation;
}