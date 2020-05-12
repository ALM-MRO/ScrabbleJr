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
    file_word.createFile();
    boardSize();
    printBoard();
    readFile();
    validation = Rules(lines,columns);
    validation.flagEnd(false);
}

void Board::boardSize() {
    cout << "Choose the size of the board you wish to build.\n" << "Lines(5-20):";
    cin >> lines;
    while (cin.fail() || lines < 5 || lines > 20){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout << "Choose again (5-20):";
        cin >> lines;
    }
    cout << "\nColumns(5-20):";
    cin >> columns;
    while (cin.fail() || columns < 5 || columns > 20){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout << "Choose again (5-20):\n";
        cin >> columns;
    }

    resetBoard(lines, columns);
    file_word.sizeBoardFile(lines, columns);
}

void Board::resetBoard(int lines, int columns){
    cout << "\nThis is your initial board.\n";
    board.resize(lines);
    for (int i = 0; i < lines; i++)
        board[i].resize(columns);

    for (int i = 0; i < lines; i++)
        for (int k = 0; k < columns; k++)
            board[i][k] = ' ';
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

    if(word_size == 0)
        cout <<"\n\nHere is a list of 10 words from where you may choose one to place on the board.\n"; // ask Phil
    else
        cout <<"\n\nList of available words:\n";

    if (count_letter > 13){
        cout << "0) finish the board\n";
    }

    while(i < 10) { //choosing 10 random words from dictionary
        random_number = rand() % dic_size;
        validation.currentDic(dictionary[random_number]);
        for (auto & c: dictionary[random_number]) c = toupper(c);
        if (validation.verifyWords()) {
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
    cout << "11) choose your own word\n" ;
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
    cout << "\nEnter the number of the word you chose (1-10) or 11 if you want to write a word that it's not in the list\n";}
    else {cout << "\nEnter 1-10 to choose a word from the list, 11 to write your word or 0 to end the board\n";}

    cin >> chosen_index;
    validation.currentBoard(board);

    if (count_letter < 13) {
        while (cin.fail() || chosen_index < 1 || chosen_index > 11) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Please, enter a number between 1 and 11.\n";
            cin >> chosen_index;
        }
    } else {
        while (cin.fail() || chosen_index < 0 || chosen_index > 11) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Please, enter a number between 0 and 11.\n";
            cin >> chosen_index;
        }
    }

    if (chosen_index == 0) { // perguntar a margarida se organizaçao desta função está bem ou separar por idx
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
        validation.flagEnd(true);
        char again;
        cout << "\nDo you want to build another board? (Y/N)\n";
        cin >> again;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Enter 'Y' if you want to play again";
                cin >> again;
            }
            validation.flagAgain(again == 'y' || again == 'Y');
        }
        if (answer == 'n' || answer == 'N') { choosingInfo(); }


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
            cout << "Your word is invalid. Choose again:\n";
            choosingIndex();
        }
    } else {
        chosen_index--; // changing from position to index
        chosen_word = temporary_words[chosen_index];
    }
}

void Board::choosingInfo() {
    cout << "Chosen word: '" << chosen_word << "'" << endl;
    cout << "Now you may choose the position where the first letter will be placed. " << endl << "Line (uppercase):" ;
    cin >> pos_y;
    while ( cin.fail() || pos_y > lines + 'A' - 1 || pos_y < 65 ) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please, enter a valid line:";
        cin >> pos_y;
    }
    cout << "Column (lowercase):" ;
    cin >> pos_x;

    while ( cin.fail() || pos_x > columns + 'a' - 1  || pos_x < 97 ) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please, enter a valid column: ";
        cin >> pos_x;
    }

    cout << "And now choose the direction(H or V): ";
    cin >> dir;

    while ( cin.fail() || ((dir != 'H' && dir != 'h')&& (dir != 'V' && dir != 'v')) ) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please, enter a valid direction (H or V):";
        cin >> dir;
    }
}

void Board::changeBoard(){
    int s = chosen_word.size();
    //validation.counter++; //-- to validate not intersecting in first word placed --//
    validation.changeIntersection(false);
    bool flag = false;

    if (dir == 'H'|| dir =='h'){
        for (idx = 0; idx < s; idx++) {
            flag  = false;
            if (!validation.verifyLimits(pos_y - 'A',pos_x - 'a' + idx))
                {cout << "\n(The word is overcoming the limits of the board)\n" ; break;}

            if (!validation.verifyIntersection(board[pos_y - 'A'][pos_x - 'a' + idx],chosen_word[idx]))
                {cout << "\n(The word is not intersecting other words in places that have the same letter)\n"; break;}

            if(!validation.verifySide(pos_y - 'A',pos_x - 'a' + idx, idx, 'H'))
                {cout << "\n(The word cannot have anny letter around it, except for those in which intersect other words)\n"; break;}

            validation.forceIntersection();
            flag = true;
        }
        validation.changeFlag(flag);

        if(validation.verifyRules()){
            for (idx = 0; idx < s; idx++) {
                if (board[pos_y - 'A'][pos_x - 'a' + idx] == ' '){
                    board[pos_y - 'A'][pos_x - 'a' + idx] = chosen_word[idx];
                }
            }
        }
    }

    if (dir == 'V' || dir == 'v'){
        for (idx = 0; idx < s; idx++) {
            flag = false;
            if (!validation.verifyLimits(pos_y - 'A' + idx, pos_x - 'a'))
                {cout << "\n(The word is overcoming the limits of the board)\n" ; break;}

            if (!validation.verifyIntersection(board[pos_y - 'A' + idx][pos_x - 'a'],chosen_word[idx]))
                {cout << "\n(The word is not intersecting other words in places that have the same letter)\n"; break;}

            if (!validation.verifySide(pos_y - 'A' + idx,pos_x - 'a',idx,'V'))
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
    }
    if (!validation.forceIntersection()){cout << "(The word has to be intersected in at least one letter)\n";}

    if (validation.verifyRules()){
        file_word.writeInFile(pos_x, pos_y, dir, chosen_word );
    }
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
}
