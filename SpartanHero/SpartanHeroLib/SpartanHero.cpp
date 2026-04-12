/**
 * @file SpartanHero.cpp
 * @author charl, Conner
 *
 * Game class
 */

#include "pch.h"
#include "SpartanHero.h"
#include "Scoreboard.h"
#include "Soundboard.h"
#include "Item.h"
#include "Level.h"
#include "AddPuck.h"
#include "ItemVisitor.h"
#include <wx/graphics.h>
#include "Sound.h"

using namespace std;

/// variable for seconds per minute
const int SecondsPerMinute = 60;

/**
 * SpartanHero contructor
 * @param audioEngine ma engine for audio sounds
 */
SpartanHero::SpartanHero(ma_engine* audioEngine)
{
    mAudioEngine = audioEngine;
    mGameScore = new Score();
}

/**
 * SpartanHero deconstructor
 */
SpartanHero::~SpartanHero()
{
    delete mGameScore;
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void SpartanHero::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth =  mPlayX;
    int pixelHeight = mPlayY;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE

    for (auto item : mItems)
    {
        // Handle other types of items
        item->Draw(graphics);
    }

    if (mDrawBegin)
    {
        DrawBegin(graphics);
    }
    if (mDrawEnd)
    {
        DrawEnd(graphics);
    }

    graphics->PopState();
}


/**
 * Game Constructor
 */
