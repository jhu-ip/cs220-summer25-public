#include "WordHunt.h"

#include <assert.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

WordHunt::WordHunt() : trie(new CTrie()) {}

WordHunt::WordHunt(const WordHunt& rhs) : trie(new CTrie(*rhs.trie)) {}

WordHunt::~WordHunt() { if (trie) delete trie; }

WordHunt& WordHunt::operator=(const WordHunt& rhs) {
  if (this != &rhs) {
    if (trie) delete trie;
    trie = new CTrie(*rhs.trie);
  }
  return *this;
}

// load the file
void WordHunt::load_file(std::string filename) {
    std::ifstream file(filename);

    std::string word;
    while (file >> word) {
        *trie += word;
    }
}

// set the board string to the object
void WordHunt::setBoard(std::string& brd) {
    assert(brd.length() == 16);

    this->board = brd;
}

// dfs method to find all the links.
void WordHunt::dfs(const CTrie* ct, int idx, int mask, std::string word_so_far,
                   int start_coord) {
    // if it is the end of a word, then add to the vector and the set of words
    // found so far.
    if (ct->isEndpoint() && words_set.find(word_so_far) == words_set.end()) {
        this->m_vec[start_coord].push_back(word_so_far);
        words_set.insert(word_so_far);
    }

    // the node does not have any children, then return.
    if (!ct->hasChild()) {
        return;
    }
    int next_idx, new_row, new_col;
    // iterate through all the positions
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            new_row = idx / GAME_SIZE + x;
            new_col = idx % GAME_SIZE + y;

            // if out of bounds or in same place
            if (new_row < 0 || new_row >= GAME_SIZE || new_col < 0 ||
                new_col >= GAME_SIZE || !(x || y)) {
                continue;
            }

            // flatten index
            next_idx = GAME_SIZE * new_row + new_col;

            // if not already accessed and has a child with that particular
            // letter, then recurse.
            if (!(mask & (1 << next_idx)) &&
                ct->hasChild(this->board[next_idx])) {
                const CTrie* next_ct = ct->getChild(this->board[next_idx]);
                mask |= (1 << next_idx);
                this->dfs(next_ct, next_idx, mask,
                          word_so_far + board[next_idx], start_coord);
            }
        }
    }
}

// solve the board, by going through all the variables.
void WordHunt::solve() {
    // go through all the starting tiles, if it can start with that letter, then
    // recurse.
    for (int i = 0; i < (int)this->board.length(); i++) {
        if (this->trie->hasChild(this->board.at(i))) {
            const CTrie* ct = this->trie->getChild(this->board.at(i));
            int mask = (1 << i);
            std::string word_so_far;
            word_so_far = this->board.at(i);
            this->dfs(ct, i, mask, word_so_far, i);
        }
    }
}

// priint out the results.
void WordHunt::displayResults() {
    std::map<int, std::vector<std::string>>::iterator it;
    int row, col;
    for (it = this->m_vec.begin(); it != m_vec.end(); ++it) {
        row = it->first / GAME_SIZE;
        col = it->first % GAME_SIZE;
        std::cout << "( " << row << ", " << col << " ) : ";

        for (std::string word : it->second) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
}
