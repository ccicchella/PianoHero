/**
 * @file Scoreboard.cpp
 * @author Ben
 */
#include "pch.h"
#include <string>
#include "Scoreboard.h"

using namespace std;

/**
 * Constructor
 * @param spartanHero pointer to SpartanHero
 * @param width width of scoreboard
 * @param height height of scoreboard
 * @param x x pos of scoreboard
 * @param y y pos of scoreboard
 * @param image image of scoreboard
 */
Scoreboard::Scoreboard(SpartanHero *spartanHero, int width, int height, int x, int y, string image) : Item(spartanHero,width, height, x, y, image), mScore()
{
    mGame = spartanHero;

    mWidth = width;
    mHeight = height;

    mX = x-(width/2);
    mY = y-(height/2);

    mScore = spartanHero->GetGameScore();
}


/**
 * Function that draws the scoreboard
 * @param graphics shared pointer to graphics in our program
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    auto beat = mGame->GetBeat();
    auto measure = mGame->GetMeasure() + 1;

    if (mGame->GetCountdown() > 4)
    {
        wxFont scoreFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(scoreFont, *wxBLACK);

        graphics->DrawText("Get Ready!", mX + mWidth / 2 - 52, mY + mHeight / 2 - 25);
    }
    else if (mGame->GetCountdown() > 1)
    {
        wxFont countdownFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(countdownFont, *wxBLACK);

        wxString cd = wxString::Format("%.0lf", mGame->GetCountdown());


        double wid, hit;
        graphics->GetTextExtent(cd, &wid, &hit);
        graphics->DrawText(cd, mX + (mWidth - wid) / 2,  mY + mHeight / 2 - 45);

        // Draw the score as text on the scoreboard
        wxFont scoreFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(scoreFont, *wxBLACK);

        wxString scoreText = wxString::Format("%06d", mScore->GetScore());
        graphics->DrawText(scoreText, mX + mWidth / 2 - 55, mY + mHeight / 2 - 10);
    }
    else
    {
        // Draw the score as text on the scoreboard
        wxFont scoreFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(scoreFont, *wxBLACK);

        wxString scoreText = wxString::Format("%06d", mScore->GetScore());
        graphics->DrawText(scoreText, mX + mWidth / 2 - 55, mY + mHeight / 2 - 10);

        wxFont beatFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(beatFont, *wxBLACK);

        graphics->SetFont(beatFont, *wxBLACK);

        wxString beatText = wxString::Format("%d:%d", measure, beat);

        wxDouble textWidth, textHeight;
        graphics->GetTextExtent(beatText, &textWidth, &textHeight);
        wxDouble centeredX = mX + (mWidth - textWidth) / 2;

        graphics->DrawText(beatText, centeredX, mY + mHeight / 2 - 45);
    }
}
void Scoreboard::ResetItem()
{
    mScore->ResetScore();
}
