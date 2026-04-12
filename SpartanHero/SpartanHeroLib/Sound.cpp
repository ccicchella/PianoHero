/**
 * @file Sound.cpp
 * @author Ishraj Yadav
 * @brief Implementation of the Sound class
 */

#include "pch.h"
#include "Sound.h"

/**
 * Constructor
 */
Sound::Sound()
{

}

/**
 * Load an audio file into the ma_sound object.
 * @param audioEngine The miniaudio engine.
 * @param audioFile the audio file we are using
 */
void Sound::loadAudioFile(ma_engine* audioEngine, wxString audioFile) {
    audioFile = mAudioDirectory + L"/" + audioFile;
    if(audioEngine != nullptr) {

        auto result = ma_sound_init_from_file(audioEngine, wxString(audioFile), 0, NULL, NULL, &mSound);
        if (result != MA_SUCCESS) {
            wxString msg;
            msg.Printf(L"Unable to load audio file %s - %d", audioFile, result);
            wxMessageBox(msg, wxT("miniaudio failure"), wxICON_ERROR);
        } else {
            mLoaded = true;
            ma_sound_set_volume(&mSound, mVolume);
        }
    }
}

/**
 * @brief Play the sound
 */
void Sound::PlaySound()
{
    if(mLoaded)
    {
        // If the sound is already playing, stop it first
        if(ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }

        // Always rewind to the beginning before playing
        ma_sound_seek_to_pcm_frame(&mSound, 0);

        // And play the sound!
        ma_sound_start(&mSound);
    }
}

/**
 * @brief Stop playing the sound
 */
void Sound::PlayEnd()
{
    if(mLoaded)
    {
        // If the sound is already playing, stop it first
        if(ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }
    }
}

/**
 * Destructor
 */
Sound::~Sound()
{
    if(mLoaded)
    {
        if(ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }

        ma_sound_uninit(&mSound);
    }
}
