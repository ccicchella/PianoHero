# PianoHero

A Guitar Hero-style piano game built in C++ as part of MSU's CSE 335 (Object-Oriented Software Design) course. Notes scroll down the screen and the player presses the corresponding keys in time with the music.

## Try It

A prebuilt Windows executable is included — download `SpartanHero.exe` and run it directly, no build required.

## Features

- Scrolling note tracks with timing-based scoring
- Multiple levels loaded from XML configuration files
- Audio playback via the miniaudio library
- Scoreboard tracking hits, misses, and total score
- Automatic window scaling to fit any screen size

## Tech Stack

C++14, wxWidgets, miniaudio, CMake, GoogleTest

## Build from Source

Requirements: CMake 3.x, a C++14 compiler, wxWidgets installed.

    git clone https://github.com/ccicchella/PianoHero
    cd PianoHero/SpartanHero
    mkdir build && cd build
    cmake ..
    cmake --build .

Built as a team project with contributions from Charles Cicchella, Conner Smith, Caden McDonald, and Ben Crimmins.
