/**
 * @file LevelTest.cpp
 * @author Conner
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <memory>

using namespace std;

TEST(LevelTest, DeclarationsTest)
{
    SpartanHero game;

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(L"../levels/level0.xml"))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    Level level;
    level.LoadLevel(xmlDoc, &game);

    /// Tests basic level information
    ASSERT_EQ(level.GetmDeclarations().size(), 12);

    /// Tests that items can be pulled from mDeclarations
    /// and that all level 0 items are accounted for
    ASSERT_TRUE(level.GetmDeclarations()["i600"]);
    ASSERT_TRUE(level.GetmDeclarations()["i622"]);
    ASSERT_TRUE(level.GetmDeclarations()["i871"]);
    ASSERT_TRUE(level.GetmDeclarations()["i921"]);
    ASSERT_TRUE(level.GetmDeclarations()["t1"]);
    ASSERT_TRUE(level.GetmDeclarations()["t2"]);
    ASSERT_TRUE(level.GetmDeclarations()["t3"]);
    ASSERT_TRUE(level.GetmDeclarations()["t4"]);
    ASSERT_TRUE(level.GetmDeclarations()["t7"]);
    ASSERT_TRUE(level.GetmDeclarations()["t8"]);
    ASSERT_TRUE(level.GetmDeclarations()["t9"]);
    ASSERT_TRUE(level.GetmDeclarations()["t10"]);
}

TEST(LevelTest, PucksTest)
{
    /// Ensure the right amount of pucks are added to the game

    SpartanHero game;

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(L"../levels/level1.xml"))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    Level level;
    level.LoadLevel(xmlDoc, &game);

    ASSERT_EQ(level.GetPucks().size(), 262);
}