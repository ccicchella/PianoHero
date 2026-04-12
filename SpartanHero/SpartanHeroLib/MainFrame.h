/**
 * @file MainFrame.h
 * @author Charles Cicchella
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_SPARTANHEROLIB_MAINFRAME_H
#define PROJECT1_SPARTANHEROLIB_MAINFRAME_H

#include <miniaudio.h>
#include "SpartanHeroView.h"
#include "Score.h"
#include "SpartanHero.h"

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    /// Pointer to SpartanHeroView
    SpartanHeroView* mGameView = nullptr;

    /// Map to scores for achievement
    std::map<wxString, int> mHighestScores;


public:
    void Initialize(ma_engine* audioEngine);

    void DisplayAchievements(wxCommandEvent &event);

    void OnClose(wxCloseEvent &event);

    void AutoPlay(wxCommandEvent& event);
};

#endif //PROJECT1_SPARTANHEROLIB_MAINFRAME_H
