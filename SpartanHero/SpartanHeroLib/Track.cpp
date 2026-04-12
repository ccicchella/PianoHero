/**
 * @file Track.cpp
 * @author Caden McDonald
 */

#include "pch.h"
#include <cmath>
#include "Track.h"
#include "SpartanHero.h"

/// The maximum number of tracks
const int MaxTracks = 10;

/// What is the border of the left and right
/// of the tracks? This is the percentage of
/// the space to the left of the first track line
/// and to the right of the last track line
const double Border = 0.09;

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

/// Percentage down on the soundboard to the keys
/// This is where the pucks go under the key and
/// disappear.
const double KeyRow = 0.85;

/// Width of the track line. The line is
/// drawn a wxBLACK.
const int TrackLineWidth = 5;


/**
 * Constructor for track
 * @param spartanHero pointer to SpartanHero
 * @param number track number
 * @param keyImage image for key
 * @param keySizeX x size of key
 * @param keySizeY y size of key
 * @param key string of key
 * @param xPos x pos of track
 * @param yPos y pos of track
 * @param width width of track
 * @param height height of track
 * @param topWidth top width of track
 */
Track::Track(SpartanHero* spartanHero, int number, std::string keyImage, int keySizeX, int keySizeY, std::string key, double xPos, double yPos, double width, double height, double topWidth)
{
    keyImage = "images/" + keyImage;

    mNumber = number;
    mKeyImage = std::make_unique<wxImage>(keyImage, wxBITMAP_TYPE_ANY);
    mKeySizeX = keySizeX;
    mKeySizeY = keySizeY;
    mKey = key;
    mGame = spartanHero;

    mXPos = xPos;
    mYPos = yPos;
    mHeight = height;
    mWidth = width;
    mTopWidth = topWidth;

    auto newWidth = ((mWidth-mTopWidth)*TopClearance)+mTopWidth;
    auto distanceIn = (mWidth-newWidth)/2;
    auto keyDistance = (newWidth-(Border*newWidth))/10;
    mXTrackStart = (mXPos + distanceIn)+(Border*mTopWidth)+(keyDistance*(mNumber-1));
    mYTrackStart = (mYPos + (TopClearance*mHeight));
    newWidth = ((mWidth-mTopWidth)*KeyRow)+mTopWidth;
    distanceIn = (mWidth-newWidth)/2;
    keyDistance = (newWidth-(Border*newWidth))/10;
    mXTrackEnd = (mXPos + distanceIn)+(Border*newWidth)+(keyDistance*(mNumber-1));
    mYTrackEnd = mYPos+(mHeight*KeyRow);
    mSlope = (mXTrackEnd-mXTrackStart)/(mYTrackEnd-mYTrackStart);
}


/**
 * Function to draw tracks
 * @param graphics pointer to wx graphics objects
 * @param absoluteBeat float representing the beat to specific decimal value
 */
void Track::DrawTrack(std::shared_ptr<wxGraphicsContext> graphics, float absoluteBeat)
{
    if (mKeyBitmap.IsNull())
    {
        mKeyBitmap = graphics->CreateBitmapFromImage(*mKeyImage);
    }

    wxPen pen(*wxBLACK, TrackLineWidth);
    graphics->SetPen(pen);

    graphics->StrokeLine(mXTrackStart, mYTrackStart, mXTrackEnd, mYTrackEnd);

    for (auto puck : mTrackPucks)
    {
        puck->DrawPuck(graphics, mXTrackStart, mYTrackStart, mXTrackEnd, mYTrackEnd, mSlope);
    }

    graphics->DrawBitmap(mKeyBitmap, mXTrackEnd-(mKeySizeX/2), mYTrackEnd-(mKeySizeY/2), mKeySizeX, mKeySizeY);
}


/**
 * Function to add pucks to track
 * @param puck shared pointer to PuckItem
 */
void Track::AddPuck(std::shared_ptr<PuckItem> puck)
{
    puck->SetPos(mXTrackStart, mYTrackStart);
    puck->SetStartX(mXTrackStart);
    puck->SetStartY(mYTrackStart);
    puck->SetEndX(mXTrackEnd);
    puck->SetEndY(mYTrackEnd);
    puck->SetBeatsPerMinute(mGame->GetBeatsPerMinute());
    puck->SetBeatsPerMinute(mGame->GetBeatsPerMinute());

    mCounter+=1;
    mTrackPucks.push_back(puck);
}

/**
 * Function to update the track
 * @param elapsed time spent in game
 */
void Track::Update(double elapsed)
{
    if (mTrackPucks.size()>mCurrent)
    {
        auto currentPuck = mTrackPucks[mCurrent];
        if(currentPuck->GetAbsoluteBeat() < (mGame->GetAbsoluteBeat()) + mGame->GetBeatsPerMeasure())
        {
            mCurrent += 1;
            mActivePucks.push_back(currentPuck);
        }
    }
        for(auto puck : mActivePucks)
        {
            if(puck->GetY() > mYTrackEnd)
            {
                if(puck->GetDuration() >= 1)
                {
                    mActiveLongPucks.push_back(puck);
                }
                else
                {
                    mGame->IncrementTotalScore(10);
                }
                mActivePucks.pop_front();
            }
            else
            {
                puck->Update(elapsed);
            }
        }
        for(auto puck : mActiveLongPucks)
        {
            if(puck->GetAbsoluteBeat()+puck->GetDuration() < mGame->GetAbsoluteBeat())
            {
                //double percentage = (mGame->GetAbsoluteBeat()-puck->GetAbsoluteBeat())/(puck->GetDuration());
                mActiveLongPucks.pop_front();
                mGame->IncrementTotalScore(10);
            }
            puck->Update(elapsed);
        }
}
