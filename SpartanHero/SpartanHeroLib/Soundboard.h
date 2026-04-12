/**
 * @file Soundboard.h
 * @author Ishraj Yadav
 * @brief Decleration of the Soundboard class
 *
 * This class is a child class from Item that creates the soundboard of the game
 */

#ifndef SPARTANHERO_SOUNDBOARD_H
#define SPARTANHERO_SOUNDBOARD_H

#include <map>
#include "Item.h"
#include "SpartanHero.h"
#include "SoundBoardDeclaration.h"
#include "Track.h"

/**
 * This class defines the soundboard
 */
class Soundboard : public Item
{
private:
    /// pointer to SpartanHero
    SpartanHero* mGame;

    /// The cover of the soundboard
    std::unique_ptr<wxImage> mSoundboardCover;

    /// The bitmap used to display the cover
    wxGraphicsBitmap mSoundboardCoverBitmap;

    /// List of tracks
    std::vector<std::shared_ptr<Track>> mTracks = std::vector<std::shared_ptr<Track>>(10);
    /// X pos
    int mX;
    /// Y pos
    int mY;
    /// Width
    int mWidth;
    /// height
    int mHeight;
    /// top width
    int mTopWidth;
    /// size of beats
    int mSizeBeats;
    /// Bool for first beat
    bool mCounter = false;

public:
    Soundboard(SpartanHero *spartanHero, int width, int height, int x, int y, std::string boardImage, std::string coverImage, wxXmlNode* sbChildren, int topWidth, int sizeBeats);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    virtual void Update(double elapsed);

    /**
     * Getter for tracks
     * @return tracks
     */
    std::vector<std::shared_ptr<Track>> GetTracks() {return mTracks;}

    /**
    * Accept a visitor
    * @param item The visitor we accept
    */
    void Accept(ItemVisitor* item) override { item->VisitSoundboard(this); }
    void AddPuck(std::shared_ptr<PuckItem> puck);
};


#endif //SPARTANHERO_SOUNDBOARD_H
