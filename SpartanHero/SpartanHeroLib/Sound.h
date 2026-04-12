/**
 * @file Sound.h
 * @author Ishraj Yadav
 *
 * Game sound class
 *
 * This class is responsible for the sounds in our game
 */

#ifndef SPARTANHERO_SOUND_H
#define SPARTANHERO_SOUND_H
#include <miniaudio.h>

/**
 * @brief The Sound class represents an audio sound.
 */
class Sound {
public:
    /**
     * @brief Constructor for the Sound class.
     */
    Sound();

    /**
     * @brief Destructor for the Sound class.
     */
    ~Sound();

    /**
     * @brief Play the sound.
     */
    void PlaySound();

    /**
     * @brief Handle sound playback completion.
     */
    void PlayEnd();

    void loadAudioFile(ma_engine *audioEngine, wxString audioFile);
    /**
     * Function to change volume
     * @param volume number to set volume
     *
     */
    void SetVolume(double volume) {mVolume = volume;}


private:
    /// The miniaudio sound
    ma_sound mSound;

    /// Directory that contains the audio files
    const std::wstring mAudioDirectory = L"audio";

    /// The volume of the sound
    double mVolume = 1.0;

    /// Has the sound been loaded?
    bool mLoaded = false;

};

#endif //SPARTANHERO_SOUND_H
