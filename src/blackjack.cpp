#include "blackjack.h"

#include <iomanip>
#include <iostream>
#include <limits>

#include "deck.h"
#include "player.h"

Blackjack::Blackjack(Player& dealer, Player& player, Deck& deck)
    : player(player), deck(deck), dealer(dealer) {
    player.setHasNatural(false);
    dealer.setHasNatural(false);
};

void Blackjack::setStake() {
    int budget = player.getBudget();
    int stake = 0;

    std::cout << "Type in your stake 1 - " << budget << "." << std::endl;

    while (true) {
        if (!(std::cin >> stake)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Type an integer." << std::endl;
            continue;
        }

        if (stake > 0 && stake <= budget) {
            break;
        }

        std::cout << "Type a valid stake between 1 and "
                  << budget << "." << std::endl;
    }

    player.setBudget(budget - stake);
    player.setStake(stake);
}

char Blackjack::readDecision(const Player& p) {
    char decision;
    std::cout << p.getName() << ": Hit H or Stand S? " << std::endl;

    while (true) {
        if (!(std::cin >> decision)) {
            std::cout << "Input error. Aborting turn.\n";
            return 'S';  // konservativ: stehen
        }

        if (decision == 'H' || decision == 'h' ||
            decision == 'S' || decision == 's') {
            return decision;
        }

        std::cout << "Did not understand. Type again: " << std::endl;
    }
}

void Blackjack::performPlayerTurn(Player& p, Deck& deck) {
    while (true) {
        int value = p.getHandValue();

        if (value > 21) {
            std::cout << p.getName() << " lost with " << value << ".\n";
            return;
        }

        if (value == 21) {
            std::cout << p.getName() << " has 21 and stands automatically.\n";
            return;
        }

        char decision = readDecision(p);

        if (decision == 'S' || decision == 's') {
            std::cout << p.getName() << " stands with " << value << ".\n";
            return;
        }

        p.drawFrom(deck);
        p.showHand();
    }
}

void Blackjack::evaluateResults() {
    std::cout << std::left
              << std::setw(15) << "Name"
              << std::setw(10) << "Payment"
              << std::setw(10) << "Profit"
              << std::setw(10) << "Budget"
              << "\n";

    int playerValue = player.getHandValue();
    int dealerValue = dealer.getHandValue();

    bool playerBeatsDealer =
        (playerValue <= 21 && dealerValue > 21) ||
        (playerValue <= 21 && dealerValue <= 21 && playerValue > dealerValue);

    bool dealerBeatsPlayer =
        (dealerValue <= 21 && playerValue > 21) ||
        (dealerValue <= 21 && playerValue <= 21 && dealerValue > playerValue);

    if (playerBeatsDealer) {
        player.setBudget(player.getBudget() + 2 * player.getStake());
        std::cout << std::left
                  << std::setw(15) << player.getName()
                  << std::setw(10) << 2 * player.getStake()
                  << std::setw(10) << player.getStake()
                  << std::setw(10) << player.getBudget()
                  << "\n";

        std::cout << "Player has won " << player.getHandValue() << " points.\n";
    } else if (dealerBeatsPlayer) {
        std::cout << std::left
                  << std::setw(15) << player.getName()
                  << std::setw(10) << 0
                  << std::setw(10) << 0
                  << std::setw(10) << player.getBudget()
                  << "\n";

        std::cout << "Dealer has won with " << dealer.getHandValue() << " points.\n";
    } else {  // draw
        player.setBudget(player.getBudget() + player.getStake());
        std::cout << std::left
                  << std::setw(15) << player.getName()
                  << std::setw(10) << player.getStake()
                  << std::setw(10) << 0
                  << std::setw(10) << player.getBudget()
                  << "\n";

        std::cout << "It is a draw.\n";
    }
}

void Blackjack::playRound() {
    setStake();

    player.drawFrom(deck);
    player.drawFrom(deck);

    // Check if player has a natural.
    if (player.getHandValue() == 21) {
        player.showHand();
        std::cout << "Player has a Natural.\n";
        player.setHasNatural(true);
    } else {
        player.showHand();
    }

    dealer.drawFrom(deck);
    dealer.drawFrom(deck);

    // Check if dealer has a natural.
    if (dealer.getHandValue() == 21) {
        std::cout << "Dealer has a Natural.\n";
        dealer.showHand();
        dealer.setHasNatural(true);
        // If dealer has not a natural and player has a natural.
    } else if (player.hasNatural()) {
        dealer.showHand();
    } else {
        dealer.showFirstCard();  // Second card covered, if not natural.
    }

    bool oneHasNatural = dealer.hasNatural() || player.hasNatural();
    
    if (!oneHasNatural) {
        performPlayerTurn(player, deck);

        // Dealer draws until 17 or more.
        dealer.showHand();
        while (dealer.getHandValue() < 17) {
            dealer.drawFrom(deck);
            dealer.showHand();
        }
        std::cout << dealer.getName() << " stands with " << dealer.getHandValue() << "." << std::endl;

        if (dealer.getHandValue() > 21) {
            std::cout << "Dealer is over 21.\n";
        }
    }

    evaluateResults();

    player.resetHand();
    dealer.resetHand();
    player.setHasNatural(false);
    dealer.setHasNatural(false);
}
