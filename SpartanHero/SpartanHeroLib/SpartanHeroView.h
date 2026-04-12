/**
 * @file SpartanHeroView.h
 * @author charl
 *
 * Game View class
 *
 * This class has all of the information related to changing the view of the Game
 */

#ifndef PROJECT1_SPARTANHEROLIB_SPARTANHEROVIEW_H
#define PROJECT1_SPARTANHEROLIB_SPARTANHEROVIEW_H


#include "SpartanHero.h"
#include "Sound.h"
#include <miniaudio.h>
#include <set>

/**
 * This class is for the view of SpartanHero
 */
class SpartanHeroView : public wxWindow
{
private:
    void OnPaint(wxPaintEvent& event);

    /// An object that describes our game
    SpartanHero mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// Audio engine
    ma_engine* mAudioEngine;

    /// Set to keep track of active keys
    std::set<int> mActiveKeys;



public:
    void Initialize(wxFrame* parent);
    //void OnLeftDown(wxMouseEvent &event);
    void OnTimer(wxTimerEvent &event);
    void OnLoadLevelZero(wxCommandEvent &event);
    void OnLoadLevelOne(wxCommandEvent &event);
    void OnLoadLevelTwo(wxCommandEvent &event);
    void OnLoadLevelThree(wxCommandEvent &event);
    void OnKeyUp(wxKeyEvent& event);
    void OnKeyDown(wxKeyEvent& event);

    SpartanHeroView(ma_engine *audioEngine);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
    /**
     * Getter for Game
     * @return pointer to game
     */
     SpartanHero* GetGame(){return &mGame;}

};

#endif //PROJECT1_SPARTANHEROLIB_SPARTANHEROVIEW_H
