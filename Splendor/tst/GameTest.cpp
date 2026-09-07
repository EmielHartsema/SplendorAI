#include <gtest/gtest.h>

#include <Game.hpp>

TEST(GameTest, StartsWithTwoPlayers)
{
    Game game;

    EXPECT_EQ(game.getNumberOfPlayers(), 2);
}