#pragma once
#include <stdexcept>

namespace card_rules {

inline int rank_value(std::string& rank) {
    // accepts "A", "K", "Q", "J", "10", "2"..."9"
    if (rank.size() == 2 && rank[0] == '1' && rank[1] == '0')
        return 10;

    switch (rank.empty() ? '\0' : rank[0]) {
        case 'A':
            return 11;
        case 'K':
        case 'Q':
        case 'J':
            return 10;
        case '9':
            return 9;
        case '8':
            return 8;
        case '7':
            return 7;
        case '6':
            return 6;
        case '5':
            return 5;
        case '4':
            return 4;
        case '3':
            return 3;
        case '2':
            return 2;
        default:
            throw std::invalid_argument("Unknown rank.");
    }
}

inline std::string extract_rank(std::string card) {
    if (card.find("10") == 0)
        return std::string(card.substr(0, 2));
    return std::string(card.substr(0, 1));
}

} 