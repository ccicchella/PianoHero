/**
 * @file PuckLongItem.h
 * @author Conner
 *
 * Class for trailing lined pucks
 *
 * This class is a child of PuckItem and is specifically for trailing lined pucks
 */

#ifndef SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_PUCKLONGITEM_H
#define SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_PUCKLONGITEM_H

#include "Item.h"
#include "PuckItem.h"
#include "SpartanHero.h"

class Soundboard;
/**
 * This class is a child to PuckItem and is for pucks with trailing lines
 */
class PuckLongItem : public PuckItem
{
private:
    /// duration of puck
    double mDuration;
    /// pointer to SpartanHero
    SpartanHero* mGame;

public:

    /// Assignment operator
    void operator=(const PuckLongItem &) = delete;

    PuckLongItem(SpartanHero* spartanHero, int width, int height, int x, int y, std::string image, int track, double tolerance, double beat, int measure, double duration,wxString sound);

    void DrawPuck(std::shared_ptr<wxGraphicsContext> graphics, double xStart, double yStart, double xEnd, double yEnd, double slope) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPuckLongItem(this) ;}
};

#endif //SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_PUCKLONGITEM_H
