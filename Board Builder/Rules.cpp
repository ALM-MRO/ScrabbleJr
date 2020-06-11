//
// Created by aluis on 06/05/2020.
//

#include "Rules.h"
#include <fstream>
#include <utility>
#include "Words.h"
#include "Board.h"

Rules::Rules(){
    flag = false;
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

//void Rules::changeIntersection(bool c_intersection){
    //intersection = c_intersection;
//}

//bool Rules::dontIntersect(bool choose_intersection){
   // no_intersect = choose_intersection;
//}

bool Rules::verifyIntersection(char board_word, char ch_word,int idx) {
    if (idx == 0) (keep_idx = -2);
    //if (counter == 10) { intersection = true;}
    if (board_word == ch_word) {
        (intersection = true);
        intersection_char = true;
        if  (idx == keep_idx + 1){
            intersection_char = false;
            return false;
        }
        keep_idx = idx;
        flag_intersection = true;
        return true;
    }
    intersection_char = false;
    flag_intersection = board_word ==' ';
    return  board_word == ' ';
}

//bool Rules::forceIntersection(){
    //return true;}

bool Rules::verifyLimits(int index_l, int index_c) {
    flag_limits = !(index_c > columns - 1 || index_l > lines - 1);
    return !(index_c > columns - 1 || index_l > lines - 1);
}

bool Rules:: verifySide(int index_l, int index_c, int index, char direction, int word_size) {
    flag_sides = false;
    bool first_letter = (index == 0);
    bool last_letter =  (index  == word_size-1);
    if (direction == 'H'){
        if (index_c != columns-1 && last_letter && (actual_board[index_l][index_c+1] != ' ')) return false; //
        if (index_c != 0 && first_letter && (actual_board[index_l][index_c-1] != ' ')) return false;
        if (!intersection_char){
            if (index_l == 0 && actual_board[index_l+1][index_c] != ' ') return false;
            if (index_l == lines-1 && actual_board[index_l-1][index_c] != ' ')return false;
            if ((index_l != 0 && index_l != lines-1) &&
            ( actual_board[index_l-1][index_c] != ' ' || actual_board[index_l+1][index_c] != ' ' )) return false;
        }
    }
    if (direction == 'V') {
        if (first_letter && index_l!=0 && (actual_board[index_l-1][index_c] != ' ')) return false;
        if (index_l != lines -1 && last_letter && (actual_board[index_l + 1][index_c] != ' ')) return false;
        if (!intersection_char) {
                if (index_c == 0 && actual_board[index_l][index_c + 1] != ' ') return false; //aurea
                if (index_c == columns - 1 && actual_board[index_l][index_c - 1] != ' ') return false;
                if ((index_c != 0 && index_c != columns - 1) &&
                (actual_board[index_l][index_c + 1] != ' ' || actual_board[index_l][index_c - 1] != ' ')) return false;
        }
    }
    flag_sides = true;
    return true;
}

bool Rules::verifyWordsList() {
    ++counter;
    flag = false;
    int w_size = random_dic.length();

    if (counter < 11) {return true;}

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            int c = 0;
            //intersection = false;
            // horizontal
            for (int w = 0; w < w_size; ++w) {
                flag = (verifyLimits(i, j+w) &&
                       verifyIntersection(actual_board[i][j + w], random_dic[w],w)
                       && verifySide(i, j+w, w, 'H', w_size));
                //cout << "flags:" <<flag_limits << flag_sides<< flag_intersection << intersection << "idx:" << i << j+w << random_dic[w] << "fim\n";
                if (!flag){break;}
                if (flag) ++c; // rules need to be valid in all of the letters
            }

            if ((flag && c == w_size)) return true;//&& intersection )) return true; // || (flag && d == w_size))return true;
            else flag = false;
        }
        if (flag) break;
    }
    //vertical
   if (!flag) {
        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < lines; ++j) {
                int c = 0;
                //intersection = false;
                for (int w = 0; w < w_size; ++w) {
                    flag = (verifyLimits(j+w, i) &&
                            verifyIntersection(actual_board[j+w][i], random_dic[w], w)
                            && verifySide(j+w, i, w, 'V',w_size));
                    if (!flag){break;}
                    if (flag) c++;
                }
                if (flag && c == w_size ) return true;//&& intersection) return true;
                else flag = false;
            }
            if (flag) break;
        }
    }
    return flag;
}

bool Rules::verifyChosenWord(int pos_x, int pos_y, char dir, string word) {

}

bool Rules::verifyRules(){
        return( flag_sides && flag_intersection && flag_limits && flag );//&& forceIntersection());

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