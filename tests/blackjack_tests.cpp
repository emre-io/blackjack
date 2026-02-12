#include "blackjack.h"
#include "player.h"
#include "deck.h"

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// RAII-Helfer, um std::cin temporär umzulenken
struct CinRedirect {
    std::istringstream in;
    std::streambuf* oldBuf;

    explicit CinRedirect(const std::string& data)
        : in(data),
          oldBuf(std::cin.rdbuf(in.rdbuf())) {}

    ~CinRedirect() {
        std::cin.rdbuf(oldBuf);
    }
};

TEST(BlackjackTest, PlayerWinsSimpleRound) {
    Player player("Player", 10);
    Player dealer("Dealer", 0);

    // Player: K♣ + 10♣ = 20
    // Dealer: 9♣ + 9♦ = 18
    std::vector<std::string> cards = {"9♦", "9♣", "10♣", "K♣"};
    Deck deck(cards);

    Blackjack blackjack(dealer, player, deck);

    // Einsatz 5, dann sofort Stand
    CinRedirect redirect("5\nS\n");

    blackjack.playRound();

    // 10 - 5 (Stake) + 2*5 (Auszahlung) = 15
    EXPECT_EQ(player.getBudget(), 15);
}

TEST(BlackjackTest, DealerWinsSimpleRound) {
    Player player("Player", 10);
    Player dealer("Dealer", 0);

    // Player: 10♣ + 7♣ = 17
    // Dealer: 9♣ + 10♦ = 19
    std::vector<std::string> cards = {"10♦", "9♣", "7♣", "10♣"};
    Deck deck(cards);

    Blackjack blackjack(dealer, player, deck);

    CinRedirect redirect("5\nS\n");

    blackjack.playRound();

    // 10 - 5, keine Auszahlung
    EXPECT_EQ(player.getBudget(), 5);
}

TEST(BlackjackTest, DrawSimpleRound) {
    Player player("Player", 10);
    Player dealer("Dealer", 0);

    // Beide: 18
    // Player: 10♣ + 8♣ = 18
    // Dealer: 9♣ + 9♦ = 18
    std::vector<std::string> cards = {"9♦", "9♣", "8♣", "10♣"};
    Deck deck(cards);

    Blackjack blackjack(dealer, player, deck);

    CinRedirect redirect("5\nS\n");

    blackjack.playRound();

    // 10 - 5 + 5 (Stake zurück)
    EXPECT_EQ(player.getBudget(), 10);
}

// Player Natural, Dealer kein Natural -> Player gewinnt
TEST(BlackjackNaturalTest, PlayerNaturalBeatsDealerNonNatural) {
    Player player("Player", 10);
    Player dealer("Dealer", 0);

    // Player: A♣ + K♣ = 21 (Natural)
    // Dealer: 9♣ + 9♦ = 18
    // Reihenfolge im Vektor: c1, c2, c3, c4
    // draw: Player: c4, c3; Dealer: c2, c1
    std::vector<std::string> cards = {"9♦", "9♣", "K♣", "A♣"};
    Deck deck(cards);

    Blackjack blackjack(dealer, player, deck);

    // Einsatz 5, danach keine Entscheidung nötig (Natural)
    CinRedirect redirect("5\n");

    blackjack.playRound();

    // Budget: 10 - 5 + 2*5 = 15
    EXPECT_EQ(player.getBudget(), 15);
    EXPECT_TRUE(player.hasNatural());
    EXPECT_FALSE(dealer.hasNatural());
}

// Dealer Natural, Player kein Natural -> Dealer gewinnt
TEST(BlackjackNaturalTest, DealerNaturalBeatsPlayerNonNatural) {
    Player player("Player", 10);
    Player dealer("Dealer", 0);

    // Player: 9♣ + 9♦ = 18
    // Dealer: A♣ + K♣ = 21 (Natural)
    std::vector<std::string> cards = {"A♣", "K♣", "9♦", "9♣"};
    Deck deck(cards);

    Blackjack blackjack(dealer, player, deck);

    CinRedirect redirect("5\n");

    blackjack.playRound();

    // Budget: 10 - 5, keine Auszahlung
    EXPECT_EQ(player.getBudget(), 5);
    EXPECT_FALSE(player.hasNatural());
    EXPECT_TRUE(dealer.hasNatural());
}

// Beide Naturals -> Unentschieden, Stake zurück
TEST(BlackjackNaturalTest, BothNaturalsResultInDraw) {
    Player player("Player", 10);
    Player dealer("Dealer", 0);

    // Player: A♣ + K♣ = 21
    // Dealer: A♦ + K♦ = 21
    std::vector<std::string> cards = {"A♦", "K♦", "K♣", "A♣"};
    Deck deck(cards);

    Blackjack blackjack(dealer, player, deck);

    CinRedirect redirect("5\n");

    blackjack.playRound();

    // Budget: 10 - 5 (Stake), bei Draw +5 zurück => 10
    EXPECT_EQ(player.getBudget(), 10);
    EXPECT_TRUE(player.hasNatural());
    EXPECT_TRUE(dealer.hasNatural());
}