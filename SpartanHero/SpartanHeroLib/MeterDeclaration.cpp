/**
 * @file MeterDeclaration.cpp
 * @author Conner
 */
#include "pch.h"
#include "MeterDeclaration.h"

/**
 * XML declaration for Meter
 * @param image image of meter
 * @param sizeX x size of meter
 * @param sizeY y size of meter
 * @param needle needle image of meter
 * @param cover cover image of meter
 */
MeterDeclaration::MeterDeclaration(std::string image, int sizeX, int sizeY, std::string needle, std::string cover) : ItemDeclaration(image, sizeX, sizeY)
{
    mNeedleImage = needle;
    mCoverImage = cover;
}
