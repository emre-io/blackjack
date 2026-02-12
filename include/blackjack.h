#pragma once

#include <vector>

#include "deck.h"
#include "player.h"

class Blackjack {
   public:
    Blackjack(Player& dealer, Player& player, Deck& deck);
    void playRound();

   private:
    Player& player;
    Player& dealer;
    Deck& deck;

    void setStake();
    void performPlayerTurn(Player& p, Deck& deck);
    void evaluateResults();
    char readDecision(const Player& p);
};