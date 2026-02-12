#include <iostream>
#include <string>
#include <vector>

#include "blackjack.h"
#include "deck.h"
#include "player.h"

int main(int argc, char* argv[]) {
    int num_decks = 1;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--num_decks") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value for --num_decks\n";
                return 1;
            }

            try {
                num_decks = std::stoi(argv[i + 1]);
            } catch (...) {
                std::cerr << "Invalid integer for --num_decks" << std::endl;
                return 1;
            }

            if (num_decks < 1 || num_decks > 20) {
                std::cerr << "num_decks must be between 1 and 20" << std::endl;
                return 1;
            }

            i++;
        }
    }
    std::cout << "Using " << num_decks << " deck(s).\n";

    int budget = 10;
    Player player("Player", budget);
    Player dealer("Dealer", 0);
    Deck deck(num_decks);
    Blackjack blackjack(dealer, player, deck);

    while (player.getBudget() > 0) {
        blackjack.playRound();
    }

    std::cout << "You don't have any budget left. Game is over.\n";
    return 0;
}
