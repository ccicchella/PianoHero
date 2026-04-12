/**
 * @file PuckDeclaration.h
 * @author Conner
 *
 * Declaration for pucks
 *
 * This class loads in xml data for the pucks in the game
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_PUCKDECLARATION_H
#define SPARTANHERO_SPARTANHEROLIB_PUCKDECLARATION_H

#include "ItemDeclaration.h"
/**
 * This class is a declaration class for puck
 */
class PuckDeclaration : public ItemDeclaration
{
private:
    /// Track number to be placed on
    int mTrack;

    /// Distance from note tolerated as a valid press
    double mTolerance;

public:
    PuckDeclaration(std::string image, int sizeX, int sizeY, int track, double tolerance);

    /**
     * Getter for track
     * @returns track
     */
    virtual int GetmTrack() {return mTrack;}
    /**
     * Getter for tolerance
     * @returns tolerance
     */
    virtual double GetmTolerance() {return mTolerance;}
};

#endif //SPARTANHERO_SPARTANHEROLIB_PUCKDECLARATION_H
