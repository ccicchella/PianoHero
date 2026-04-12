/**
 * @file ItemDeclaration.cpp
 * @author Conner
 *
 * Item declaration class
 */
#include "pch.h"
#include "ItemDeclaration.h"


/**
 * Constructor
 * @param image image of the item
 * @param sizeX x size of item
 * @param sizeY y size of item
 */
ItemDeclaration::ItemDeclaration(std::string image, int sizeX, int sizeY)
{
    mSizeX = sizeX;
    mSizeY = sizeY;
    mImageFileName = image;
}
