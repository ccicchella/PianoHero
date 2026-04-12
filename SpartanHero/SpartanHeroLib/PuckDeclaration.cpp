/**
 * @file PuckDeclaration.cpp
 * @author Conner
 */
#include "pch.h"
#include "PuckDeclaration.h"


/**
 * XML declaration for Puck
 * @param image image of puck
 * @param sizeX x size of puck
 * @param sizeY y size of puck
 * @param track track number
 * @param tolerance tolerance number of puck
 */
PuckDeclaration::PuckDeclaration(std::string image, int sizeX, int sizeY, int track, double tolerance) : ItemDeclaration(image, sizeX, sizeY)
{
    mTrack = track;
    mTolerance = tolerance;
}