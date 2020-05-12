//
// Created by aluis on 06/05/2020.
//

#include "Rules.h"

#include <utility>
#include "Words.h"
#include "Board.h"

Rules::Rules(){

};

Rules::Rules(int line, int column){
    lines = line;
    columns = column;
}


bool Rules::changeFlag(bool v_flag){
    flag = v_flag;
}

void Rules::currentBoard(vector<vector<char> > board) {
    actual_board = board;
}

void Rules::currentDic(string dic){
    random_dic = dic;
}

void Rules::changeIntersection(bool c_intersection){
    intersection = c_intersection;
}

bool Rules::verifyIntersection(char board_word, char ch_word) {
    b_word = board_word;
    if (counter == 10) { intersection = true; }

    else if (board_word == ch_word) {
        (intersection = true);
        b_word = ' ';
        (intersection_char = true);
        flag_intersection = true;
        return true;
    }

    intersection_char = false;
    flag_intersection = board_word ==' ';
    return  board_word == ' ';
}

bool Rules::forceIntersection(){
    return intersection;
}

bool Rules::verifyLimits(int index_l, int index_c) {
    flag_limits = !(index_c > columns - 1 || index_l > lines - 1);
    return !(index_c > columns - 1 || index_l > lines - 1);
}

bool Rules:: verifySide(int index_l, int index_c, int index, char direction) {
    flag_sides = false;
    bool first_letter = (index == 0);
    bool last_letter =  (index  == word.size()-1);

    if (!intersection_char){
        if (direction == 'H'){
            if (index_l == 0){
                if ( last_letter && index_c != columns - 1 && actual_board[index_l][index_c+1] != ' ') return false; //last_letter &&
                     // is next place empty?
                if ( index_c != columns - 1 && actual_board[index_l+1][index_c] != ' ' && actual_board[index_l+1][index_c+1] != ' ') return false;
                    // next line next column and same one are empty?
                if (first_letter && index_c!= 0 && actual_board[index_l+1][index_c-1]!=' '&& actual_board[index_l+1][index_c]!=' ') return false;
                    // next line last column and same column are empty?
            }
            if (index_l == lines-1){
                if (  first_letter && index_c != 0 && actual_board[index_l][index_c-1] != ' ') return false; //first_letter &&
                    // is last place empty?
                if (index_c!= columns-1 && actual_board[index_l-1][index_c] != ' ' && actual_board[index_l-1][index_c+1] != ' ') return false;
                    // last line same column and next one are empty?
                if(last_letter && actual_board[index_l-1][index_c-1]!=' '&& actual_board[index_l-1][index_c]!=' ') return false;
                    // last line last column and same one are empty?
            }
            if (index_l != 0 && index_l != lines-1){
                if (index_c!=columns-1 && last_letter && (actual_board[index_l][index_c+1] != ' ')) return false; //
                    // next place or last place are empty?
                if (index_c!=0 && first_letter && (actual_board[index_l][index_c-1] != ' ')) return false; //
                    // next place or last place are empty?
                if (index_c!=columns-1 && (actual_board[index_l -1][index_c] != ' ' && actual_board[index_l - 1][index_c + 1] != ' ')) return false;
                    // last line same column and next one are empty?
                if (index_c !=columns-1 && actual_board[index_l + 1][index_c] != ' ' && actual_board[index_l + 1][index_c + 1] != ' ') return false;
                    // next line same column and next one are empty?
                if (first_letter && index_c!=0 ){
                    if(actual_board[index_l-1][index_c-1]!=' '&& actual_board[index_l-1][index_c]!=' ') return false;
                        // last line last column and same one are empty?
                    if (actual_board[index_l+1][index_c-1]!=' '&& actual_board[index_l+1][index_c]!=' ') return false;
                        // next line last column and same one are empty?
                }
            }
        }
        if (direction == 'V') {
            if (index_c == 0) {
                if (last_letter && index_l != lines-1 && actual_board[index_l + 1][index_c] != ' ') return false; //
                    // is next place empty?
                if (index_l != lines-1 && actual_board[index_l][index_c + 1] != ' ' && actual_board[index_l + 1][index_c + 1] != ' ') return false;
                    // next column same line and next one are empty
                if ( first_letter && index_l != 0 && actual_board[index_l][index_c + 1] != ' ' && actual_board[index_l - 1][index_c + 1] != ' ') return false;
                    // next column same line and last one are empty
            }
            if (index_c == columns-1) {
                if (first_letter && index_l != 0 && actual_board[index_l-1][index_c]!= ' ') return false; //
                    // is last place empty?
                if (index_l != lines -1 && actual_board[index_l][index_c - 1] != ' ' && actual_board[index_l + 1][index_c - 1] != ' ') return false;
                    // last column same line and next one are empty
                if (first_letter && index_l != 0 && (actual_board[index_l][index_c - 1] != ' ' && actual_board[index_l - 1][index_c - 1] != ' ')) return false;
                    // last column last line and same one are empty
            }
            if (index_c != 0 && index_c != columns-1) {
                if (first_letter && index_l!=0 && (actual_board[index_l-1][index_c] != ' ')) return false; //
                    // next place or last one are empty?
                if (index_l != lines -1 && last_letter && (actual_board[index_l + 1][index_c] != ' ')) return false; //
                    // next place or last one are empty?
                if (index_l!=lines-1 && actual_board[index_l][index_c - 1] != ' ' && actual_board[index_l + 1][index_c - 1] != ' ') return false;
                    // last column same line and next one are empty
                if (index_l!= lines-1 && actual_board[index_l][index_c + 1] != ' ' && actual_board[index_l + 1][index_c + 1] != ' ') return false;
                    // next columns same line and next one are empty
                if(first_letter and index_l != 0){
                    if(actual_board[index_l][index_c-1]!=' ' && actual_board[index_l-1][index_c-1]!=' ') return false;
                        // last column same line and last one
                    if (actual_board[index_l][index_c+1]!=' ' && actual_board[index_l-1][index_c+1]!=' ') return false;
                        // next columns same line and last one
                }
            }
        }
        }
        flag_sides = true;
        return true;
}

