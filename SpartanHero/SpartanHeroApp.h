/**
 * @file SpartanHeroApp.h
 * @author Charles Cicchella
 *
 *
 */

#ifndef PROJECT1__SPARTANHEROAPP_H
#define PROJECT1__SPARTANHEROAPP_H
#include <miniaudio.h>

/**
 * Main application class
 */
class SpartanHeroApp : public wxApp
{
public:
    bool OnInit() override;

    int OnExit() override;
private:
    /// The audio engine for miniaudio
    ma_engine mAudioEngine;
};

#endif //PROJECT1__SPARTANHEROAPP_H
