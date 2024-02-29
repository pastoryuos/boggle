#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg = "ERROR";
};

class Dictionary
{

public:
    /*
     * Function:Basic Constructor
     * Precondition: none
     * Postcondition: initialize empty dictionary with root
     */
    Dictionary();
    /*
     * Function:Destructor
     * Precondition: dictionary initialized
     * Postcondition: call helper to delete tree
     */
    ~Dictionary();
    /*
     * Function: copy dictionary Constructor
     * Precondition: parameter satisfied
     * Postcondition: initialize dictionary copied from provided dictionary
     */
    Dictionary(const Dictionary& otherDict);
    /*
     * Function:explicit Constructor
     * Precondition: parameter satisfied
     * Postcondition: initialize dictionary copied from provided file using copyother funct
     */
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.
    /*
     * Function: overload assign operator
     * Precondition: parameter satisfied
     * Postcondition: return dictionary copied from provided file using copyother funct
     */
    Dictionary& operator=(const Dictionary& otherDict);
    /*
     * Function: load dictionary wrapper
     * Precondition: parameter satisfied, dictionary initialized
     * Postcondition: wrapper for load helper until no more input from files
     */
    void LoadDictionaryFile(string filename);
    /*
     * Function: save dictionary wrapper
     * Precondition: parameter satisfied, dictionary initialized
     * Postcondition: wrapper for recursion call save helper
     */
    void SaveDictionaryFile(string filename);
    /*
     * Function: addwoord
     * Precondition: parameter satisfied, dictionary initialized
     * Postcondition: change the isWord at required node to true, follow path provided by word
     */
    void AddWord(string word);
    /*
     * Function: empty dictionary wrapper
     * Precondition: dictionary not empty
     * Postcondition: return if empty, otherwise call destroyHelper recursion to delete all nodes
     */
    void MakeEmpty();
    /*
     * Function: check Isword
     * Precondition: parameter satisfied, dictionary initialized
     * Postcondition: return IsWord at location provided by path word
     */
    bool IsWord(string word);
    /*
     * Function: Is it prefix?
     * Precondition: parameter satisfied, dictionary initialized
     * Postcondition: return false if node at end of followed path has all child set to nullptr, true if at least 1 is not.
     */
    bool IsPrefix(string word);
    /*
     * Function: get wordcount
     * Precondition: dictionary initialized
     * Postcondition: return numWords
     */
    int WordCount();  // Returns total number of words in dictionary

private:

    class Node {
    public:
        Node* child[NUM_CHARS];
        bool isWord;
        /*
         * Function: Basic Constructor
         * Precondition: none
        * Postcondition: initialize node with NUM_CHARS amount of child, all childs set to nullptr, isWord is false
         */
        Node(){
            isWord = false;
            for (int i = 0; i< NUM_CHARS; i++){
                child[i] = nullptr;
            }
        }
    };

    Node* root;
    int numWords;

    // This function is used by the
    // copy constructor and the assignment operator.
    /*
     * Function: copy wrapper
     * Precondition: parameter satisfied, dictionary initialized, this->root != otherDict->root
     * Postcondition: return if same root, empty current dict, call recursion until all word from otherDict is loaded.
     */
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.
    /*
     * Function: destroy recursion
     * Precondition: thisTree != nullptr
     * Postcondition: return if at nullptr, call recursion for each child, delete current node and set it to nullptr
     */
    void destroyHelper(Node* thisTree);
    /*
     * Function: copy recursion
     * Precondition: thisTree != otherTree
     * Postcondition: return if same node, check each child, create child or destroy child if needed, use otherTree as build guide for thisTree, call recursion to each child
     */
    void copyHelper(Node*& thisTree, Node* otherTree);
    /*
     * Function: save recursion
     * Precondition: parameter satisfied, cur != nullptr
     * Postcondition: return if nullptr, save currPrefix to file if isWord, call recursion to each child
     */
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
    /*
     * Function: load helper
     * Precondition: parameter satisfied
     * Postcondition: use word as path to set IsWord at end of path to true
     */
    void LoadDictionaryHelper(Node* curr, string word, ifstream& inFile);
};

#endif //BOGGLE_DICTIONARY_H
