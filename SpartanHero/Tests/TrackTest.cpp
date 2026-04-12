/**
 * @file TrackTest.cpp
 * @author Caden McDonald
 */
#include <pch.h>
#include <gtest/gtest.h>
#include <SpartanHero.h>
#include <AddPuck.h>

TEST(TrackTest, TrackPlacement)
{
    /// Ensure track placement for each track is correct
    SpartanHero game;

    game.Load(L"../levels/level0.xml");

    AddPuck soundboardVisitor;
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

    ASSERT_EQ(std::round(track1->GetXTrackStart()), 508);
    ASSERT_EQ(track1->GetYTrackStart(), 247.5);
    ASSERT_EQ(std::round(track1->GetXTrackEnd()), 381);
    ASSERT_EQ(track1->GetYTrackEnd(), 656.25);

    ASSERT_EQ(std::round(track2->GetXTrackStart()), 539);
    ASSERT_EQ(track2->GetYTrackStart(), 247.5);
    ASSERT_EQ(std::round(track2->GetXTrackEnd()), 441);
    ASSERT_EQ(track2->GetYTrackEnd(), 656.25);

    ASSERT_EQ(std::round(track3->GetXTrackStart()), 570);
    ASSERT_EQ(track3->GetYTrackStart(), 247.5);
    ASSERT_EQ(std::round(track3->GetXTrackEnd()), 501);
    ASSERT_EQ(track3->GetYTrackEnd(), 656.25);
}

TEST(TrackTest, TrackInitialization)
{
    // Ensure all values of the track are properly created

    SpartanHero game;

    game.Load(L"../levels/level0.xml");

    AddPuck soundboardVisitor;
    game.Accept(&soundboardVisitor);

    auto tracks = soundboardVisitor.GetTracks();

    auto track1 = tracks[0];

    ASSERT_EQ(track1->GetXPos(), 289);
    ASSERT_EQ(track1->GetYPos(), 193);
    ASSERT_EQ(track1->GetWidth(), 726);
    ASSERT_EQ(track1->GetHeight(), 545);

}
