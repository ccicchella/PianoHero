/**
 * @file SpartanHeroApp.cpp
 * @author Charles Cicchella
 */

#include "pch.h"
#include "SpartanHeroApp.h"
#include "MainFrame.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif



/**
 * Initialize the application.
 * @return
 */
bool SpartanHeroApp::OnInit()
{
#ifdef WIN32
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Initialize the audio engine
    auto result = ma_engine_init(NULL, &mAudioEngine);
    if (result != MA_SUCCESS)
    {
        wxString msg;
        msg.Printf(L"Unable to initialize miniaudio engine - %d", result);
        wxMessageBox(msg, wxT("miniaudio failure"), wxICON_ERROR);
        return false;
    }

    auto frame = new MainFrame();
    frame->Initialize(&mAudioEngine);
    frame->Show(true);

    return true;
}

/**
 * Exit the application. Time to shut down services such as miniaudio
 * @return Normal program exit code
 */
int SpartanHeroApp::OnExit()
{
    ma_engine_uninit(&mAudioEngine);
    return wxAppBase::OnExit();
}