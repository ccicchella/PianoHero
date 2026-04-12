/**
 * @file Item.cpp
 * @author Ben, Conner
 *
 * Main class that all items on screen are drawn from
 */

#include "pch.h"
#include "Item.h"
#include "SpartanHero.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Deconstructor
 *
 */
Item::~Item()
{
}

/**
 * Draw an item
 * @param graphics Device context to draw on
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap.IsNull())
    {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }
    graphics->DrawBitmap(mItemBitmap, mX, mY, mW, mH);
}

/**
 * Constructor
 * @param spartanHero The game this item is a member of
 * @param filename The name of the file to display for this item
 */
Item::Item(SpartanHero *spartanHero, const std::wstring &filename) : mGame(spartanHero)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
}

/**
 * Function to set position of item
 * @param x x location
 * @param y y location
 */
void Item::SetPos(double x, double y)
{
    mX = x;
    mY = y;
}

/**
 * Constructor
 * @param spartanHero pointer to SpartanHero game
 * @param sizeX x size of game
 * @param sizeY y size of game
 * @param posX x pos of game
 * @param posY y pos of game
 * @param image image of game
 */
Item::Item(SpartanHero *spartanHero, int sizeX, int sizeY, int posX, int posY, std::string image) : mGame(spartanHero)
{
    mW = sizeX;
    mH = sizeY;
    mX = posX-(sizeX/2);
    mY = posY-(sizeY/2);

    image = "images/" + image;

    mItemImage = make_unique<wxImage>(image, wxBITMAP_TYPE_ANY);
}
