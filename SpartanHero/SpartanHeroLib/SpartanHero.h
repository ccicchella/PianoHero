/**
 * @file SpartanHero.h
 * @author charl, Ben
 *
 * Game class
 *
 * This class creates the game, has important member variables used throught the rest of the classes
 */

#ifndef PROJECT1_SPARTANHEROLIB_SPARTANHERO_H
#define PROJECT1_SPARTANHEROLIB_SPARTANHERO_H

#include "Item.h"
#include "ItemVisitor.h"
#include "Score.h"
#include "Sound.h"
#include <miniaudio.h>
#include "Track.h"
#include <map>
#include <utility>

class Level;

/**
 * This class is our game class
 */
class SpartanHero
{
private:
    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// Map of sounds
    std::map<wxString, std::shared_ptr<Sound>> mSoundMap = {};

    /// screen x dimension
    int mPlayX = 2000;
    /// screen y dimension
    int mPlayY = 1400;

    /// variable for scaling
    double mScale;

    /// The audio engine for miniaudio
    ma_engine* mAudioEngine;

    /// X offset
    double mXOffset;

    /// Y offset
    double mYOffset;

    /// Whether or not to draw the beginning sequencing text
    bool mDrawBegin = true;

    /// Whether or not to draw the end sequencing text
    bool mDrawEnd = false;

    /// Current absolute beat
    float mAbsoluteBeat = -4;

    /// Current beat
    int mBeat = 0;

    /// Current measure
    int mMeasure = 0;

    /// Current beats per minute
    int mBeatsPerMinute = 0;

    /// Current beats per measure
    float mBeatsPerMeasure = 0;

    /// Current max amount of measures
    int mMaxMeasure = 0;

    /// Shared pointer to graphics
    std::shared_ptr<wxGraphicsContext> mGraphics;

    /// Current Level Number
    /// Initialized at 1
    wxString mCurrLevel = L"1";

    /// Current score of the game
    Score *mGameScore;


    /// Countdown count
    double mCountDown = 6;

    /// Countdown end
    double mCountDownEnd = 2;

    /// First absolute beat to start track
    double mFirstAbsoluteBeat;

    /// For backing track start
    bool mFirstTicker=true;

    /// Counter for pucks in HitTest
    int mCounter = 0;

    /// Bool for AutoPlay
    bool mAutoPlayEnabled = false;

public:
    ~SpartanHero();
    SpartanHero();
    SpartanHero(ma_engine* audioEngine);
    /**
     * Getter for AutoPlayEnabled
     * @returns AutoPlayEnabled
     */
    bool GetAutoPlayEnabled(){return mAutoPlayEnabled;}
    /**
     * Setter for AutoPlayEnabled
     * @param enabled boolean to set mAutoPlayEnabled
     */
    void SetAutoPlayEnabled(bool enabled){mAutoPlayEnabled = enabled;}

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    /**
     * Getter for absolute beat
     * @returns absolute beat
     */
    float GetAbsoluteBeat() { return mAbsoluteBeat; }
    /**
     * Getter for beat
     * @returns beat
     */
    int GetBeat() { return mBeat; }
    /**
     * Getter for measure
     * @returns measure
     */
    int GetMeasure() { return mMeasure; }
    /**
     * Getter for countdown
     * @returns countdown
     */
    double GetCountdown() {return mCountDown;}
    /**
     * Getter for bpm
     * @returns bpm
     */
    int GetBeatsPerMinute() {return mBeatsPerMinute;}
    /**
     * Getter for beats per measure
     * @returns beats per measure
     */
    double GetBeatsPerMeasure() {return mBeatsPerMeasure;}
    /**
     * Getter for max measure
     * @returns max measure
     */
    int GetMaxMeasure() {return mMaxMeasure;}
    /**
     * Getter for current level
     * @returns current level
     */
    wxString GetCurrentLevel(){return mCurrLevel;}
    /**
     * gets mAudioEngine
     * @return mAudioEngine
     */
     ma_engine* GetAudioEngine() {return mAudioEngine;}
     /**
      * Plays sound from mSoundMap
      * @param sound Key in mSoundMap
      */
      void PlaySoundFromMap(const wxString& sound) {mSoundMap[sound]->PlaySound();}
      /**
       * Stops sound from mSoundMap
       * @param sound Key in mSoundMap
       */
      void StopSoundFromMap(const wxString& sound) {mSoundMap[sound]->PlayEnd();}
      /**
       * Sets the first absolute beat
       * @param firstAbsoluteBeat first absolute beat of the game
       */
       void SetFirstAbsoluteBeat(double firstAbsoluteBeat){mFirstAbsoluteBeat=firstAbsoluteBeat;}

    void Update(double elapsed);
    void Load(const wxString &filename);
    void ResetLevel();

    void Clear();
    void Add(std::shared_ptr<Item> item);
    /**
     * Set x play window
     * @param playX
     */
    void SetPlayX(int playX) {mPlayX = playX;}
    /**
     * Set y play window
     * @param playY
     */
    void SetPlayY(int playY) {mPlayY = playY;}
    /**
     * Set current level
     * @param currLevel
     */
    void SetCurrLevel(const wxString &currLevel) {mCurrLevel = currLevel;}
    /**
     * Getter for x dimension of game
     * @returns x dimension of game
     */
    int GetPlayX() {return mPlayX;}
    /**
     * Getter for y dimension of game
     * @returns y dimension of game
     */
    int GetPlayY() {return mPlayY;}


    /**
     * Set beats per minute
     * @param bpm beats per minute
     */
    void SetBeatsPerMinute(int bpm) {mBeatsPerMinute = bpm;}
    /**
     * Set beats per measure
     * @param bpm beats per measure
     */
    void SetBeatsPerMeasure(int bpm) {mBeatsPerMeasure = bpm;}
    /**
     * Set max measure
     * @param measure max measure
     */
    void SetMaxMeasure(int measure) {mMaxMeasure = measure;}

    void DrawBegin(std::shared_ptr<wxGraphicsContext> graphics);
    /**
     * Set Draw begin
     * @param set what to set draw begin
     */
    void SetDrawBegin(bool set) {mDrawBegin = set;}

    void Accept(ItemVisitor *visitor);

    bool HitTest(int trackNum);

    void IncrementScore(int increment);

    /**
     * Getter for score
     * @returns score
     */
    Score* GetGameScore() {return mGameScore;}

    void IncrementTotalScore(int increment);
    /**
     * Function to add sound to map
     * @param name name of sound
     * @param sound shared pointer to sound
     */
    void AddToSoundMap(const wxString& name, std::shared_ptr<Sound> sound) {mSoundMap[name] = sound;}
    void DrawEnd(std::shared_ptr<wxGraphicsContext> graphics);
    void StopSound(int trackNum);
    void AutoPlay();
    double DurationHitTest(int trackNum);
    void IncrementMeterScore(int increment);
};

#endif //PROJECT1_SPARTANHEROLIB_SPARTANHERO_H
