/**
 * @file PuckItem.h
 * @author Conner Smith
 *
 * Puck class
 *
 * This class is a child of Item and is the pucks to our game
 */

#ifndef SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_PUCKITEM_H
#define SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_PUCKITEM_H

#include "Item.h"
#include "PuckDeclaration.h"
/**
 * This class is a child of item for pucks
 */
class PuckItem : public Item
{
private:
    /// Track to be placed on
    int mTrack=1;

    /// X size of puck
    double mSizeX=60;
    /// Y size of puck
    double mSizeY=60;

    /// pointer to the game
    SpartanHero* mGame;

    /// Tolerance of the puck
    double mTolerance=0.5;
    /// beat of puck
    double mBeat=1;
    /// measure of puck
    int mMeasure=1;
    /// duration of puck
    double mDuration = 0.25;

    /// The underlying puck image
    std::unique_ptr<wxImage> mPuckImage = nullptr;

    /// The bitmap used to display the puck
    wxGraphicsBitmap mPuckBitmap;

    /// x speed
    double mSpeedX=-10;
    /// y speed
    double mSpeedY=-10;
    /// absolute beat
    double mAbsoluteBeat=0;
    /// Name of sound to be played on hit
    wxString mSound;

    /// start x position
    double mXStart=0;
    /// start y position
    double mYStart=0;
    /// end x position
    double mXEnd=0;
    /// end y position
    double mYEnd=0;

    /// level beats per minute
    double mBeatsPerMinute=0;

    /// Bool for if was hit
    bool mHitTest = false;


public:
    /// Assignment operator
    void operator=(const PuckItem &) = delete;

    /// Destructor
    ~PuckItem(){}
    /**
     * Getter for track
     * @returns track
     */
    int GetTrack() {return mTrack;}
    /**
     * Getter for absolute beat
     * @returns absolute beat
     */
    double GetAbsoluteBeat() {return mAbsoluteBeat;}
    /**
     * Getter for tolerance
     * @returns tolerance
     */
    double GetTolerance() {return mTolerance;}
    /**
     * Getter for mSound
     * @return mSound
     */
    wxString GetSound() {return mSound;}
    /**
     * Getter for x speed
     * @returns x speed
     */
    double GetSizeX(){return mSizeX;}
    /**
     * Getter for y speed
     * @returns y speed
     */
    double GetSizeY(){return mSizeY;}
    /**
     * Sets x size
     * @param sizeX x size
     */
    void SetSizeX(double sizeX){mSizeX = sizeX;}
    /**
     * Sets y size
     * @param sizeY y size
     */
    void SetSizeY(double sizeY){mSizeY = sizeY;}
    /**
     * Getter for duration
     * @returns duration
     */
    double GetDuration(){return mDuration;}
    /**
     * Getter for HitTest
     * @returns duration
     */
     bool GetHitTest(){return mHitTest;}
    /**
     * Sets HitTest
     * @param boolean
     */
    void SetHitTest(bool boolean){mHitTest = boolean;}



    PuckItem(SpartanHero *spartanHero, int width, int height, int x, int y, std::string image, int track, double tolerance, double beat, int measure, double duration, wxString sound);
    void virtual DrawPuck(std::shared_ptr<wxGraphicsContext> graphics, double xStart, double yStart, double xEnd, double yEnd, double slope);
    void Update (double elapsed);

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPuckItem(this) ;}

    /**
     * Sets x start
     * @param startX start x
     */
    void SetStartX(double startX){mXStart=startX;}
    /**
     * Sets y start
     * @param startY start y
     */
    void SetStartY(double startY){mYStart=startY;}
    /**
     * Sets x end
     * @param endX end x
     */
    void SetEndX(double endX){mXEnd=endX;}
    /**
     * Sets y end
     * @param endY end y
     */
    void SetEndY(double endY){mYEnd=endY;}
    /**
     * Sets the level's bpm
     * @param bpm level's bpm
     */
    void SetBeatsPerMinute(double bpm){mBeatsPerMinute=bpm;}
};

#endif //SPARTANHERO_SPARTANHERO_SPARTANHEROLIB_PUCKITEM_H
