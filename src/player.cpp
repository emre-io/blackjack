#include "player.h"

#include <iostream>

#include "card_rules.h"
#include "deck.h"

Player::Player(const std::string& name, int budget) : name(name), budget(budget) {
    stake = 0;
    hasNaturalAttribute = false;
}

void Player::drawFrom(Deck& deck) {
    if (deck.size() == 0) {
        std::cout << "Deck has reached zero cards. Deck is reset and shuffled.\n";
        deck.reset();
        deck.shuffle();
    }
    hand.push_back(deck.draw());
}

int Player::getHandValue() const {
    int total = 0, aces = 0;
    for (const std::string& card : hand) {
        std::string rank = card_rules::extract_rank(card);
        int value = card_rules::rank_value(rank);
        total += value;
        if (rank == "A") ++aces;
    }

    while (total > 21 && aces > 0) {
        total -= 10;
        --aces;
    }
    return total;
}

std::string Player::handToString() const {
    std::string hand_str = "";
    for (const std::string& card : hand) {
        hand_str += card + " ";
    }
    if (!hand_str.empty()) hand_str.pop_back();
    return hand_str;
}

void Player::showHand() const {
    std::cout << name << "'s hand: " << handToString() << "\n";
}

void Player::showFirstCard() const {
    std::cout << name << "'s hand: " << hand.at(0) << "\n";
}

void Player::resetHand() {
    hand.clear();
}

std::string Player::getName() const {
    return name;
}

int Player::getBudget() const {
    return budget;
}

void Player::setBudget(int newBudget) {
    budget = newBudget;
}

void Player::showBudget() const {
    std::cout << name << "'s budget: " << budget << "\n";
}

int Player::getStake() const {
    return stake;
}

void Player::setStake(int newStake) {
    stake = newStake;
}

void Player::setHasNatural(bool newHasNatural) {
    hasNaturalAttribute = newHasNatural;
}

bool Player::hasNatural() const {
    return hasNaturalAttribute;
}

void Player::giveCard(std::string card) {
    hand.push_back(card);
}