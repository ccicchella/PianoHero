/**
 * @file StaticImage.h
 * @author Caden McDonald
 *
 * This class creates static images
 *
 * This is for the images that don't move in SpartanHero like the figures on the side
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_STATICIMAGE_H
#define SPARTANHERO_SPARTANHEROLIB_STATICIMAGE_H

#include <string>
#include "SpartanHero.h"
#include "Item.h"

/**
 * This class is a child to item and is for static images in game
 */
class StaticImage : public Item
{
private:
    /**
     * Size of image
     */
    std::string mSize;
    /**
     * X size of image
     */
    int mSizeX;
    /**
     * Y size of image
     */
    int mSizeY;

public:
    StaticImage(SpartanHero *spartanHero, int sizeX, int sizeY, int posX, int posY, std::string image);

    /// Default constructor (disabled)
    StaticImage() = delete;

    /// Copy constructor (disabled)
    StaticImage(const StaticImage &) = delete;

    /// Assignment operator
    void operator=(const StaticImage &) = delete;

    /**
     * Getter for X size
     * @returns x size
     */
    int GetSizeX() const { return mSizeX; }
    /**
     * Getter for Y size
     * @returns y size
     */
    int GetSizeY() const { return mSizeY; }

    /**
    * Accept a visitor
    * @param item The visitor we accept
    */
    void Accept(ItemVisitor* item) override { item->VisitStaticImage(this); }



};

#endif //SPARTANHERO_SPARTANHEROLIB_STATICIMAGE_H
