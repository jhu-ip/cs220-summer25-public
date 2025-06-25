#include <chrono>
#include <fstream>
#include <iostream>

#include "CTrie.h"
#include "WordHunt.h"

using std::cout;
using std::endl;
using namespace std::chrono;

int main() {
    WordHunt wh;
    auto start = high_resolution_clock::now();
    // hard coded file
    wh.load_file("words.txt");
    auto mid = high_resolution_clock::now();
    std::string board = "eaneohndlrrothts";
    wh.setBoard(board);

    wh.solve();
    auto stop = high_resolution_clock::now();
    wh.displayResults();

    auto total = duration_cast<microseconds>(stop - start);
    auto trie_formation = duration_cast<microseconds>(mid - start);
    auto search = duration_cast<microseconds>(stop - mid);

    cout << "Total Time: " << total.count() / 1e6 << " seconds" << endl;

    cout << "Time taken to form Trie: " << trie_formation.count() / 1e6
         << " seconds" << endl;

    cout << "Time taken to search Board: " << search.count() / 1e6 << " seconds"
         << endl;

    return 0;
}
