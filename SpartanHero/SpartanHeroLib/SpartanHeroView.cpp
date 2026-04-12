/**
 * @file SpartanHeroView.cpp
 * @author charl
 *
 * Game view class
 */

#include "pch.h"
#include "SpartanHeroView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include <wx/graphics.h>
#include "Sound.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 60;

/**
 * Constructorff
 * @param audioEngine The audio engine to use
 */
SpartanHeroView::SpartanHeroView(ma_engine *audioEngine) : mGame(audioEngine)
{
    mAudioEngine = audioEngine;
}

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void SpartanHeroView::Initialize(wxFrame* parent)
{
    wxString filename = "../levels/level1.xml";
    mGame.Load(filename);
    Refresh();

    Create(parent, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SpartanHeroView::OnPaint, this);
    Bind(wxEVT_KEY_UP, &SpartanHeroView::OnKeyUp, this);
    Bind(wxEVT_KEY_DOWN, &SpartanHeroView::OnKeyDown, this);


    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanHeroView::OnLoadLevelZero, this, IDM_LEVEL_ZERO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanHeroView::OnLoadLevelOne, this, IDM_LEVEL_ONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanHeroView::OnLoadLevelTwo, this, IDM_LEVEL_TWO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanHeroView::OnLoadLevelThree, this, IDM_LEVEL_THREE);

    Bind(wxEVT_TIMER,&SpartanHeroView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanHeroView::OnPaint(wxPaintEvent& event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);

    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Handle a key press event
 * @param event Keypress event
 */
void SpartanHeroView::OnKeyDown(wxKeyEvent& event)
{
    wxString currentLevel = mGame.GetCurrentLevel();
    int keyCode = event.GetKeyCode();

        // Check if the pressed key is 'A' (key code 65)
        if(keyCode == 65)
        {
            if (mGame.HitTest(0))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'S' (key code 83)
        else if(keyCode == 83)
        {
            if (mGame.HitTest(1))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'D' (key code 68)
        else if(keyCode == 68)
        {
            if (mGame.HitTest(2))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'F' (key code 70)
        else if(keyCode == 70)
        {
            if (mGame.HitTest(3))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'G' (key code 71)
        else if(keyCode == 71 && mGame.GetCurrentLevel() == "2")
        {
            if (mGame.HitTest(4))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'H' (key code 72)
        else if(keyCode == 72 && mGame.GetCurrentLevel() == "2")
        {
            if (mGame.HitTest(5))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'J' (key code 74)
        else if(keyCode == 74)
        {
            if (mGame.HitTest(6))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'K' (key code 75)
        else if(keyCode == 75)
        {
            if (mGame.HitTest(7))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is 'L' (key code 76)
        else if(keyCode == 76)
        {
            if (mGame.HitTest(8))
            {
                mGame.IncrementScore(10);
            }
        }
            // Check if the pressed key is ';' (key code 59)
        else if(keyCode == 59)
        {
            if (mGame.HitTest(9))
            {
                mGame.IncrementScore(10);
            }
        }
}
/**
 * Handle a key up event
 * @param event key up event
 */
void SpartanHeroView::OnKeyUp(wxKeyEvent& event)
{
    //UpdateTime();
    int keyCode = event.GetKeyCode();

        if (keyCode == 65)
        {
            double percentage = mGame.DurationHitTest(0);
            mGame.IncrementScore(int(percentage*10));
            //mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(0);
        }
        if (keyCode == 83)
        {
            double percentage = mGame.DurationHitTest(1);
            mGame.IncrementScore(int(percentage*10));
            //mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(1);
        }
        if (keyCode == 68)
        {
            double percentage = mGame.DurationHitTest(2);
            mGame.IncrementScore(int(percentage*10));
            //mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(2);
        }
        if (keyCode == 70)
        {
            double percentage = mGame.DurationHitTest(3);
            mGame.IncrementScore(int(percentage*10));
           // mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(3);
        }
        if (keyCode == 71 && mGame.GetCurrentLevel() == "2")
        {
            double percentage = mGame.DurationHitTest(4);
            mGame.IncrementScore(int(percentage*10));
            //mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(4);
        }
        if (keyCode == 72 && mGame.GetCurrentLevel() == "2")
        {
            double percentage = mGame.DurationHitTest(5);
            mGame.IncrementScore(int(percentage*10));
           // mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(5);
        }
        if (keyCode == 74)
        {
            double percentage = mGame.DurationHitTest(6);
            mGame.IncrementScore(int(percentage*10));
            //mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(6);
        }
        if (keyCode == 75)
        {
            double percentage = mGame.DurationHitTest(7);
            mGame.IncrementScore(int(percentage*10));
            //mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(7);
        }
        if (keyCode == 76)
        {
            double percentage = mGame.DurationHitTest(8);
            mGame.IncrementScore(int(percentage*10));
           // mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(8);
        }
        if (keyCode == 59)
        {
            double percentage = mGame.DurationHitTest(9);
            mGame.IncrementScore(int(percentage*10));
           // mGame.IncrementMeterScore(int(percentage*10));
            mGame.StopSound(9);
        }
}

/**
 * Time event handler
 * @param event Menu eventd
 */
void SpartanHeroView::OnTimer(wxTimerEvent& event)
{
    if (mGame.GetCountdown() <= 0)
    {
        mGame.SetDrawBegin(false);
    }
    Refresh();
}

/**
 * Load level zero handler
 * @param event
 */
void SpartanHeroView::OnLoadLevelZero(wxCommandEvent& event)
{
    wxString filename = "../levels/level0.xml";
    mGame.SetCurrLevel(L"0");
    mGame.Load(filename);
    mGame.ResetLevel();
    Refresh();
}

/**
 * Load level one handler
 * @param event
 */
void SpartanHeroView::OnLoadLevelOne(wxCommandEvent &event)
{
    wxString filename = "../levels/level1.xml";
    mGame.SetCurrLevel(L"1");
    mGame.Load(filename);
    mGame.ResetLevel();
    Refresh();

}

/**
 * Load level two handler
 * @param event
 */
void SpartanHeroView::OnLoadLevelTwo(wxCommandEvent &event)
{
    wxString filename = "../levels/level2.xml";
    mGame.SetCurrLevel(L"2");
    mGame.Load(filename);
    mGame.ResetLevel();
    Refresh();
}

/**
 * Load level three handler
 * @param event
 */
void SpartanHeroView::OnLoadLevelThree(wxCommandEvent &event)
{
    wxString filename = "../levels/level3.xml";
    mGame.SetCurrLevel(L"3");
    mGame.Load(filename);
    mGame.ResetLevel();
    Refresh();
}
