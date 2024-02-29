#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    /*
     * Function:Basic Constructor
     * Precondition: dictionary.txt
     * Postcondition: initialize a boggle object with dictionary private object loaded from dictionary.txt, wordFounds initialized empty, set board and visited to empty
     */
    Boggle();
    /*
     * Function:explicit Constructor
     * Precondition: file filename
     * Postcondition: initialize a boggle object with dictionary private object loaded from file filename, wordFounds initialized empty, set board and visited to empty
     */
    explicit Boggle(string filename);
    /*
     * Function:Set Board
     * Precondition: board[BOARD_SIZE][BOARD_SIZE], boggle initialized
     * Postcondition: Set private member board to the value of provided board
     */
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);
    /*
     * Function:Solve Board
     * Precondition: boggle initialized, printBoard provided
     * Postcondition: wrapper function for recursion call SolveBoardHelper
     */
    void SolveBoard(bool printBoard, ostream& output);
    /*
     * Function:Save Board
     * Precondition: boggle initialized, filename
     * Postcondition: call save method from dictionary class to save WordsFound into file filename
     */
    void SaveSolve(string filename);   // Saves all the words from the last solve.
    /*
     * Function:get dictionary
     * Precondition: boggle initialized
     * Postcondition: Return dict
     */
    Dictionary GetDictionary();
    /*
     * Function:get wordsFound
     * Precondition: boggle initialized
     * Postcondition: Return WordsFound
     */
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];
    /*
     * Function:print board
     * Precondition: called by SolveBoardHelper when found a word, output provided
     * Postcondition: load board and visited in correct format to output
     */
    void PrintBoard(ostream& output);
    /*
     * Function: solve board recursion
     * Precondition: called by wrapper, or itself, parameters satisfied.
     * Postcondition: call print if found word; return if out bounds, step into a visited plot, or not prefix. check 8 directions clockwise from north
     */
    void SolveBoardHelper( Dictionary &found, Dictionary &ans, int x, int y, string word, int& count, int step, bool& print, ostream &output);
};

#endif //BOGGLE_BOGGLE_H
