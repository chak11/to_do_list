//
// Created by chaki on 23/06/2025.
//
#include "gtest/gtest.h"
#include "../date.h"


TEST(DateTest, ConstructorTest) {
    Date date(15, 9, 2000);
    EXPECT_EQ(date.getGiorno(), 15);
    EXPECT_EQ(date.getMese(), 9);
    EXPECT_EQ(date.getAnno(), 2000);
}

TEST(DateTest, DefaultConstructorTest) {
    Date date;
    EXPECT_EQ(date.getGiorno(), 0);
    EXPECT_EQ(date.getMese(), 0);
    EXPECT_EQ(date.getAnno(), 0);
}

TEST(DateTest, IsLeapTest) {
    Date date(15, 9, 2000);
    date.setMese(2);
    date.setGiorno(29);
    ASSERT_EQ(date.getGiorno(), 29);
    Date date2(15, 2, 2003);
    EXPECT_THROW(date2.setGiorno(29), std::out_of_range);
}

TEST(DateTest, GetDaysOfMonthTest) {
    Date date(15, 9, 2000);
    date.setGiorno(30);
    ASSERT_EQ(date.getGiorno(), 30);
    EXPECT_THROW(date.setMese(2), std::out_of_range);
    date.setMese(1);
    date.setGiorno(31);
    ASSERT_EQ(date.getGiorno(), 31);
    date.setAnno(2003);
    date.setGiorno(28);
    date.setMese(2);
    ASSERT_EQ(date.getGiorno(), 28);
}

TEST(DateTest, EqualityOperatorTest) {
    Date d1(10, 7, 2023);
    Date d2(10, 7, 2023);

    ASSERT_TRUE(d1 == d2);
    d2.setGiorno(11);
    ASSERT_FALSE(d1 == d2);
}

TEST(DateTest, InvalidDateTest) {
    EXPECT_THROW(Date date(29, 2, 2023), std::out_of_range);
    EXPECT_THROW(Date date(31, 4, 2023), std::out_of_range);
    EXPECT_THROW(Date date(33, 6, 2023), std::out_of_range);
    EXPECT_THROW(Date date(0, 7, 2023), std::out_of_range);
    EXPECT_THROW(Date date(10, 0, 2023), std::out_of_range);
    EXPECT_THROW(Date date(10, 13, 2023), std::out_of_range);
    EXPECT_THROW(Date date(10, 7, 1000), std::out_of_range);
    EXPECT_THROW(Date date(10, 7, 2200), std::out_of_range);
}

TEST(DateTest, SettersDateTest) {
    Date date(10, 12, 2023);
    EXPECT_THROW(date.setGiorno(340), std::out_of_range);
    EXPECT_THROW(date.setMese(0), std::out_of_range);
    EXPECT_THROW(date.setAnno(30000), std::out_of_range);
    date.setGiorno(15);
    date.setMese(9);
    date.setAnno(2000);
    ASSERT_EQ(date, Date(15, 9, 2000));
}