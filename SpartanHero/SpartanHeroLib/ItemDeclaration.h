/**
 * @file ItemDeclaration.h
 * @author baske
 *
 * Declaration class for items
 *
 * This class loads in xml data for the items in the game
 */

#ifndef SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_DECLARATION_H
#define SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_DECLARATION_H

/**
 * This class is a base class for item declarations
 */
class ItemDeclaration
{
private:
    /// Identifier
    std::string mIdentifier;

    /// Image file name
    std::string mImageFileName;

    /// x size of image
    int mSizeX;
    /// y size of image
    int mSizeY;

public:
    ItemDeclaration(std::string image, int sizeX, int sizeY);

    /**
     * Getter for image file
     * @returns image file name
     */
    std::string getMImageFileNameDeclaration() {return mImageFileName;}
    /**
     * Getter for x size
     * @returns x size
     */
    int getMSizeXDeclaration() {return mSizeX;}
    /**
     * Getter for y size
     * @returns y size
     */
    int getMSizeYDeclaration() {return mSizeY;}

    /**
     * Virtual getter for needle image
     * @returns needle image
     */
    virtual std::string GetmNeedleImage() {return "";}
    /**
     * Virtual getter for cover image
     * @returns cover image
     */
    virtual std::string GetmCoverImage() {return "";}

    /**
     * Virtual getter for top width
     * @returns top width
     */
    virtual int GetTopWidth() {return 0;}
    /**
     * Virtual getter for beat size
     * @returns beat size
     */
    virtual int GetSizeBeats() {return 0;}
    /**
     * Virtual getter track
     * @returns track
     */
    virtual int GetmTrack() {return 0;}
    /**
     * Virtual getter for tolerance
     * @returns tolerance
     */
    virtual double GetmTolerance() {return 0;}

};

#endif //SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_DECLARATION_H
