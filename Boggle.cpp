
#include "Dictionary.h"
#include "Boggle.h"

// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}


Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");
    for (int i = 0; i< BOARD_SIZE; i++){
        for (int j = 0; j< BOARD_SIZE; j++){
            board[i][j] = "";
            visited[i][j] = 0;
        }
    }
}

Boggle::Boggle(string filename) {
    dict.LoadDictionaryFile(filename);
    for (int i = 0; i< BOARD_SIZE; i++){
        for (int j = 0; j< BOARD_SIZE; j++){
            board[i][j] = "";
            visited[i][j] = 0;
        }
    }
}

void Boggle::SetBoard(string b[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i< BOARD_SIZE; i++){
        for (int j = 0; j< BOARD_SIZE; j++){
            board[i][j] = b[i][j];
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    int c = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {

            int s=0;
            bool e = false;
            for (int x = 0; x < BOARD_SIZE; x++) {
                for (int y = 0; y < BOARD_SIZE; y++) {
                    visited[x][y]=0;
                }
            }
            SolveBoardHelper(wordsFound, dict, i, j, "", c, s,printBoard, output);
        }
    }

}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (visited[i][j] == 0) {
                output << "  " << board[i][j] << "  ";
            } else {
                output << " '" << board[i][j] << "' ";
            }
        }
        output << "\t";
        for (int j = 0; j < BOARD_SIZE; j++) {
            output << "  " << visited[i][j] << "  ";
        }
        output << endl;
    }
    output << endl;
}

void Boggle::SolveBoardHelper( Dictionary &found, Dictionary &ans, int x, int y, string word, int &count, int step, bool& print, ostream &output) {
    step++;
    //move y then move x, y is row and x is collum


    if (x<0||y<0||x>=BOARD_SIZE||y>=BOARD_SIZE){
        return;
    }
    if (visited[x][y] != 0){
        return;
    }
    word+=board[x][y];
    if (ans.IsWord(word)){
        visited[x][y] = step;
        if (!found.IsWord(word)){
            found.AddWord(word);
            count++;
            if (print) {
                output << "Word: "<< word << endl;
                output << "Number of Words: " << count <<endl;
                PrintBoard(output);
            }
            else{
                output << count << "\t" << word << endl;
            }
        }

    }
    if (!(ans.IsPrefix(word))){ //base case
        if (ans.IsWord(word)){
            visited[x][y]=0; //picking up crumbs
        }
        return;
    }
        visited[x][y] = step; //lay down crumbs


    SolveBoardHelper(found, ans, x - 1, y, word, count, step,print, output); //north

    SolveBoardHelper(found, ans, x - 1, y + 1, word, count, step,print, output); //ne

    SolveBoardHelper(found, ans, x, y + 1, word, count, step,print, output); //east

    SolveBoardHelper(found, ans, x + 1, y + 1, word, count, step,print, output); //se

    SolveBoardHelper(found, ans, x + 1, y, word, count, step,print, output); //south

    SolveBoardHelper(found, ans, x + 1, y - 1, word, count, step,print, output); //sw

    SolveBoardHelper(found, ans, x, y-1, word, count, step, print, output); //west

    SolveBoardHelper(found, ans, x - 1, y - 1, word, count, step,print, output); //nw


        visited[x][y]=0; //picking up crumbs

}







