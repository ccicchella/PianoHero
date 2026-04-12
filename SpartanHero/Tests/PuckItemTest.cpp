/**
 * @file PuckItemTest.cpp
 * @author Conner
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SpartanHero.h>
#include <Soundboard.h>
#include <PuckItem.h>
#include <Track.h>
#include <AddPuck.h>
#include <Level.h>

using namespace std;

class PuckItemTest : public ::testing::Test
{
protected:
//    AddPuck() {}
};

TEST_F(PuckItemTest, PuckAccuracy)
{
    SpartanHero game;

    AddPuck soundboardVisitor;

    wxXmlDocument xmlDoc;

    Level levelLoader;

    auto file = L"../levels/level2.xml";
    if(!xmlDoc.Load(file))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    levelLoader.LoadLevel(xmlDoc, &game);

    game.Accept(&soundboardVisitor);

    // Initialize all tracks

    auto tracks = soundboardVisitor.GetTracks();

    auto track1 = tracks[0];
    auto track2 = tracks[1];
    auto track3 = tracks[2];
    auto track4 = tracks[3];
    auto track5 = tracks[4];
    auto track6 = tracks[5];
    auto track7 = tracks[6];
    auto track8 = tracks[7];
    auto track9 = tracks[8];
    auto track10 = tracks[9];

    // Hit test for every key, no pucks
    ASSERT_FALSE(game.HitTest(0));
    ASSERT_FALSE(game.HitTest(1));
    ASSERT_FALSE(game.HitTest(2));
    ASSERT_FALSE(game.HitTest(3));
    ASSERT_FALSE(game.HitTest(4));
    ASSERT_FALSE(game.HitTest(5));
    ASSERT_FALSE(game.HitTest(6));
    ASSERT_FALSE(game.HitTest(7));
    ASSERT_FALSE(game.HitTest(8));
    ASSERT_FALSE(game.HitTest(9));

    // Hit test for every key, no hits


    // Hit test for every key, all hit


    // Hit test for one key, multiple pucks

}

TEST(LevelTest, TrackTest)
{
    /// Ensure the track is correct, such as the key and the number of pucks

    SpartanHero game;

    AddPuck soundboardVisitor;

    wxXmlDocument xmlDoc;

    Level levelLoader;

    auto file = L"../levels/level1.xml";
    if(!xmlDoc.Load(file))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    levelLoader.LoadLevel(xmlDoc, &game);

    game.Accept(&soundboardVisitor);

    auto tracks = soundboardVisitor.GetTracks();

    auto track1 = tracks[0];
    auto track2 = tracks[1];
    auto track3 = tracks[2];
    auto track4 = tracks[3];
    auto track5 = tracks[6];
    auto track6 = tracks[7];
    auto track7 = tracks[8];
    auto track8 = tracks[9];

    ASSERT_EQ(track1->GetCounter(), 37);
    ASSERT_EQ(track2->GetCounter(), 39);
    ASSERT_EQ(track3->GetCounter(), 32);
    ASSERT_EQ(track4->GetCounter(), 38);
    ASSERT_EQ(track5->GetCounter(), 46);
    ASSERT_EQ(track6->GetCounter(), 32);
    ASSERT_EQ(track7->GetCounter(), 24);
    ASSERT_EQ(track8->GetCounter(), 14);
}