#include "player.h"
#include "deck.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(PlayerTest, EmptyHandHasValueZero) {
    Player p("Player", 100);
    EXPECT_EQ(p.getHandValue(), 0);
}

TEST(PlayerTest, HandValueWithoutAcesIsSumOfCards) {
    Player p("Player", 100);
    p.giveCard("10♣");
    p.giveCard("7♦");

    EXPECT_EQ(p.getHandValue(), 17);
}

TEST(PlayerTest, SingleAceActsAsElevenIfNoBust) {
    Player p("Player", 100);
    p.giveCard("A♣");
    p.giveCard("7♦");

    EXPECT_EQ(p.getHandValue(), 18);
}

TEST(PlayerTest, AceDowngradesToOneToAvoidBust) {
    Player p("Player", 100);
    p.giveCard("A♣");
    p.giveCard("9♦");
    p.giveCard("9♥");

    // 11 + 9 + 9 = 29 -> Ace wird zu 1 -> 19
    EXPECT_EQ(p.getHandValue(), 19);
}

TEST(PlayerTest, MultipleAcesAreHandledCorrectly) {
    Player p("Player", 100);
    p.giveCard("A♣");
    p.giveCard("A♦");
    p.giveCard("9♥");

    // 11 + 11 + 9 = 31 -> ein Ass zu 1: 21
    EXPECT_EQ(p.getHandValue(), 21);
}

TEST(PlayerTest, HandToStringFormatsCardsWithSpaces) {
    Player p("Player", 100);
    p.giveCard("K♣");
    p.giveCard("A♦");
    p.giveCard("10♥");

    EXPECT_EQ(p.handToString(), "K♣ A♦ 10♥");
}

TEST(PlayerTest, ResetHandClearsCardsAndValue) {
    Player p("Player", 100);
    p.giveCard("10♣");
    p.giveCard("7♦");

    ASSERT_GT(p.getHandValue(), 0);

    p.resetHand();

    EXPECT_EQ(p.getHandValue(), 0);
    // Wenn du eine getHandSize-Funktion hast:
    // EXPECT_EQ(p.getHandSize(), 0);
}

TEST(PlayerTest, BudgetAndStakeSettersAndGettersWork) {
    Player p("Player", 100);

    p.setBudget(50);
    EXPECT_EQ(p.getBudget(), 50);

    p.setStake(10);
    EXPECT_EQ(p.getStake(), 10);
}

TEST(PlayerTest, NaturalFlagCanBeSetAndQueried) {
    Player p("Player", 100);

    EXPECT_FALSE(p.hasNatural());

    p.setHasNatural(true);
    EXPECT_TRUE(p.hasNatural());

    p.setHasNatural(false);
    EXPECT_FALSE(p.hasNatural());
}

// Test für drawFrom mit Test-Deck
TEST(PlayerTest, DrawFromAddsCardFromDeckToHand) {
    std::vector<std::string> cards = {"A♣", "K♦"};
    Deck d(cards);  // nutzt deinen Test-Konstruktor

    Player p("Player", 100);
    p.drawFrom(d);

    // Deck zieht von hinten, also K♦ zuerst
    EXPECT_EQ(p.handToString(), "K♦");
    EXPECT_EQ(d.size(), 1);
}
