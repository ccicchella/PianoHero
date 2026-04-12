/**
 * @file Scoreboard.h
 * @author Ben
 *
 * Scoreboard class for game
 *
 * This class is a child of item and creates the scoreboard for the game
 */

#ifndef SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_SCOREBOARD_H
#define SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_SCOREBOARD_H

#include "SpartanHero.h"
#include "Item.h"
#include "Score.h"
/**
 * This class is for the scoreboard item in the game
 */
class Scoreboard : public Item
{
private:
    /// pointer to SpartanHero
    SpartanHero *mGame;
    /// x pos
    int mX;
    /// y pos
    int mY;
    /// width
    int mWidth;
    /// height
    int mHeight;
    /// pointer to Score
    Score *mScore;
public:
    Scoreboard(SpartanHero *spartanHero, int width, int height, int x, int y, std::string image);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * override function for reset item
     */
    void ResetItem() override;

    /**
    * Accept a visitor
    * @param item The visitor we accept
    */
    void Accept(ItemVisitor* item) override { item->VisitScoreboard(this); }

};

#endif //SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_SCOREBOARD_H
