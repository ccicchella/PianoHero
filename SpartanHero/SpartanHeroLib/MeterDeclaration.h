/**
 * @file MeterDeclaration.h
 * @author Conner
 *
 * Declaration class for meter
 *
 * This class gets the xml data for the meter in the game
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_METERDECLARATION_H
#define SPARTANHERO_SPARTANHEROLIB_METERDECLARATION_H

#include "ItemDeclaration.h"

/**
 * This class is a declaration class for meter
 */
class MeterDeclaration : public ItemDeclaration
{
private:
    /// File name for needle image
    std::string mNeedleImage;

    /// File name for cover image
    std::string mCoverImage;

    /// x size
    int sizeX;
    /// y size
    int sizeY;

public:
    MeterDeclaration(std::string image, int sizeX, int sizeY, std::string needle, std::string cover);

    /**
     * Getter for needle image
     * @return needle image
     */
    std::string GetmNeedleImage() override {return mNeedleImage;}
    /**
     * Getter for cover image
     * @return cover image
     */
    std::string GetmCoverImage() override {return mCoverImage;}
};

#endif //SPARTANHERO_SPARTANHEROLIB_METERDECLARATION_H