bool Rules::verifyWords() {
    ++counter;
    flag = false;
    int w_size = random_dic.length();

    if (counter < 11) {return true;}

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            int c = 0;
            intersection = false;
            // horizontal
            for (int w = 0; w < w_size; ++w) {
                flag = (verifyLimits(i, j+w) &&
                       verifyIntersection(actual_board[i][j + w], random_dic[w]) &&
                       forceIntersection() && verifySide(i, j+w, w, 'H'));
                //cout << "flags:" <<flag_limits << flag_sides<< flag_intersection << intersection << "idx:" << i << j+w << random_dic[w] << "fim\n";
                if (!flag){//cout << "false\n";
                break;}
                if (flag) ++c;
            }

            /*int d = 0;
            intersection = false;
            // vertical
            for (int w = 0; w < w_size; ++w) {
                if (flag && c==w_size) break;
                flag = (verifyLimits(i+w, j) &&
                        verifyIntersection(actual_board[i+w][j], random_dic[w]) &&
                        forceIntersection() && verifySide(i+w, j, w, 'V'));
                //cout << flag_limits << flag_sides<< flag_intersection << intersection <<  i+w << j;
                if (!flag){//cout << "false\n";
                    break;}
                if (flag) d++;*/
            //}
            if ((flag && c == w_size)) return true; // || (flag && d == w_size))return true;
            else flag = false;
        }
    }
    //vertical
   if (!flag) {
        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < lines; ++j) {
                int c = 0;
                intersection = false;
                for (int w = 0; w < w_size; ++w) {
                    flag = (verifyLimits(j+w, i) &&
                            verifyIntersection(actual_board[j+w][i], random_dic[w]) &&
                            forceIntersection() && verifySide(j+w, i, w, 'V'));
                    //cout << flag_limits << flag_sides<< flag_intersection << intersection <<  i+w << j;
                    if (!flag){//cout << "false\n";
                        break;}
                    if (flag) c++;
                }
                if (flag && c == w_size) return true;
                else flag = false;
            }
            if (flag) break;
        }
    }
    return flag;
}

bool Rules::verifyRules(){
        return( flag_sides && flag_intersection && flag_limits && flag && forceIntersection());

}

void Rules::flagEnd( bool e ){
    the_end = e;
}
bool Rules::finishBoard() {
    return the_end;
}

void Rules::flagAgain(bool a){
    play_again = a;
}
bool Rules::playAgain(){
    if (play_again)counter = 0;
    return play_again;
}