#include "deck.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>

// Hilfsfunktion zum Vergleichen zweier Vektoren als Multiset
static void expectSameMultiset(std::vector<std::string> a,
                               std::vector<std::string> b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    EXPECT_EQ(a, b);
}

TEST(DeckTest, SingleDeckHas52Cards) {
    Deck d(1);
    EXPECT_EQ(d.size(), 52);
}

TEST(DeckTest, MultipleDecksHaveCorrectSize) {
    Deck d2(2);
    EXPECT_EQ(d2.size(), 52 * 2);

    Deck d3(3);
    EXPECT_EQ(d3.size(), 52 * 3);
}

TEST(DeckTest, CardsConstructorKeepsCardsAndDrawIsLifo) {
    std::vector<std::string> cards = {"A♣", "10♦", "K♠"};
    Deck d(cards);

    EXPECT_EQ(d.size(), 3);

    // draw holt vom Ende
    std::string c1 = d.draw();
    std::string c2 = d.draw();
    std::string c3 = d.draw();

    EXPECT_EQ(c1, "K♠");
    EXPECT_EQ(c2, "10♦");
    EXPECT_EQ(c3, "A♣");
    EXPECT_EQ(d.size(), 0);
}

TEST(DeckTest, DrawReducesSize) {
    std::vector<std::string> cards = {"A♣", "K♦"};
    Deck d(cards);

    int startSize = d.size();
    d.draw();
    EXPECT_EQ(d.size(), startSize - 1);
}

TEST(DeckTest, ResetRestoresFullSizeForNumDecks) {
    Deck d(1);
    int fullSize = d.size();

    // ein paar Karten ziehen
    d.draw();
    d.draw();
    EXPECT_LT(d.size(), fullSize);

    // reset baut Deck neu
    d.reset();
    EXPECT_EQ(d.size(), fullSize);
}

TEST(DeckTest, ShuffleKeepsSameCardsForCardsConstructor) {
    std::vector<std::string> original = {"A♣", "2♦", "3♥", "4♠", "K♣"};
    Deck d(original);

    // Deck mischen
    d.shuffle();

    // alle Karten ziehen
    std::vector<std::string> drawn;
    while (d.size() > 0) {
        drawn.push_back(d.draw());
    }

    EXPECT_EQ(drawn.size(), original.size());
    expectSameMultiset(drawn, original);
}
