/**
 * @file SoundBoardDeclaration.cpp
 * @author Conner
 */
#include "pch.h"
#include "SoundBoardDeclaration.h"


/**
 * XML declaration for Soundboard
 * @param image image of soundboard
 * @param sizeX x size of soundboard
 * @param sizeY y size of soundboard
 * @param sizeBeats size of beats in soundboard
 * @param topWidth top width of soundboard
 * @param coverImage cover image of soundboard
 */
SoundBoardDeclaration::SoundBoardDeclaration(std::string image, int sizeX, int sizeY, int sizeBeats, int topWidth, std::string coverImage) : ItemDeclaration(image, sizeX, sizeY)
{
    mSizeBeats = sizeBeats;
    mTopWidth = topWidth;
    mCoverImage = coverImage;
}