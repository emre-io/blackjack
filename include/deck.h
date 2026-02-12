#pragma once

#include <string>
#include <vector>

class Deck {
   public:
    Deck(int numDecks);
    Deck(const std::vector<std::string>& cards);
    
    void buildDeck(int numDecks);
    std::string draw();
    void reset();
    void shuffle();
    int size();

   private:
    static const std::vector<std::string> RANKS;
    static const std::vector<std::string> SUITS;
    std::vector<std::string> deck;
    int numDecks;
};
