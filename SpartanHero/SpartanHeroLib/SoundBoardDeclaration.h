/**
 * @file SoundBoardDeclaration.h
 * @author Conner
 *
 * Declaration class for sound
 *
 * This class loads in the xml attributes for sound
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_SOUNDBOARDDECLARATION_H
#define SPARTANHERO_SPARTANHEROLIB_SOUNDBOARDDECLARATION_H

#include "ItemDeclaration.h"

/**
 * This class is a declaration class for soundboard
 */
class SoundBoardDeclaration : public ItemDeclaration
{
private:
    /// Beat size
    int mSizeBeats;

    /// Width of top of soundboard
    int mTopWidth;

    /// Cover image file name
    std::string mCoverImage;
public:
    SoundBoardDeclaration(std::string image, int sizeX, int sizeY, int sizeBeats, int topWidth, std::string coverImage);

    /**
     * Getter for cover image
     * @returns cover image
     */
    std::string GetmCoverImage() override {return mCoverImage;}
    /**
     * Getter for top width
     * @returns top width
     */
    int GetTopWidth() override {return mTopWidth;}
    /**
     * Getter for beat size
     * @returns beat size
     */
    int GetSizeBeats() override {return mSizeBeats;}



};

#endif //SPARTANHERO_SPARTANHEROLIB_SOUNDBOARDDECLARATION_H
