/**
 * @file Meter.h
 * @author Caden McDonald
 *
 * Game meter class
 *
 * This class holds information of the meter in the game and has fucntions to adjust the meter
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_METER_H
#define SPARTANHERO_SPARTANHEROLIB_METER_H

#include "Item.h"
#include "SpartanHero.h"
#include "Track.h"
/**
 * This class creates a meter for the accuracy of player
 */
class Meter : public Item
{
private:

    /// The needle of the meter
    std::unique_ptr<wxImage> mMeterNeedle;

    /// The cover of the meter
    std::unique_ptr<wxImage> mMeterCover;

    /// The bitmap used to display the needle
    wxGraphicsBitmap mNeedleBitmap;

    /// The bitmap used to display the cover
    wxGraphicsBitmap mCoverBitmap;
    /// x pos
    int mX;
    /// y pos
    int mY;
    /// width
    int mWidth;
    /// height
    int mHeight;
    /// pointer to SpartanHero
    SpartanHero* mGame;
    /// accuracy of player
    double mAccuracy;

public:

    Meter(SpartanHero *spartanHero, int width, int height, int x, int y, std::string image, std::string needle, std::string cover);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param item The visitor we accept
     */
    void Accept(ItemVisitor* item) override { item->VisitMeter(this); }
};

#endif //SPARTANHERO_SPARTANHEROLIB_METER_H
