#pragma once

#include <string>
#include <vector>

class Deck;

class Player {
   public:
    Player(const std::string& name, int budget);

    void drawFrom(Deck& deck);

    int getHandValue() const;

    std::string handToString() const;
    void showHand() const;
    void showFirstCard() const;
    void resetHand();

    std::string getName() const;

    int getBudget() const;
    void setBudget(int newBudget);
    void showBudget() const;

    int getStake() const;
    void setStake(int newStake);

    bool hasNatural() const;
    void setHasNatural(bool newNatural);

    void giveCard(std::string card);

   private:
    std::string name;
    int budget;
    int stake;
    bool hasNaturalAttribute;
    std::vector<std::string> hand;
};
