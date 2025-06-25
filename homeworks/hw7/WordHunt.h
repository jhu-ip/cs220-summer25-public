#ifndef __WORDHUNT_H__
#define __WORDHUNT_H__

#define GAME_SIZE 4

#include <set>
#include <string>

#include "CTrie.h"

class WordHunt {
   public:
    WordHunt();
    WordHunt(const WordHunt& rhs);
    ~WordHunt();

    WordHunt& operator=(const WordHunt& rhs);

    void load_file(std::string filename);

    void solve();

    void setBoard(std::string& brd);

    void displayResults();

   private:
    CTrie* trie;

    std::map<int, std::vector<std::string>> m_vec;

    std::string board;

    std::set<std::string> words_set;

    void dfs(const CTrie* ct, int idx, int mask, std::string word_so_far,
             int start_coord);
};

#endif