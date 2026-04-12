/**
 * @file StaticImage.cpp
 * @author Caden McDonald
 */
#include "pch.h"
#include "StaticImage.h"

/**
 * Constructor for static images
 * @param spartanHero pointer to SpartanHero
 * @param sizeX x size of image
 * @param sizeY y size of image
 * @param posX x position of image
 * @param posY y position of image
 * @param image image of static image
 */
StaticImage::StaticImage(SpartanHero *spartanHero, int sizeX, int sizeY, int posX, int posY, std::string image) : Item(spartanHero, sizeX, sizeY, posX, posY, image)
{

}