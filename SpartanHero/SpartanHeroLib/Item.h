/**
 * @file Item.h
 * @author Ben
 *
 * Class to hold Item functions and attributes
 */

#ifndef SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_ITEM_H
#define SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_ITEM_H

#include <wx/graphics.h>
#include "ItemDeclaration.h"
#include "ItemVisitor.h"

class SpartanHero;
/**
 * This class is a base class for items in game
 */
class Item
{
private:
    /// The game this item is contained in
    SpartanHero  *mGame;

    /// Item location in the game window
    double  mX = 0;     ///< X location for the top left of the item
    double  mY = 0;     ///< Y location for the top left of the item
    double  mW = 0;     ///< Width of the item in pixels
    double  mH = 0;     ///< Height of the item in pixels

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    wxGraphicsBitmap mItemBitmap;

public:
    /// Deconstructor
    ~Item();

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    void SetPos(double x, double y);
    /**
     * Getter for X
     * @returns x pos
     */
    double GetX() {return mX;}
    /**
     * Getter for Y
     * @returns y pos
     */
    double GetY() {return mY;}
    /**
     * Getter for width
     * @returns width
     */
    double GetW() {return mW;}
    /**
     * Getter for height
     * @returns height
     */
    double GetH() {return mH;}

    /**
     * Accept funtion for visitor
     * @param visitor pointer to item visitor
     */
    virtual void Accept(ItemVisitor* visitor) = 0;
    /**
     * virtual function to reset item
     */
    virtual void ResetItem() {}
protected:

    Item(SpartanHero *spartanHero, const std::wstring &filename);

    Item(SpartanHero *spartanHero, int sizeX, int sizeY, int posX, int posY, std::string image);


};


#endif //SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_ITEM_H
