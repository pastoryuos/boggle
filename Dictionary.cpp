#include "Dictionary.h"



Dictionary::Dictionary() {
    root = new Node;
    Node* cur = root;
    numWords = 0;
}

Dictionary::~Dictionary() {
    MakeEmpty();
}

int Dictionary::WordCount() {
    return numWords;
}

void Dictionary::AddWord(string word) {
    Node* cur = root;

    //traversing the tree
    for (int i = 0; i < word.size(); i++){
        int j = int(word[i]) - 97; //take advantage of the ascii of 'a' being 0x97
        if (j < 0 || j>NUM_CHARS){
            throw DictionaryError("Invalid character");
        }
        if (cur->child[j] == nullptr){
            cur->child[j] = new Node;
        }
        cur = cur->child[j];

    }
    cur->isWord = true;
    numWords++;
}

bool Dictionary::IsWord(string word) {
    //presume we only store lower case char, ill need to implement to lower if we allow custom char save
    if (numWords < 0) {
        throw DictionaryError("ERROR");
    }

    Node* cur = root;

    //traversing the tree
    for (int i = 0; i < word.size(); i++){
        int j = int(word[i]) - 97; //take advantage of the ascii of 'a' being 0x97
        if (cur->child[j] == nullptr) {
            return false;
        }
        cur = cur->child[j];

    }

    return cur->isWord;
}

bool Dictionary::IsPrefix(string word) {
    if (numWords < 0) {
        throw DictionaryError("ERROR");}

    Node* cur = root;

    //traversing the tree
    for (int i = 0; i < word.size(); i++){
        int j = int(word[i]) - 97; //take advantage of the ascii of 'a' being 0x97
        if (cur->child[j] == nullptr){
            return false;
        }
        cur = cur->child[j];

    }

        //as long as there is a child node not nullptr
    for (int i = 0; i < NUM_CHARS; i++){
        if (cur->child[i] != nullptr){
            return true;
        }
    }
    return false;

}

void Dictionary::MakeEmpty() {
    if (numWords ==0){
        return;
    }

    destroyHelper(root);
    root = new Node;
    //delete cur;
    numWords =0;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if(thisTree == nullptr){
        return;
    }
        for (int i = 0; i < NUM_CHARS; i++) {

            destroyHelper(thisTree->child[i]);
        }
        delete thisTree;
        thisTree = nullptr;
}


Dictionary::Dictionary(string filename) {
    root= new Node;

    numWords = 0;
    LoadDictionaryFile(filename);
}


void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {

    if (curr ==nullptr){
        return;
    }
    if (curr->isWord){
        outFile << currPrefix << endl;
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        SaveDictionaryHelper(curr->child[i], currPrefix+char(i+97), outFile);
    }


}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream dictFile;
    dictFile.open(filename);
    if (!(dictFile.is_open())){
        throw DictionaryError("ERROR");
    }
    // Notice we start with the empty string as the prefix.
    SaveDictionaryHelper(root, "", dictFile);
}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream dictFile;
    dictFile.open(filename);
    if (!(dictFile.is_open())){
        throw DictionaryError("ERROR");
    }

    string word;
    while(dictFile >> word){
        LoadDictionaryHelper(root, word, dictFile);
    }
}

void Dictionary::LoadDictionaryHelper(Dictionary::Node *curr, string word, ifstream &inFile) {

    for (int i = 0; i<word.length(); i++){
        int j = word[i] -97;
        if (curr->child[j] == nullptr){
            curr->child[j] = new Node;
        }
        curr = curr->child[j];
    }
    //if word already added
    if (curr->isWord){
        return;
    }
    curr->isWord= true;
    numWords++;
}

Dictionary::Dictionary(const Dictionary &otherDict) {
    root= new Node;

    numWords = 0;
    copyOther(otherDict);
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    copyOther(otherDict);
    return *this;
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    if (this->root == otherDict.root){
        return;
    }
    this->MakeEmpty(); //destructor already set numword to 0

    while(this->numWords<otherDict.numWords){
        copyHelper(this->root, otherDict.root);
    }
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if (otherTree == nullptr){
        return;
    }
    for (int i = 0; i< NUM_CHARS; i++){
        if (otherTree->child[i] == nullptr){
            continue; //check each child, if all children are null (not prefix), end for loop and return to last recursion call [recursion out]
        }
        thisTree->child[i] = new Node; //build child nodes
        if (otherTree->child[i]->isWord){
            thisTree->child[i]->isWord = true; //get words, if isword
            this->numWords++;
        }
        copyHelper(thisTree->child[i], otherTree->child[i]); //recursion in
    }
}

