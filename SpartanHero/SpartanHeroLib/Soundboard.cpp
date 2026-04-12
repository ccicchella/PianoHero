/**
* @file Soundboard.cpp
* @author Ishraj Yadav
* @brief Implementation of the Soundboard class
*/

#include "pch.h"
#include <string>
#include "Soundboard.h"

using namespace std;


/**
 * Soundboard constructor
 * @param spartanHero pointer to SpartanHero
 * @param width width of soundboard
 * @param height height of soundboard
 * @param x x pos of soundboard
 * @param y y pos of soundboard
 * @param boardImage image of soundboard
 * @param coverImage soundboard cover image
 * @param sbChildren pointer to xml node
 * @param topWidth top width of soundboard
 * @param sizeBeats size of beats
 */
Soundboard::Soundboard(SpartanHero *spartanHero, int width, int height, int x, int y, string boardImage, string coverImage, wxXmlNode* sbChildren, int topWidth, int sizeBeats) : Item(spartanHero, width, height, x, y, boardImage)
{
    mGame = spartanHero;

    mWidth = width;
    mHeight = height;
    mTopWidth = topWidth;
    mSizeBeats = sizeBeats;

    mX = x-(width/2);
    mY = y-(height/2);

    coverImage = "images/" + coverImage;

    std::shared_ptr<Track> track;

    for (;sbChildren;sbChildren=sbChildren->GetNext())
    {
        auto number = wxAtoi(sbChildren->GetAttribute(L"track"));
        auto keyImage = sbChildren->GetAttribute(L"key-image").ToStdString();
        auto keySize = sbChildren->GetAttribute(L"key-size");

        // Get the two positions from the tuple
        int keySizeX, keySizeY;
        keySizeX = wxAtoi(keySize.BeforeFirst(','));
        keySizeY = wxAtoi(keySize.AfterFirst(','));

        auto key = sbChildren->GetAttribute(L"key").ToStdString();

        track = std::make_shared<Track>(spartanHero, number, keyImage, keySizeX, keySizeY, key, mX, mY, mWidth, mHeight, mTopWidth);
        mTracks[number-1]=track;
    }

    mSoundboardCover = make_unique<wxImage>(coverImage, wxBITMAP_TYPE_ANY);
}

/**
 * Function to draw soundboard
 * @param graphics shared pointer to graphics objects
 */
void Soundboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    if(mSoundboardCoverBitmap.IsNull())
    {
        mSoundboardCoverBitmap = graphics->CreateBitmapFromImage(*mSoundboardCover);
    }

    for (auto track : mTracks)
    {
        if (track!= nullptr)
        {
            track->DrawTrack(graphics, mGame->GetAbsoluteBeat());
        }
    }

    graphics->DrawBitmap(mSoundboardCoverBitmap, mX, mY, mWidth, mHeight);
}


/**
 * Function to update the soundboard
 * @param elapsed time spent in game
 */
void Soundboard::Update(double elapsed)
{
    for (auto track : mTracks)
    {
        if (track!= nullptr)
        {
            track->Update(elapsed);
        }
    }
}

/**
 * Function to add pucks to soundboard
 * @param puck shared pointer of PuckItems
 */
void Soundboard::AddPuck(std::shared_ptr<PuckItem> puck)
{
    auto trackNumber = puck->GetTrack();
    if (!mCounter)
    {
        mGame->SetFirstAbsoluteBeat(puck->GetAbsoluteBeat());
        mCounter=true;
    }
    mTracks[trackNumber-1]->AddPuck(puck);
}
