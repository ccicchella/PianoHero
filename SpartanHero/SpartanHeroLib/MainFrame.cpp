/**
 * @file MainFrame.cpp
 * @author Charles Cicchella
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartanHeroView.h"
#include "ids.h"
#include <wx/graphics.h>
#include <miniaudio.h>

/**
 * Initialize the MainFrame window.
 * @param audioEngine ma engine for audio
 */
void MainFrame::Initialize(ma_engine* audioEngine)
{
    Create(nullptr, wxID_ANY, L"SpartanHero",
           wxDefaultPosition,  wxSize( 1200,700 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto spartanHeroView = new SpartanHeroView(audioEngine);
    mGameView = spartanHeroView;
    spartanHeroView->Initialize(this);

    // Add it to the sizer
    sizer->Add(spartanHeroView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto achievementMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save game as...");
    fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open game file...");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    levelMenu->Append(IDM_LEVEL_ZERO, "Level 0", "Play level 0");
    levelMenu->Append(IDM_LEVEL_ONE, "Level 1", "Play level 1");
    levelMenu->Append(IDM_LEVEL_TWO, "Level 2", "Play level 2");
    levelMenu->Append(IDM_LEVEL_THREE, "Level 3", "Play level 3");
    levelMenu->AppendSeparator();
    levelMenu->Append(IDM_AUTOPLAY, "AutoPlay", "Plays the game without user input");

    achievementMenu->Append(IDM_ACHIEVEMENT, "Achievement Menu", "Achievement Menu");
    //PopupMenu(achievementMenu);


    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Levels");
    menuBar->Append(achievementMenu, L"&Achievements");
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar( menuBar );

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    //Bind OnExit
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);

    //Bind Achievement
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::DisplayAchievements, this, IDM_ACHIEVEMENT);

    //Bind About
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    /// Autoplay
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::AutoPlay, this, IDM_AUTOPLAY);

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to SpartanHero!",
                 L"About SpartanHero",
                 wxOK,
                 this);
}


/**
 * Achievement menu option handlers
 * @param event
 */
void MainFrame::DisplayAchievements(wxCommandEvent& event)
{
    int score = mGameView->GetGame()->GetGameScore()->GetScore();
    wxString level = mGameView->GetGame()->GetCurrentLevel();

    if (mHighestScores[level] < score) {
        mHighestScores[level] = score;
    }

    std::vector<std::pair<wxString, std::pair<wxString, int>>> achievementRequirements =
        {
        {"1", {"Finish with a score of 500 on Level 1", 500}},
        {"1", {"Finish with a score of 1000 on Level 1", 1000}},
        {"1", {"Finish with a score of 1500 on Level 1", 1500}},
        {"2", {"Finish with a score of 500 on Level 2", 500}},
        {"2", {"Finish with a score of 1000 on Level 2", 1000}},
        {"2", {"Finish with a score of 1500 on Level 2", 1500}},
        {"3", {"Finish with a score of 500 on Level 3", 500}},
        {"3", {"Finish with a score of 1000 on Level 3", 1000}},
        {"3", {"Finish with a score of 1500 on Level 3", 1500}},
        };


    wxString message;

    // Iterate through achievements and mark completed ones based on score
    for (const auto& achievement : achievementRequirements)
    {
        message += achievement.second.first;
        if (mHighestScores[achievement.first] >= achievement.second.second)
        {
            message += " (Completed)";
        }
        message += "\n";
    }

    // Display the achievements
    wxMessageBox(message, "Achievements", wxOK | wxICON_INFORMATION);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}


/**
 * Handler for AutoPlay
 * @param event The AutoPlay event
 */
void MainFrame::AutoPlay(wxCommandEvent& event)
{
    if (mGameView->GetGame()->GetAutoPlayEnabled())
    {
        mGameView->GetGame()->SetAutoPlayEnabled(false);
    }
    else
    {
        mGameView->GetGame()->SetAutoPlayEnabled(true);
    }
}