SpartanHero::SpartanHero()
{
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void SpartanHero::Update(double elapsed)
{
    for(auto item : mItems)
    {
        item->Update(elapsed);
    }

    if (mCountDown > mBeatsPerMeasure)
    {

        mCountDown -= elapsed; ///< Speed up the countdown

    }
    if (mCountDown <= mBeatsPerMeasure)
    {
        mCountDown -= elapsed * mBeatsPerMinute / SecondsPerMinute;
        mAbsoluteBeat += elapsed * mBeatsPerMinute / SecondsPerMinute;
        mMeasure = (mAbsoluteBeat / mBeatsPerMeasure);
        mBeat = mAbsoluteBeat - (mMeasure * mBeatsPerMeasure)+1;
    }
    if (mMeasure >= mMaxMeasure)
    {
        mDrawEnd=true;
        StopSoundFromMap("BACK");
        mCountDownEnd -= elapsed;
        if (mCountDownEnd <= 0 && mCurrLevel == "0")
        {
            wxString filename = "../levels/level1.xml";
            SetCurrLevel(L"1");
            Load(filename);
            ResetLevel();
        }
        if (mCountDownEnd <= 0 && mCurrLevel == "1")
        {
            wxString filename = "../levels/level2.xml";
            SetCurrLevel(L"2");
            Load(filename);
            ResetLevel();
        }
        if (mCountDownEnd <= 0 && mCurrLevel == "2")
        {
            wxString filename = "../levels/level3.xml";
            SetCurrLevel(L"3");
            Load(filename);
            ResetLevel();
        }
        if (mCountDownEnd <= 0 && mCurrLevel == "3")
        {
            wxString filename = "../levels/level3.xml";
            SetCurrLevel(L"3");
            Load(filename);
            ResetLevel();
        }
    }
    if (mAbsoluteBeat >= 0 && mFirstTicker)
    {
        PlaySoundFromMap("BACK");
        mFirstTicker=false;
    }
    if (mAutoPlayEnabled)
    {
        AutoPlay();
    }
}

/**
 * Clear the game data.
 *
 * Deletes all known items in the game.
 */
void SpartanHero::Clear()
{
    mItems.clear();
}

/**
 * Reset items presented on scoreboard
 */
void SpartanHero::ResetLevel()
{
    mBeat = 0;
    mAbsoluteBeat = -4;
    mMeasure = 0;
    mCountDown = 6;
    mCountDownEnd = 2;
    mDrawBegin = true;
    mDrawEnd = false;
    mFirstTicker = true;

    mGameScore->ResetScore();
    mGameScore->ResetTotalScore();
    mGameScore->ResetMeterScore();
}

/**
 * Load in a level
 * @param filename Name of level file to load in
 */
void SpartanHero::Load(const wxString &filename)
{
    if (!mItems.empty())
    {
        ResetLevel();
    }

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    Clear();

    Level level;
    level.LoadLevel(xmlDoc, this);
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void SpartanHero::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Function for beginning drawing of SpartanHero
 * @param graphics shared pointer to graphics objects
 */
void SpartanHero::DrawBegin(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mCountDown > 4)
    {
        auto str = L"Level " + mCurrLevel + " Begin";
        wxFont font(wxSize(100, 100),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(192, 252, 207));

        double wid, hit;
        graphics->GetTextExtent(str, &wid, &hit);
        graphics->DrawText(str, mPlayX / 2 - wid / 2, mPlayY / 2 - 40 - hit / 2);
    }
}

/**
 * Function for end drawing of SpartanHero
 * @param graphics shared pointer to graphics objects
 */
void SpartanHero::DrawEnd(std::shared_ptr<wxGraphicsContext> graphics)
{
        auto str = L"Level Complete!";
        wxFont font(wxSize(100, 100),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(192, 252, 207));

        double wid, hit;
        graphics->GetTextExtent(str, &wid, &hit);
        graphics->DrawText(str, mPlayX / 2 - wid / 2, mPlayY / 2 - 40 - hit / 2);
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void SpartanHero::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}


/**
 * Hit test function for pucks in game
 * @param trackNum number for track
 * @return boolean whether the note was hit or not
 */
bool SpartanHero::HitTest(int trackNum)
{
    AddPuck soundboardVisitor;
    this->Accept(&soundboardVisitor);
    auto tracks = soundboardVisitor.GetTracks();

    auto track = tracks[trackNum];
    auto pucks = track->GetActivePucks();

    if (!pucks.empty())
    {
        auto puck = pucks[0];
        auto lowerTolerance = puck->GetAbsoluteBeat() - puck->GetTolerance();
        auto upperTolerance = puck->GetAbsoluteBeat() + puck->GetTolerance();
        if(mAbsoluteBeat > lowerTolerance && mAbsoluteBeat < upperTolerance && !puck->GetHitTest())
        {
            if (puck->GetDuration() < 1)
            {
                IncrementMeterScore(10);
            }
            PlaySoundFromMap(puck->GetSound());
            puck->SetHitTest(true);
            return true;
        }
    }
    return false;
}

/**
 * Hit test function for long pucks in game
 * @param trackNum number for track
 * @return boolean whether the duration was hit or not
 */
double SpartanHero::DurationHitTest(int trackNum)
{
    AddPuck soundboardVisitor;
    this->Accept(&soundboardVisitor);
    auto tracks = soundboardVisitor.GetTracks();

    auto track = tracks[trackNum];
    auto pucks = track->GetActiveLongPucks();

    if (!pucks.empty())
    {
        auto puck = pucks[0];
        if(mAbsoluteBeat<=puck->GetAbsoluteBeat()+puck->GetDuration() && puck->GetHitTest())
        {
            double percentage = (mAbsoluteBeat-puck->GetAbsoluteBeat())/(puck->GetDuration());
            IncrementMeterScore(percentage*10);
            //IncrementTotalScore(10);
            return percentage;
        }
    }
    return 0;
}

/**
 * Stops the current sound of the track from playing
 * @param trackNum num of the track
 */
void SpartanHero::StopSound(int trackNum)
{
    AddPuck soundboardVisitor;
    this->Accept(&soundboardVisitor);
    auto tracks = soundboardVisitor.GetTracks();

    auto track = tracks[trackNum];
    auto pucks = track->GetActiveLongPucks();

    if (!pucks.empty())
    {
        auto puck = pucks[0];
        if (puck->GetDuration()>=1)
        {
            StopSoundFromMap(puck->GetSound());
        }
    }
}

/**
 * Increments the mGameScore variable
 * @param increment
 */
void SpartanHero::IncrementScore(int increment)
{
    mGameScore->Increment(increment);
}

/**
 * Increments the mGameTotalScore variable
 * @param increment
 */
void SpartanHero::IncrementTotalScore(int increment)
{
    mGameScore->IncrementTotal(increment);
}
/**
 * Increments the meter score
 * @param increment
 */
void SpartanHero::IncrementMeterScore(int increment)
{
    mGameScore->IncrementMeterTotal(increment);
}

/**
 * SpartanHero AutoPlay Function
 */
void SpartanHero::AutoPlay()
{
    AddPuck soundboardVisitor;
    this->Accept(&soundboardVisitor);
    auto tracks = soundboardVisitor.GetTracks();

    for(auto &track : tracks)
    {
        if (track != nullptr)
        {
            auto pucks = track->GetActivePucks();
            if (!pucks.empty())
            {
                auto puck = pucks[0];
                if (mAbsoluteBeat >= puck->GetAbsoluteBeat() && !puck->GetHitTest())
                {
                    puck->SetHitTest(true);
                    PlaySoundFromMap(puck->GetSound());
                    IncrementScore(10);
                    IncrementMeterScore(10);
                }
            }
        }
    }
}