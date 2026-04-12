/**
 * @file PuckItem.cpp
 * @author Conner
 *
 * Puck class (taps only)
 */

#include "pch.h"
#include <string>
#include <wx/graphics.h>
#include "PuckItem.h"
#include "SpartanHero.h"


using namespace std;

/// Const variable for beats per measure
const int beatsPerMeasure=4;

/**
 * Puck Constructor
 * @param spartanHero pointer to SpartanHero class
 * @param width width of meter
 * @param height height of meter
 * @param x x pos of meter
 * @param y y pos of meter
 * @param image image of meter
 * @param track track for puck
 * @param tolerance tolerance of puck
 * @param beat beat of puck
 * @param measure measure of puck
 * @param duration duration of puck
 * @param sound sound of puck
 */
PuckItem::PuckItem(SpartanHero *spartanHero, int width, int height, int x, int y, string image, int track, double tolerance, double beat, int measure, double duration, wxString sound) : Item(spartanHero, width, height, x, y, image)
{
    mGame = spartanHero;

    mSizeX = 28.3176;
    mSizeY = 28.3176;

    mSpeedX = 0;
    mSpeedY = 0;

    mTrack = track;
    mTolerance = tolerance;

    mBeat = beat;
    mMeasure = measure;
    mDuration = duration;

    mAbsoluteBeat = (measure - 1) * beatsPerMeasure + (beat - 1);

    image = "images/" + image;

    mPuckImage = make_unique<wxImage>(image, wxBITMAP_TYPE_ANY);

    mSound = sound;
}

/**
 * Function to draw pucks
 * @param graphics shared pointer to graphics in game
 * @param xStart x start of puck
 * @param yStart y start of puck
 * @param xEnd x end of puck
 * @param yEnd y end of puck
 * @param slope slope of puck
 */
void PuckItem::DrawPuck(std::shared_ptr<wxGraphicsContext> graphics, double xStart, double yStart, double xEnd, double yEnd, double slope)
{
    if (GetY() >= yStart && GetY() <= yEnd)
    {
        if(mPuckBitmap.IsNull())
        {
            mPuckBitmap = graphics->CreateBitmapFromImage(*mPuckImage);
        }
        graphics->DrawBitmap(mPuckBitmap, GetX() - (mSizeX / 2), GetY() - (mSizeY / 2), mSizeX, mSizeY);
    }
}

/**
 * Function that updates the position of the puck
 * @param elapsed time elapsed in game
 */
void PuckItem::Update(double elapsed)
{
    auto totalLengthBeatX = (mXEnd-mXStart)/4;
    auto totalLengthBeatY = (mYEnd-mYStart)/4;
    auto beatDuration = 60/mBeatsPerMinute;
    /// Calculated growth of size for every beat
    const double growthRate = 6.6006;
    auto distanceTraveledX = totalLengthBeatX*((elapsed)/beatDuration);
    auto distanceTraveledY = totalLengthBeatY*((elapsed)/beatDuration);
    auto growth = growthRate*((elapsed)/beatDuration);

    SetPos(GetX() + distanceTraveledX, GetY()+distanceTraveledY);
    SetSizeX(GetSizeX() + growth);
    SetSizeY(GetSizeY() + growth);
}
