//
// Created by chaki on 30/06/2025.
//
#include "gtest/gtest.h"
#include "../SubTask.h"

TEST(SubTaskTest, ConstructorAndGetters) {
    SubTask s("Fare la spesa", false);
    EXPECT_EQ(s.getDescrizione(), "Fare la spesa");
    EXPECT_FALSE(s.isCompletato());

    SubTask s2("Pulire casa", true);
    EXPECT_EQ(s2.getDescrizione(), "Pulire casa");
    EXPECT_TRUE(s2.isCompletato());
}

TEST(SubTaskTest, SetCompletato) {
    SubTask s("Studiare", false);
    EXPECT_FALSE(s.isCompletato());

    s.setCompletato(true);
    EXPECT_TRUE(s.isCompletato());

    s.setCompletato(false);
    EXPECT_FALSE(s.isCompletato());
}
