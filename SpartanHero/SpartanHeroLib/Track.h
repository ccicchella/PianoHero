/**
 * @file Track.h
 * @author Caden McDonald
 *
 * This class is for tracks in SpartanHero
 *
 * Track contains information for tracks and pucks active on the track
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_TRACK_H
#define SPARTANHERO_SPARTANHEROLIB_TRACK_H

#include <wx/graphics.h>
#include <deque>
#include "PuckItem.h"
/**
 * This class defines the tracks in the game
 */
class Track
{
private:
    /// Track number
    int mNumber;
    /// Pointer to key
    std::unique_ptr<wxImage> mKeyImage;
    /// Key image
    wxGraphicsBitmap mKeyBitmap;
    /// key size in x
    int mKeySizeX;
    /// key size in y
    int mKeySizeY;
    /// key
    std::string mKey;
    /// pucks in track
    std::deque<std::shared_ptr<PuckItem>> mTrackPucks;
    /// active pucks
    std::deque<std::shared_ptr<PuckItem>> mActivePucks;
    /// inactive pucks
    std::vector<std::shared_ptr<PuckItem>> mInactivePucks;
    /// active long pucks
    std::deque<std::shared_ptr<PuckItem>> mActiveLongPucks;
    ///Pucks to remove
    std::vector<std::shared_ptr<PuckItem>> mToRemove;
    /// x position
    double mXPos;
    /// y position
    double mYPos;
    /// width of track
    double mWidth;
    /// height of track
    double mHeight;
    /// top width of track
    double mTopWidth;
    /// counter for pucks
    int mCounter=0;
    /// track start location in x
    double mXTrackStart=0;
    /// track start location in y
    double mYTrackStart=0;
    /// track end location in x
    double mXTrackEnd=0;
    /// track end location in y
    double mYTrackEnd=0;
    /// slope of track
    double mSlope;
    /// pointer to SpartanHero
    SpartanHero* mGame;

    /// shared pointer to graphics
    std::shared_ptr<wxGraphicsContext> mGraphics;

    /// Current puck index
    int mCurrent = 0;

public:


    Track(SpartanHero* spartanHero, int number, std::string keyImage, int keySizeX, int keySizeY, std::string key, double xPos, double yPos, double width, double height, double topWidth);

    void AddPuck(std::shared_ptr<PuckItem> puck);

    /**
     * Getter for puck count
     * @return puck count
     */
    int GetCounter(){return mCounter;}
    /**
     * Getter for x track start
     * @return x start
     */
    double GetXTrackStart(){return mXTrackStart;}
    /**
     * Getter for y track start
     * @return y start
     */
    double GetYTrackStart(){return mYTrackStart;}
    /**
     * Getter for x track end
     * @return x end
     */
    double GetXTrackEnd(){return mXTrackEnd;}
    /**
     * Getter for y track end
     * @return y end
     */
    double GetYTrackEnd(){return mYTrackEnd;}
    /**
     * Getter for x pos
     * @return x pos
     */
    double GetXPos(){return mXPos;}
    /**
     * Getter for y pos
     * @return y pos
     */
    double GetYPos(){return mYPos;}
    /**
     * Getter for width
     * @return width
     */
    double GetWidth(){return mWidth;}
    /**
     * Getter for height
     * @return height
     */
    double GetHeight(){return mHeight;}
    /**
     * Getter for active pucks
     * @return active pucks
     */
    std::deque<std::shared_ptr<PuckItem>> GetActivePucks() {return mActivePucks;}

    /**
     * Getter for active long pucks
     * @return deque of pointers to pucks / active pucks
     */
    std::deque<std::shared_ptr<PuckItem>> GetActiveLongPucks(){return mActiveLongPucks;}

    void DrawTrack(std::shared_ptr<wxGraphicsContext> graphics, float absoluteBeat);

    void Update(double elapsed);
};

#endif //SPARTANHERO_SPARTANHEROLIB_TRACK_H
