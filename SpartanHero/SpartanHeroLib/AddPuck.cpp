/**
 * @file AddPuck.cpp
 * @author Caden McDonald
 *
 */
#include "pch.h"
#include "AddPuck.h"
#include "Soundboard.h"
#include "Scoreboard.h"


/**
 * Visitor function that adds pucks to tracks
 * @param soundboard The game instance we are in
 */
void AddPuck::VisitSoundboard(Soundboard *soundboard)
{
    mTracks=soundboard->GetTracks();
    if (mPuck!=nullptr)
    {
        soundboard->AddPuck(mPuck);
    }
}

/**
 * Visits the scoreboard
 * @param scoreboard
 */
void AddPuck::VisitScoreboard(Scoreboard *scoreboard)
{
    mScoreboardW = scoreboard->GetW();
    mScoreboardH = scoreboard->GetH();

}

