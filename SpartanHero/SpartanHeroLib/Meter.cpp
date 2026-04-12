/**
 * @file Meter.cpp
 * @author Caden McDonald
 */

#include "pch.h"
#include "Meter.h"
#include <wx/graphics.h>

using namespace std;


/**
 * Meter Constructor
 * @param spartanHero pointer to SpartanHero class
 * @param width width of meter
 * @param height height of meter
 * @param x x pos of meter
 * @param y y pos of meter
 * @param image image of meter
 * @param needle needle of meter
 * @param cover cover of meter
 */
Meter::Meter(SpartanHero *spartanHero, int width, int height, int x, int y, string image, string needle, string cover) : Item(spartanHero, width, height, x, y, image)
{
    mWidth = width;
    mHeight = height;

    mX = x-(width/2);
    mY = y-(height/2);

    needle = "images/" + needle;
    cover = "images/" + cover;

    mMeterNeedle = make_unique<wxImage>(needle, wxBITMAP_TYPE_ANY);
    mMeterCover = make_unique<wxImage>(cover, wxBITMAP_TYPE_ANY);

    mGame = spartanHero;
}

/**
 * Draw function for meter
 * @param graphics shared pointer to wx graphics objects
 */
void Meter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    if(mNeedleBitmap.IsNull())
    {
        mNeedleBitmap = graphics->CreateBitmapFromImage(*mMeterNeedle);
    }

    if(mCoverBitmap.IsNull())
    {
        mCoverBitmap = graphics->CreateBitmapFromImage(*mMeterCover);
    }

    /// Positive or negative rotations of this amount will move
    /// the needle to the limit in that direction.
    /// A meter score of 0 will be a rotation of -0.9
    /// A meter score of 100% (11) will be a rotation of 0.9
    const double MaxNeedleRotation = 0.9;

    /// This is how far down the need image the pivot point is
    /// as a percentage of the height of the image.
    const double NeedlePivotYOffset = 0.80;

    if(mGame->GetGameScore()->GetTotalScore() == 0)
    {
        mAccuracy = 100;
    }
    else
    {
        mAccuracy = ((double)mGame->GetGameScore()->GetMeterScore()/mGame->GetGameScore()->GetTotalScore())*100;
    }

    double adjustedAccuracy = (mAccuracy - 50.0) / 50.0;

    if (adjustedAccuracy > 1)
    {
        adjustedAccuracy = 1;
    }

    double needleRotation = (adjustedAccuracy) * MaxNeedleRotation;

    int needlePivotY = (int)(mHeight * NeedlePivotYOffset);

    graphics->PushState();
    graphics->Translate(mX+mWidth/2, mY + needlePivotY);
    graphics->Rotate(needleRotation);
    wxBitmap needleBitmap(*mMeterNeedle, wxBITMAP_SCREEN_DEPTH);
    graphics->DrawBitmap(needleBitmap,
                         -mWidth/2,
                         -needlePivotY,
                         mWidth, mHeight);

    graphics->PopState();

    graphics->DrawBitmap(mCoverBitmap, mX, mY, mWidth, mHeight);

}