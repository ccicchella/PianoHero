/**
 * @file PuckLongItem.cpp
 * @author Conner
 *
 * Long puck class (holds only)
 */

#include "pch.h"
#include "PuckLongItem.h"
#include <string>

using namespace std;

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;

/**
 * Long puck Constructor
 * @param spartanHero pointer to SpartanHero class
 * @param width width of meter
 * @param height height of meter
 * @param x x pos of meter
 * @param y y pos of meter
 * @param image image of meter
 * @param track track for puck
 * @param tolerance tolerance of puck
 * @param beat beat of puck
 * @param measure measure of puck
 * @param duration duration of puck
 * @param sound sound of long puck
 */
PuckLongItem::PuckLongItem(SpartanHero* spartanHero, int width, int height, int x, int y, string image, int track, double tolerance, double beat, int measure, double duration, wxString sound) : PuckItem(spartanHero, width, height, x, y, image, track, tolerance, beat, measure, duration, sound)
{
    mGame = spartanHero;
    mDuration = duration;
}
/**
 * Function to draw long pucks
 * @param graphics shared pointer to graphics in game
 * @param xStart x start of puck
 * @param yStart y start of puck
 * @param xEnd x end of puck
 * @param yEnd y end of puck
 * @param slope slope of puck
 */
void PuckLongItem::DrawPuck(std::shared_ptr<wxGraphicsContext> graphics, double xStart, double yStart, double xEnd, double yEnd, double slope)
{

    double originalLength = std::sqrt(std::pow(xEnd - xStart, 2) + std::pow(yEnd - yStart, 2));

    double desiredLength = 100 * mDuration;

    double dx = (xEnd - xStart) / originalLength;
    double dy = (yEnd - yStart) / originalLength;

    double xNew = GetX() - desiredLength * dx;
    double yNew = GetY() - desiredLength * dy;

    wxPen pen(*wxRED, LongDurationLineWidth);
    graphics->SetPen(pen);

    if(GetY() > yStart && GetY() <= yEnd && yNew < yStart)
    {
        graphics->StrokeLine(GetX(), GetY(), xStart, yStart);
    }
    else if(GetY() > yStart && GetY() <= yEnd && yNew >= yStart)
    {
        graphics->StrokeLine(GetX(), GetY(), xNew, yNew);
    }
    else if(GetY() >= yEnd && yEnd > yNew)
    {
        graphics->StrokeLine(xEnd, yEnd, xNew, yNew);
    }

    if (GetY() < yEnd)
    {
        PuckItem::DrawPuck(graphics, xStart, yStart, xEnd, yEnd, slope);
    }
}