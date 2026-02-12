#include "deck.h"

#include <algorithm>
#include <random>

const std::vector<std::string> Deck::RANKS = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const std::vector<std::string> Deck::SUITS = {"♣", "♦", "♥", "♠"};

Deck::Deck(int numDecks) : numDecks(numDecks) {
    buildDeck(numDecks);
    shuffle();
}

Deck::Deck(const std::vector<std::string>& cards) 
    : deck(cards), numDecks(1) {}

void Deck::buildDeck(int numDecks) {
    deck.clear();
    deck.reserve(numDecks * SUITS.size() * RANKS.size());
    for (int i = 0; i < numDecks; ++i) {
        for (const auto& suit : SUITS) {
            for (const auto& rank : RANKS) {
                deck.push_back(rank + suit);
            }
        }
    }
}

int Deck::size() {
    return deck.size();
}

void Deck::reset() {
    buildDeck(numDecks);
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

std::string Deck::draw() {
    std::string card = deck.back();
    deck.pop_back();
    return card;
};
