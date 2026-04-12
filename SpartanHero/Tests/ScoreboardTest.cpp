/**
 * @file ScoreboardTest.cpp
 * @author Conner
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SpartanHero.h>
#include <Level.h>
#include <AddPuck.h>

using namespace std;

TEST(ScoreboardTest, Level0LocationTest)
{
    SpartanHero game;

    AddPuck scoreboardVisitor;

    wxXmlDocument xmlDoc;

    auto file = L"../levels/level0.xml";
    if(!xmlDoc.Load(file))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    Level level;
    level.LoadLevel(xmlDoc, &game);

    game.Accept(&scoreboardVisitor);

    ASSERT_EQ(200, scoreboardVisitor.GetmScoreboardW());
    ASSERT_EQ(136, scoreboardVisitor.GetmScoreboardH());
}

TEST(ScoreboardTest, Level2LocationTest)
{
    SpartanHero game;

    AddPuck scoreboardVisitor;

    wxXmlDocument xmlDoc;

    auto file = L"../levels/level2.xml";
    if(!xmlDoc.Load(file))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    Level level;
    level.LoadLevel(xmlDoc, &game);

    game.Accept(&scoreboardVisitor);

    ASSERT_EQ(288, scoreboardVisitor.GetmScoreboardW());
    ASSERT_EQ(195, scoreboardVisitor.GetmScoreboardH());
}
